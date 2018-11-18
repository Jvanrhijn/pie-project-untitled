//
// Created by jesse on 11/15/18.
//

#ifndef __PIE_SRC_GAME_H
#define __PIE_SRC_GAME_H

#include <cstddef>

#include "src/game_tile.h"

#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/text/string.h"

#include "lib/input/input.h"

#include "lib/game/rules.h"

#include "lib/grid.h"


namespace pie {

class Game {
 public:
  Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width);
  Game(std::size_t width, const Rules& rules);

  //! Start the game loop
  void RenderLoop() const;

 private:
  //! Initialize the game board from the state of the rules object
  void SetupBoard();

  //! Convert grid indices to screen-space coordinates
  inp::Position<double> GridToScreen(const std::pair<size_t, size_t> &pos) const;

  //! Convert screen space coordinates to grid indices
  std::pair<size_t, size_t> ScreenToGrid(const inp::Position<double> &pos) const;

  //! Perform the actions required when clicking on the grid
  void ProcessMouseClick();

 private:
  // constants
  static constexpr size_t font_size_{96};
  static constexpr double fill_factor_{1.0};
  static constexpr char const *square_texture_path_{"textures/wrinkled_graph.jpg"};
  static constexpr char const *square_vs_path_{"lib/renderer/shaders/square.vs"};
  static constexpr char const *square_fs_path_{"lib/renderer/shaders/square.fs"};
  static constexpr char const *font_path_{"lib/renderer/fonts/josh.ttf"};

  Renderer renderer_;
  inp::Mouse mouse_;

  Texture square_tex_;

  Shader<GL_VERTEX_SHADER> square_vs_;
  Shader<GL_FRAGMENT_SHADER> square_fs_;
  VFShader square_shader_;

  charmap char_map_;

  Rules rules_;
  Grid<GameTile> tiles_;

  float font_scale_;

};

} // namespace pie

#endif // __PIE_SRC_GAME_H
