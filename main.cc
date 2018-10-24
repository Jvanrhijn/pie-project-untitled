#include <iostream>
#include "lib/optional.h"


int main(int argc, char *argv[]) {
  pie::Optional<int> a = 1;
  std::cout << a.value() << std::endl;
  return 0;
}



