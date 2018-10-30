//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_DRAWABLE_H
#define __PIE_LIB_DRAW_DRAWABLE_H

namespace pie {

/**
 * @brief Interface for objects that can be drawn to the screen.
 */
class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual void Draw() = 0;
};

} // namespace pie

#endif // __PIE_LIB_DRAWABLE_H
