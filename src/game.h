//
// Created by jesse on 11/15/18.
//

#ifndef __PIE_SRC_GAME_H
#define __PIE_SRC_GAME_H

#include <cstddef>

#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/text/string.h"

#include "lib/input/input.h"

#include "lib/game/rules.h"

#include "lib/grid.h"


namespace pie {

class Game {
 public:
  Game(std::size_t start_x, std::size_t start_y, std::size_t side, std::size_t width, std::size_t height);

  void RenderLoop() const;

 private:
  inp::Position<double> GridToScreen(const std::pair<size_t, size_t> &pos) const;

 private:
  static constexpr size_t font_size{48};
  static constexpr double fill_factor{0.95};

  Renderer renderer_;
  inp::Mouse mouse_;

  Texture square_tex_;

  Shader<GL_VERTEX_SHADER> square_vs_;
  Shader<GL_FRAGMENT_SHADER> square_fs_;
  VFShader square_shader_;

  charmap char_map_;

  Rules rules_;

  Grid<std::shared_ptr<Square>> squares_;
  Grid<std::shared_ptr<String>> text_;
};

} // namespace pie

#endif // __PIE_SRC_GAME_H
