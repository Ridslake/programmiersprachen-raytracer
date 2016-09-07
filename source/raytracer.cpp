#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>

#include "scene.hpp"
#include "sdfloader.cpp"

int main(int argc, char* argv[])
{
if (argc != 2) {
     std::cout << "usage: raytracer file.sdf\n";
     return 1;
  }

  Scene scene = load_sdf_file(argv[1]);

  std::string const filename = "./checkerboard.ppm";
  unsigned const width = scene.xresolution;
  unsigned const height = scene.yresolution;

  Renderer app(scene, 3);

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
