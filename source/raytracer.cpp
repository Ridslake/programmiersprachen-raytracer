#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>

#include "scene.hpp"
#include "sdfloader.cpp"

int main(int argc, char* argv[])
{


  if (argc !=2){
    std::cout << "Benutze: raytracer filename.sdf \n";

    return 1;




  };

  Scene scene = load_sdf_file(argv[1]);

  Renderer r1{scene};

  r1.render();



  return 0;
}
