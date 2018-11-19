//
// Created by jesse on 11/10/18.
//
#include "lib/renderer/text/charmap.h"

namespace pie {

charmap getCharMap(const std::string &fontpath, size_t size, const Color &color) {
  FontFace face(fontpath, size);
  Shader<GL_VERTEX_SHADER> vs("lib/renderer/shaders/text.vs");
  Shader<GL_FRAGMENT_SHADER> fs("lib/renderer/shaders/text.fs");
  VFShader shader(vs, fs);

  charmap char_map;
  for (unsigned char c = 0; c < 128; c++) {
    Character character(face, c, color, shader);
    char_map.insert(std::make_pair(c, std::move(character)));
  }
  return char_map;
}

}