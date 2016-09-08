#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <cmath>
#include <iostream>

#include "scene.hpp"
#include "sdfloader.cpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
     std::cout << "usage: raytracer file.sdf\n";
     return 1;
  }
  for(int i = 0; i <= 20; i++)
  {
    std::string s = std::to_string(i);
    std::string bildname = argv[1] + s + ".ppm";
    std::string sdfname = argv[1];
    sdfname = sdfname + ".txt";
    
    std::fstream new_text;
    float zz = i*M_PI/180;
    float camx = sin(zz)*200;
    float camz = cos(zz)*200;
    new_text.open(sdfname, std::ios::out);

    new_text<<"define material red 1 0 0 1 0 0 1 0 0 1"<<std::endl;
    new_text<<"define material blue 0 0 1 0 0 1 0 0 1 1"<<std::endl;
    new_text<<"define material green 0.5 1 0.5 1 1 1 2 2 2 1"<<std::endl;
    new_text<<"define shape sphere kugel 0 0 0 25 green"<<std::endl;
    new_text<<"define shape sphere kugel1 -20 30 -10 5 blue"<<std::endl;
    new_text<<"define shape sphere kugel2 20 -30 10 10 red" <<std::endl;
    new_text<<"define shape box quader -10 20 25 0 25 30 red"<<std::endl;
    new_text<<"define light sonne 1000 700 500 0.2 0.2 0.2 0.8 0.8 0.8"<<std::endl;
    new_text<<"define camera kamera 45 "<< camx <<" 0 "<< camz <<" "<< -camx
    <<" 0 "<< -camz <<" 0 1 0"<<std::endl;
    new_text<<"define renderer "<< bildname <<" 500 500"<<std::endl;
  
  Scene scene = load_sdf_file(sdfname);

  std::string const filename = "./checkerboard.ppm";
  unsigned const width = scene.xresolution;
  unsigned const height = scene.yresolution;

  Renderer app(scene, 3);

  std::thread thr([&app]() { app.render(); });

  /*Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }*/

  thr.join();
  }
  return 0;
}
