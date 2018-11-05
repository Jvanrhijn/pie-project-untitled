//
// Created by jesse on 10/31/18.
//

#ifndef __PIE_LIB_RENDER_SHAPE_H
#define __PIE_LIB_RENDER_SHAPE_H

#include <utility>

#include "lib/draw/drawable.h"

namespace pie {

/**
 * @brief Object for creating shape-type objects to render, meant to be inherited from (e.g. for Square)
 */
class Shape {
 public:
  Shape(double x, double y);
  virtual ~Shape() = default;

 protected:
  std::pair<double, double> location_;
};

} // namespace pie

#endif // __PIE_LIB_RENDER_SHAPE_H
