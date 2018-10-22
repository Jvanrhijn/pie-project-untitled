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
   const char *what() const noexcept {
     return "Attempted value access on empty Optional";
   }

};

 //! Wrapper that may or may not contain a value (essentially a non-nullable type)
template<class T>
class Optional {
 public:
  Optional(T value)
  : value_(value), has_value_(true) {}

  //! Default constructor
  Optional()
  : has_value_(false) {}

  //! Value getter, throws on invalid access
  T value() const {
    if (!has_value_) {
      throw OptionalAccessException();
    }
    return value_;
  }

  //! Return internal flag, true if the value is set
  bool has_value() const {
    return has_value_;
  }

  //! Conversion operator to T
  operator T() const {
    if (!has_value_) {
      throw OptionalAccessException();
    }
    return value_;
  }

  //! Copy assignment operator
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
