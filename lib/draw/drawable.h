//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_DRAWABLE_H
#define __PIE_LIB_DRAW_DRAWABLE_H

namespace pie {

/**
 * @brief Interface for objects that can be drawn to the screen.
 */
template<class Window>
class Drawable {
 public:
  virtual ~Drawable() = default;

  virtual void Draw(Window*) const = 0;
  
  virtual void Rotate(double angle) = 0;
  virtual void MoveTo(double x, double y) = 0;

};

} // namespace pie

#endif // __PIE_LIB_DRAWABLE_H
