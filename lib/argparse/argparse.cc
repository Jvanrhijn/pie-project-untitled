//
// Created by jesse on 11/18/18.
//
#include "argparse.h"

#include <iostream>

namespace pie {

ArgParser::ArgParser(int argc, char **argv) {
  for (int i=1; i<argc-1; i++) { // skip program name, handle last argument separately
    std::string arg{argv[i]};
    if (arg[0] == '-') {
      auto arg_name = NameFromArg(arg);
      if (argv[i+1][0] == '-') {
        args_.insert(std::make_pair(arg_name, "true"));
      } else {
        args_.insert(std::make_pair(arg_name, std::string(argv[i+1])));
      }
    }
  }
  auto last_arg = std::string(argv[argc-1]);
  if (argv[argc-1][0] == '-') {
    args_.insert(std::make_pair(NameFromArg(last_arg), std::string("true")));
  }
}

std::string ArgParser::NameFromArg(const std::string &arg) {
  if (arg[0] == '-' && arg[1] == '-') {
    return arg.substr(2);
  } else if (arg[0] == '-') {
    return arg.substr(1);
  } else {
    return arg;
  }
}

} // namespace pie

