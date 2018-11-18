//
// Created by jesse on 11/18/18.
//

#ifndef PIE_ARGPARSE_H
#define PIE_ARGPARSE_H

#include <map>
#include <string>
#include <type_traits>

#include "lib/optional.h"

namespace pie {

class ArgParser {
 public:
  ArgParser(int argc, char *argv[]);

  template<class T>
  T GetArg(const std::string &name, T def) const {
    auto value = args_.find(name);
    if (value != args_.end()) {
      if (SameTypes<T, bool>()) {
        return args_.at(name) == "true";
      } else if (SameTypes<T, int>()) {
        return std::stoi(args_.at(name));
      } else if (SameTypes<T, double>()) {
        return std::stod(args_.at(name));
      }
    }
    return def;
  }

 private:
  static std::string NameFromArg(const std::string &arg);

  template<class T, class U>
  static constexpr bool SameTypes() {
    return std::is_same<T, U>::value;
  }

 private:
  std::map<const std::string, std::string> args_;

};

} // namespace pie

#endif //PIE_ARGPARSE_H
