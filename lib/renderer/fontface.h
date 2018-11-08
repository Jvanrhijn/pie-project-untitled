//
// Created by jesse on 11/8/18.
//

#ifndef PIE_FONTFACE_H
#define PIE_FONTFACE_H

#include <string>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace pie {

class FontFace {
 public:
  FontFace(const std::string &path, size_t size);
  ~FontFace();

  void LoadChar(char c);

  const FT_Face& face() const;

 private:
  FT_Library ftlib_;
  FT_Face face_;


};

} // namespace pie

#endif //PIE_FONTFACE_H
