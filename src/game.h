//
// Created by jesse on 11/15/18.
//

#ifndef __PIE_SRC_GAME_H
#define __PIE_SRC_GAME_H

#include <cstddef>

#include "game_tile.h"

#include "renderer/renderer.h"
#include "renderer/square.h"
#include "renderer/text/string.h"

#include "input/input.h"

#include "game/rules.h"

#include "grid.h"


namespace pie {

class Game {
 public:
  Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width);
  Game(std::size_t width, const Rules& rules);

  //! Start the game loop
  void RenderLoop() const;

  //! Color the taken path with a gradient
  void ColorPath();

 private:
  //! Initialize the game board from the state of the rules object
  void SetupBoard();

  //! Reset state of the game
  void Reset();

  //! Convert grid indices to screen-space coordinates
  inp::Position<double> GridToScreen(const std::pair<size_t, size_t> &pos) const;

  //! Convert screen space coordinates to grid indices
  std::pair<size_t, size_t> ScreenToGrid(const inp::Position<double> &pos) const;

  //! Perform the actions required when clicking on the grid
  void ProcessMouseClick();
  
 private:
  // constants
  static constexpr float font_scale_factor_{1.2f};
  static constexpr size_t font_size_{96};
  static constexpr double fill_factor_{1.0};
  static constexpr char const *square_texture_path_{"assets/textures/graph.jpg"};
  static constexpr char const *square_vs_path_{"assets/shaders/square.vs"};
  static constexpr char const *square_fs_path_{"assets/shaders/square.fs"};
  static constexpr char const *font_path_{"assets/fonts/lemon.otf"};
  static constexpr Color text_color_{0.157, 0.259, 0.514};

  Renderer renderer_;
  inp::Mouse mouse_;

  Texture square_tex_;

  Shader<GL_VERTEX_SHADER> square_vs_;
  Shader<GL_FRAGMENT_SHADER> square_fs_;
  VFShader square_shader_;

  charmap char_map_;

  Rules rules_;
  Rules init_rules_;
  Grid<GameTile> tiles_;

  float font_scale_;

};

} // namespace pie

#endif // __PIE_SRC_GAME_H
