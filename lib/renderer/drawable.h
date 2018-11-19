//
// Created by jesse on 10/30/18.
//

#ifndef __PIE_LIB_DRAW_DRAWABLE_H
#define __PIE_LIB_DRAW_DRAWABLE_H

#include <utility>

namespace pie {

/**
 * @brief Interface for objects that can be drawn to the screen.
 */
template<class Window>
class Drawable {
 public:
  Drawable(float x, float y) : angle_(0.0f), location_(x, y) {}
  virtual ~Drawable() = default;

  //! Draw object to the window
  virtual void Draw(Window*) const = 0;

  //! Rotate object counterclockwise by angle
  virtual void Rotate(float angle) {
    angle_ += angle;
  }

  //! Move object to (x, y) in screen space coordinates
  virtual void MoveTo(float x, float y) {
    location_.first = x;
    location_.second = y;
  }

  //! Move object from current position (x, y) to (x + dx, y + dy)
  virtual void MoveAlong(float dx, float dy) {
    location_.first += dx;
    location_.second += dy;
  }

  long stride() const {
    return stride_;
  }

  long vertex_offset() const {
    return vertex_offset_;
  }

  long color_offset() const {
    return color_offset_;
  }

  long texture_offset() const {
    return texture_offset_;
  }

 protected:
  // Offsets and stride for vertex buffer data (see OpenGL docs for more information)
  static constexpr long vertex_offset_{sizeof(float)*0};
  static constexpr long color_offset_{sizeof(float)*3};
  static constexpr long texture_offset_{sizeof(float)*6};
  static constexpr long stride_{sizeof(float)*8};

  float angle_;
  std::pair<float, float> location_;

};

} // namespace pie

#endif // __PIE_LIB_DRAWABLE_H
