#include "lib/renderer/renderer.h"
#include "lib/renderer/square.h"
#include "lib/renderer/drawable.h"
#include "lib/renderer/texture.h"
#include "lib/renderer/character.h"

#include <map>
#include <thread>

using namespace pie;


template<class SP>
void grid(int num_per_side, const Texture &tex, const SP &shader, Renderer &renderer) {
  double width = 2.0/num_per_side;
  for (int i=0; i<num_per_side; i++) {
    for (int j=0; j<num_per_side; j++) {
      double x = width*(j + 0.5) - 1.0;
      double y = width*(i + 0.5) - 1.0;
      std::shared_ptr<Drawable<GLFWwindow>> object = std::make_shared<Square>(x, y, 0.9*width, tex, shader);
      renderer.AddObject(object);
    }
  }
}


int main() {
  Renderer renderer(900, 900);

  Texture marble("textures/marble.jpg");

  Shader<GL_VERTEX_SHADER> vertex_shader("lib/renderer/shaders/vertex_shader_test.vs");
  Shader<GL_FRAGMENT_SHADER> fragment_shader("lib/renderer/shaders/fragment_shader_test.fs");
  VFShader square_shader(vertex_shader, fragment_shader);


  // construct charmap
  FontFace face("lib/renderer/fonts/arial.ttf", 48);
  Shader<GL_VERTEX_SHADER> vs("lib/renderer/shaders/text.vs");
  Shader<GL_FRAGMENT_SHADER> fs("lib/renderer/shaders/text.fs");
  VFShader shader(vs, fs);
  Color col{0.0, 0.0, 0.0};

  std::map<GLchar, std::shared_ptr<Drawable<GLFWwindow>>> arial_char_map;
  for (GLubyte c=0; c<128; c++) {
    std::shared_ptr<Drawable<GLFWwindow>> character  = std::make_shared<Character>(face, c, col, shader);
    arial_char_map.insert(std::make_pair(c, character));
  }

  //std::shared_ptr<Drawable<GLFWwindow>> tile = std::make_shared<Square>(0.0, 0.0, 0.5, marble, square_shader);
  //renderer.AddObject(tile);
  grid(3, marble, square_shader, renderer);

  renderer.AddObject(arial_char_map['B']);

  renderer.Loop();

  return EXIT_SUCCESS;
}

