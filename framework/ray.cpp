#include "ray.hpp"

//d
Ray::Ray():
  origin ({0, 0, 0}),
  direction ({0, 0, 0}),
  inv_direction ({-0,-0,-0})
  {}

//c
Ray::Ray(glm::vec3 const& origin, glm::vec3 const& direction):
  origin (origin),
  direction (direction),
  inv_direction ({1.0/direction.x, 1.0/direction.y, 1.0/direction.z})
  {}
//Ueberpruefen
std::ostream& operator<<(std::ostream& os, Ray const& ray)
{
  os << "Ray: " << std::endl << "Origin: ("
  << ray.origin.x << ","
  << ray.origin.y << ","
  << ray.origin.z << ") \n"
  << "Direction: ("
  << ray.direction.x << ","
  << ray.direction.y << ","
  << ray.direction.z << ") \n";
}

