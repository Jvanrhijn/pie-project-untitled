//
// Created by jesse on 11/18/18.
//

#ifndef PIE_ARGPARSE_H
#define PIE_ARGPARSE_H

#include <map>
#include <string>
#include <type_traits>

#include "optional.h"

namespace pie {

class ArgParser {
 public:
  ArgParser(int argc, char *argv[]);

  int GetArg(const std::string &name, int def) const {
    auto value = args_.find(name);
    if (value != args_.end()) {
      return std::stoi(args_.at(name));
    }
    return def;
  }

  double GetArg(const std::string &name, double def) const {
    auto value = args_.find(name);
    if (value != args_.end()) {
      return std::stod(args_.at(name));
    }
    return def;
  }

  bool GetArg(const std::string &name, bool def) const {
    auto value = args_.find(name);
    if (value != args_.end()) {
      return args_.at(name) == "true";
    }
    return def;
  }

  const std::string& GetArg(const std::string &name, const std::string &def) const {
    auto value = args_.find(name);
    if (value != args_.end()) {
      return args_.at(name);
    }
    return def;
  }

 private:
  static std::string NameFromArg(const std::string &arg);

 private:
  std::map<const std::string, std::string> args_;

};

} // namespace pie

#endif //PIE_ARGPARSE_H
