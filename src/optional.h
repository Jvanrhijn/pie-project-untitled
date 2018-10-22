//
// Created by jesse on 10/22/18.
//

#ifndef __PIE_SRC_OPTIONAL_H
#define __PIE_SRC_OPTIONAL_H

#include <stdexcept>
#include <string>


namespace pie {

 class OptionalAccessException : public std::exception {
 public:
   const char *what() const throw() {
     return "Attempted value access on empty Optional";
   }

};

template<class T>
class Optional {
 public:
  Optional(T value)
  : value_(value), has_value_(true) {}

  Optional()
  : has_value_(false) {}

  T value() const {
    if (!has_value_) {
      throw OptionalAccessException();
    }
    return value_;
  }

  bool has_value() const {
    return has_value_;
  }

  operator T() const {
    if (!has_value_) {
      throw OptionalAccessException();
    }
    return value_;
  }

  Optional &operator=(T value) {
    value_ = value;
    has_value_ = true;
    return *this;
  }

 private:
  T value_;
  bool has_value_;

};

} // namespace pie


#endif // __PIE_SRC__OPTIONAL_H
