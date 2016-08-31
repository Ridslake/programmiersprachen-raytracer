#ifndef SCENE_HPP
#define SCENE_HPP
#include <map>
#include <vector>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "light.hpp"
#include "shape.hpp"
#include "material.hpp"

struct Scene
{
  std::string filename;
  float yres_ = 0.0;
  float xres_ = 0.0;
  Camera camera;
  std::map<std::string,Material> materials;	
  std::vector<std::shared_ptr<Shape>> shapes_ptr;
  std::vector<Light> lights;
  std::map<std::string, std::vector<std::shared_ptr<Shape>>> composites;
  Color amblight;
  Color background;
};

#endif //#define SHAPE_HPP
