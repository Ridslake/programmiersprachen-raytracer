#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

struct Material
{
  Material(); //def
  
  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float const& m); //cus

  std::ostream& print(std::ostream& os) const;

//Variablen
  std::string name;
  Color ka;
  Color kd;
  Color ks;
  float m;

};

std::ostream& operator <<(std::ostream& os, Material const& mat); //streamop <<

#endif
