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

  //! Draw object to the window
  virtual void Draw(Window*) const = 0;

  //! Rotate object counterclockwise by angle
  virtual void Rotate(float angle) = 0;

  //! Move object to (x, y) in screen space coordinates
  virtual void MoveTo(double x, double y) = 0;

  //! Move object from current position (x, y) to (x + dx, y + dy)
  virtual void MoveAlong(double dx, double dy) = 0;

  // Getters
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

};

} // namespace pie

#endif // __PIE_LIB_DRAWABLE_H
