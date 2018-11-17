//
// Created by jesse on 11/15/18.
//

#include "src/game.h"

namespace pie {

Game::Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width, std::size_t height)
  : renderer_(width, height),
    mouse_(renderer_.window()),
    square_tex_(square_texture_path_),
    square_vs_(square_vs_path_),
    square_fs_(square_fs_path_),
    square_shader_(square_vs_, square_fs_),
    char_map_(getCharMap(font_path_, font_size_, Color{0.0, 0.0, 0.0})),
    rules_(side, start_x, start_y),
    tiles_(side, side)
{
  // Improvement: make GameTile drawable, avoid need to retrieve
  // Tile from board?
  const double square_width = 2.0/side;
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      double x = square_width*(j + 0.5) - 1.0;
      double y = square_width*(rules_.board().side() - i - 0.5) - 1.0;
      tiles_.Set(i, j, GameTile(
          rules_.board().GetTile(i, j),
          std::make_shared<Square>(x, y, fill_factor_*square_width, square_tex_, square_shader_),
          std::make_shared<String>("", char_map_, 1.5f)
      ));
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(tiles_.Get(i, j).square()));
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(tiles_.Get(i, j).string()));
    }
  }
  // Initialize game rules, set text and highlight for starting tile
  const auto start_coords = rules_.current_tile()->coordinates();
  auto start_tile = tiles_.Get(start_coords.first, start_coords.second);
  start_tile.SetText(
      String(std::to_string(rules_.current_tile()->value()), char_map_, 1.5f)
  );
  start_tile.CurrentHighlight();
  for (const auto& t: rules_.current_tile()->reachables()) {
    if (!t->IsSet()) {
      auto coordinates = t->coordinates();
      tiles_.Get(coordinates.first, coordinates.second).Highlight();
    }
  }
  glfwSetWindowUserPointer(renderer_.window(), this);
  mouse_.SetClickCallback([](GLFWwindow *w, int b, int a, int) {
    if (b == GLFW_MOUSE_BUTTON_LEFT && a == GLFW_PRESS) {
      auto game = static_cast<decltype(this)>(glfwGetWindowUserPointer(w));
      game->ProcessMouseClick();
    }
  });
}

void Game::RenderLoop() const {
  renderer_.Loop();
}

inp::Position<double> Game::GridToScreen(const std::pair<size_t, size_t> &pos) const {
  double square_width = 2.0/rules_.board().side();
  double x = square_width*(pos.second + 0.5) - 1.0;
  double y = square_width*(rules_.board().side() - pos.first - 0.5) - 1.0;
  return inp::Position<double>{x, y};
}

std::pair<size_t, size_t> Game::ScreenToGrid(const inp::Position<double> &pos) const {
  const double width = 2.0/rules_.board().side();
  double j = ((pos.x + 1.0)/width - 0.5);
  double i = (rules_.board().side() - 0.5 - (pos.y + 1.0)/width);
  auto row = static_cast<size_t>(std::round(i));
  auto col = static_cast<size_t>(std::round(j));
  return std::make_pair(row, col);
}

// this makes me want to kill myself but ok
void Game::ProcessMouseClick() {
  // get the grid coordinates of the mouse click
  auto coords = ScreenToGrid(mouse_.GetPosition());
  // check if the cicked tile is reachable
  for (const auto& t: rules_.current_tile()->reachables()) {
    if (coords == t->coordinates() && !t->IsSet()) {
      // if the tile is reachable, reset highlight on the currently highlighted tiles
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
          1.5f
      ));
      tile.CurrentHighlight();
      // highlight reachable tiles
      for (const auto& new_t: rules_.current_tile()->reachables()) {
        auto new_coords = new_t->coordinates();
        auto new_tile = tiles_.Get(new_coords.first, new_coords.second);
        if (!new_tile.tile()->IsSet()) {
          new_tile.Highlight();
        }
      }
      return;
    }
  }
}

} // namespace pie
