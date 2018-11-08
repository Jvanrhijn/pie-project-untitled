#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/drawable.h"
#include "lib/renderer/texture.h"

using namespace pie;


template<class SP>
void grid(int num_per_side, const Texture &tex, const SP &shader, Renderer &renderer) {
  double width = 2.0/num_per_side;
  for (int i=0; i<num_per_side; i++) {
    for (int j=0; j<num_per_side; j++) {
      double x = width*(j + 0.5) - 1.0;
      double y = width*(i + 0.5) - 1.0;
      std::shared_ptr<Drawable<GLFWwindow>> object = std::make_shared<Square>(x, y, 0.4*width, tex, shader);
      renderer.AddObject(object);
    }
  }
}


int main() {
  Renderer renderer(900, 900);

  Texture marble("textures/marble.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/vertex_shader_test.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/fragment_shader_test.fs");
  ShaderPipeline<decltype(vertex_shader), decltype(fragment_shader)> square_shader(vertex_shader, fragment_shader);

  grid(4, marble, square_shader, renderer);

  renderer.Loop();

  return EXIT_SUCCESS;
}

