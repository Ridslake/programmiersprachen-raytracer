#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "hit.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"

class Shape
{
public:
  
  virtual Hit intersect(Ray const& ray) = 0;
  virtual std::ostream& print(std::ostream&) const;

//getter
  std::string getname() const;
  Material get_material() const;

  std::string name_;
  Material mat;

protected:
  Shape();
  Shape(std::string const& name, Material const& mat_);

};

std::ostream& operator <<(std::ostream&, Shape const&);

#endif //#define SHAPE_HPP
