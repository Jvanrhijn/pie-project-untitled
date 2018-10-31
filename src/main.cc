#include <iostream>
#include "lib/optional.h"
#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/draw/drawable.h"

#include "lib/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "lib/linmath.h"
#include <stdlib.h>
#include <stdio.h>

using namespace pie;

int main() {
  Renderer renderer(1600, 900);
  Square square(0., 0., 1.);
  renderer.AddObject((std::shared_ptr<Drawable>(static_cast<Drawable*>(new Square(0., 0., 1.)))));
  renderer.Loop();
  return 0;
}

