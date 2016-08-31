#ifndef HIT_HPP
#define HIT_HPP
#include <glm/vec3.hpp>
#include <memory>
#include "ray.hpp"
//#include "shape.hpp"

class Shape;

struct Hit
{
  Hit();
  Hit(bool hit, float dis, glm::vec3 const& target,
      glm::vec3 const& norm, Shape* sptr);

  //Hit& operator=(Hit const& hit);
  bool operator==(Hit const& hit2) const;

  friend std::ostream& operator<<(std::ostream& os, Hit const& hit);

  bool hit_;
  float distance_;
  glm::vec3 target_;
  glm::vec3 normal_; //Normalenvektor am Schnittpunkt
  Shape* sptr_;
};

#endif	//HIT_HPP
