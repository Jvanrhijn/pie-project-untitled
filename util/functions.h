//
// Created by jesse on 10/26/18.
//

#ifndef __PIE_UTIL_FUNCTIONS_H
#define __PIE_UTIL_FUNCTIONS_H

#include <algorithm>

namespace pie {

template<class Container, class T>
bool contains(const Container& container, const T& element) {
  return std::find(container.begin(), container.end(), element) != container.end();
}

}

#endif //__PIE_UTIL_FUNCTIONS_H
