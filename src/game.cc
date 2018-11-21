//
// Created by jesse on 11/15/18.
//

#include "game.h"

namespace pie {

constexpr Color Game::text_color_;

Game::Game(std::size_t width, const Rules& rules)
  : renderer_(width, width),
    mouse_(renderer_.window()),
    square_tex_(square_texture_path_),
    square_vs_(square_vs_path_),
    square_fs_(square_fs_path_),
    square_shader_(square_vs_, square_fs_),
    char_map_(getCharMap(font_path_, font_size_, text_color_)),
    rules_(rules),
    init_rules_(rules_),
    tiles_(rules_.board().side(), rules_.board().side())
{
  this->SetupBoard();
  // initialize keyboard controls
  renderer_.SetKeyCallback([](GLFWwindow *w, int k, int, int, int) {
    if ((k == GLFW_KEY_ESCAPE || k == GLFW_KEY_Q) &&  GLFW_PRESS) {
      glfwSetWindowShouldClose(w, GLFW_TRUE);
    }
  });
}

Game::Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width)
  : renderer_(width, width),
    mouse_(renderer_.window()),
    square_tex_(square_texture_path_),
    square_vs_(square_vs_path_),
    square_fs_(square_fs_path_),
    square_shader_(square_vs_, square_fs_),
    char_map_(getCharMap(font_path_, font_size_, text_color_)),
    rules_(side, start_x, start_y),
    init_rules_(rules_),
    tiles_(side, side)
{
  this->SetupBoard();
  // Initialize mouse controls
  glfwSetWindowUserPointer(renderer_.window(), this);
  mouse_.SetClickCallback([](GLFWwindow *w, int b, int a, int) {
    if (b == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_PRESS) {
      auto game = static_cast<decltype(this)>(glfwGetWindowUserPointer(w));
      game->ProcessMouseClick();
    }
  });
  // initialize keyboard controls
  renderer_.SetKeyCallback([](GLFWwindow *w, int k, int, int, int) {
    auto game = static_cast<decltype(this)>(glfwGetWindowUserPointer(w));
    if ((k == GLFW_KEY_ESCAPE || k == GLFW_KEY_Q) &&  GLFW_PRESS) {
      glfwSetWindowShouldClose(w, GLFW_TRUE);
    } else if (k == GLFW_KEY_R && GLFW_PRESS) {
      game->Reset();
    }
  });
}

void Game::Reset() {
  rules_ = Rules(init_rules_);
  tiles_ = Grid<GameTile>(rules_.board().side(), rules_.board().side());
  renderer_.Clear();
  this->SetupBoard();
}

void Game::SetupBoard() {
  size_t side = rules_.board().side();
  int width, height;
  glfwGetFramebufferSize(renderer_.window(), &width, &height);
  font_scale_ = font_scale_factor_*width/(side*font_size_);
  // Build grid of GameTiles from underlying Rules
  const double square_width = 2.0 / side;
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      auto pos = GridToScreen(std::make_pair(i, j));
      // first contruct the GameTile
      const auto tile = rules_.board().GetTile(i, j);
      auto tile_text = std::make_shared<String>(tile->IsSet()? std::to_string(tile->value()) : " ", char_map_, font_scale_);
      tile_text->MoveTo(pos.x, pos.y);
      tile_text->Center();
      tiles_.Set(i, j, GameTile(
          tile,
          std::make_shared<Square>(pos.x, pos.y, fill_factor_*square_width, square_tex_, square_shader_),
          tile_text
      ));
      // Retrieve the just-constructed tile fron the tiles grid, add square and string to Renderer
      // static_pointer_cast<T>() is needed since renderer expects pointer to Drawable<GLFWwindow>
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(tiles_.Get(i, j).square()));
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(tiles_.Get(i, j).string()));
    }
  }
  // highlight the current tile and the reachable tiles
  const auto cur_tile_coords = rules_.current_tile()->coordinates();
  tiles_.Get(cur_tile_coords.first, cur_tile_coords.second).CurrentHighlight();
  for (const auto& t: rules_.current_tile()->reachables()) {
    if (!t->IsSet()) {
      const auto coordinates = t->coordinates();
      tiles_.Get(coordinates.first, coordinates.second).ReachableHighlight();
    }
  }

}

void Game::RenderLoop() const {
  renderer_.Loop();
}

inp::Position<double> Game::GridToScreen(const std::pair<size_t, size_t> &pos) const {
  const double square_width = 2.0/rules_.board().side();
  const double x = square_width*(pos.second + 0.5) - 1.0;
  const double y = square_width*(rules_.board().side() - pos.first - 0.5) - 1.0;
  return inp::Position<double>{x, y};
}

std::pair<size_t, size_t> Game::ScreenToGrid(const inp::Position<double> &pos) const {
  const double width = 2.0/rules_.board().side();
  const double j = ((pos.x + 1.0)/width - 0.5);
  const double i = (rules_.board().side() - 0.5 - (pos.y + 1.0)/width);
  const auto row = static_cast<size_t>(std::round(i));
  const auto col = static_cast<size_t>(std::round(j));
  return std::make_pair(row, col);
}

// this should probably be refactored into an Update() method or something
void Game::ProcessMouseClick() {
  // get the grid coordinates of the mouse click
  const auto coords = ScreenToGrid(mouse_.GetPosition());
  // check if the cicked tile is reachable
  for (const auto& t: rules_.current_tile()->reachables()) {
    if (coords == t->coordinates() && !t->IsSet()) {
      // if the tile is reachable, preserve the current state for undo
      // reset highlight on the currently highlighted tiles
      for (auto& r: rules_.current_tile()->reachables()) {
        size_t x, y;
        std::tie(x, y) = r->coordinates();
        tiles_.Get(x, y).ResetHighlight();
      }
      auto cur_coords = rules_.current_tile()->coordinates();
      tiles_.Get(cur_coords.first, cur_coords.second).ResetHighlight();
      // move to the new tile
      rules_.MoveTo(coords.first, coords.second);
      // retrieve current tile, set highlight and text
      auto tile = tiles_.Get(coords.first, coords.second);
      tile.SetText(String(
          std::to_string(rules_.current_tile()->value()),
          char_map_,
          font_scale_
      ));
      tile.CurrentHighlight();
      // highlight reachable tiles
      for (const auto& new_t: rules_.current_tile()->reachables()) {
        auto new_coords = new_t->coordinates();
        auto new_tile = tiles_.Get(new_coords.first, new_coords.second);
        if (!new_tile.tile()->IsSet()) {
          new_tile.ReachableHighlight();
        }
      }
      return;
    }
  }
}

void Game::ColorPath() {
  const auto side = rules_.board().side();
  const auto current_value = rules_.current_tile()->value();
  // filter set tiles from the board
  std::vector<GameTile> set_tiles;
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      auto tile = tiles_.Get(i, j);
      if (tile.tile()->IsSet()) {
        set_tiles.push_back(tile);
      } else {
        tile.square()->Color(Color{1.0, 0.0, 0.0});
      }
    }
  }
  constexpr float color_offset = 0.1;
  for (auto& t: set_tiles) {
    float c = color_offset + (1.0 - color_offset)*(t.tile()->value() - 1)/(current_value - 1);
    t.square()->Color(Color{c, c, c});
  }
}

} // namespace pie
