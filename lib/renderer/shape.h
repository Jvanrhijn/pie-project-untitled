//
// Created by jesse on 10/31/18.
//

#ifndef __PIE_LIB_RENDER_SHAPE_H
#define __PIE_LIB_RENDER_SHAPE_H

#include <utility>

#include "lib/draw/drawable.h"

namespace pie {

class Shape {
 public:
  Shape(double x, double y);
  virtual ~Shape() = default;

 private:
  std::pair<double, double> location_;
};

} // namespace pie

#endif // __PIE_LIB_RENDER_SHAPE_H
