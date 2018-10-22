#include <iostream>
#include "optional.h"


int main(int argc, char *argv[]) {
  pie::Optional<char> a;
  if (a.has_value()) {
    std::cout << a.value() << std::endl;
  }
  return 0;
}



