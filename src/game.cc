//
// Created by jesse on 11/15/18.
//

#include "src/game.h"

namespace pie {

Game::Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width, std::size_t height)
  : renderer_(width, height),
    mouse_(renderer_.window()),
    square_tex_("textures/marble.jpg"),
    square_vs_("lib/renderer/shaders/square.vs"),
    square_fs_("lib/renderer/shaders/square.fs"),
    square_shader_(square_vs_, square_fs_),
    char_map_(getCharMap("lib/renderer/fonts/arial.ttf", font_size, Color{0.0, 0.0, 0.0})),
    rules_(side, start_x, start_y),
    squares_(side, side),
    text_(side, side)
{
  // setup shaders and textures for Square
  // build charmap
  // setup grids of squares and text
  double square_width = 2.0/side;
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      double x = square_width*(j + 0.5) - 1.0;
      double y = square_width*(rules_.board().side() - i - 0.5) - 1.0;
      squares_.Set(i, j, std::make_shared<Square>(x, y, fill_factor*square_width, square_tex_, square_shader_));
      text_.Set(i, j, std::make_shared<String>("", char_map_, 1.5f));
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(squares_.Get(i, j)));
      renderer_.AddObject(std::static_pointer_cast<Drawable<GLFWwindow>>(text_.Get(i, j)));
    }
  }
  // Initialize game rules, set text to render for starting tile
  auto start_coords = rules_.current_tile()->coordinates();
  auto start_pos = GridToScreen(start_coords);
  size_t start_val = rules_.current_tile()->value().value();
  auto start_text = text_.Get(start_coords.first, start_coords.second);
  *start_text = String(std::to_string(rules_.current_tile()->value()), char_map_, 1.5f);
  start_text->MoveTo(start_pos.x, start_pos.y);
  for (const auto& t: rules_.current_tile()->reachables()) {
    auto coordinates = t->coordinates();
    if (!t->IsSet()) {
      squares_.Get(coordinates.first, coordinates.second)->Color(Color{0.0, 1.0, 0.0});
    }
  }
  // TODO: initialize mouse callback
  // TODO: dispatch game loop thread
}

void Game::RenderLoop() const {
  renderer_.Loop();
}

inp::Position<double> Game::GridToScreen(const std::pair<size_t, size_t> &pos) const {
  double square_width = fill_factor*2.0/rules_.board().side();
  double x = square_width*(pos.second + 0.5) - 1.0;
  double y = square_width*(rules_.board().side() - pos.first - 0.5) - 1.0;
  return inp::Position<double>{x, y};
}

} // namespace pie
