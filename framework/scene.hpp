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

struct Scene{
  std::string filename;
  Camera camera;

  float yresolution = 0.0;
  float xresolution = 0.0;

  std::map<std::string,Material> materials;	
  std::vector<std::shared_ptr<Shape>> shapes_ptr;
  std::vector<Light> lights;
  std::map<std::string, std::vector<std::shared_ptr<Shape>>> composites;

  Color amblight;
  Color background;
};

#endif
