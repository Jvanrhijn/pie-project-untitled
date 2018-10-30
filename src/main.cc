#include <iostream>
#include "lib/optional.h"
#include "lib/renderer/renderer.h"


int main() {
  pie::Renderer renderer(640, 480);
  renderer.Loop();
  return 0;
}

