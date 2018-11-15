//
// Created by jesse on 11/15/18.
//

#include "src/game.h"

namespace pie {

Game::Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width, std::size_t height)
  : renderer_(width, height), mouse_(renderer_.window()), board_(side), squares_(side, side), text_(side, side)
{
  // setup shaders and textures for Square
  Texture square_texture("textures/marble.jpg");
  Shader<GL_VERTEX_SHADER> square_vs("lib/renderer/shaders/square.vs");
  Shader<GL_FRAGMENT_SHADER> square_fs("lib/renderer/shaders/square.fs");
  VFShader square_shader(square_vs, square_fs);
  // build charmap
  auto char_map = getCharMap("lib/renderer/fonts/arial.ttf", font_size, Color{0.0, 0.0, 0.0});
  // setup grids of squares and text
  double square_width = fill_factor*2.0/side;
  for (size_t i=0; i<side; i++) {
    for (size_t j=0; j<side; j++) {
      double x = square_width*(j + 0.5) - 1.0;
      double y = square_width*(i + 0.5) - 1.0;
      squares_.Set(i, j, std::make_shared<Square>(x, y, square_width, square_texture, square_shader));
      text_.Set(i, j, std::make_shared<String>("", char_map, 1.5f));
    }
  }
  // TODO: initialize mouse callback

  // TODO: build grid of drawable tiles
  // TODO: set text to render
  // TODO: dispatch game loop thread
}

} // namespace pie
