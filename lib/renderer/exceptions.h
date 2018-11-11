//
// Created by jesse on 10/30/18.
//

#ifndef PIE_EXIT_CODES_H
#define PIE_EXIT_CODES_H

#include <string>
#include <exception>

namespace pie {

class RenderException : std::exception {
 public:
  explicit RenderException(const std::string& message) : message_(message) {}

  virtual const char *what() const noexcept {
    return message_.c_str();
  }

 private:
  std::string message_;

};

}

#endif //PIE_EXIT_CODES_H
