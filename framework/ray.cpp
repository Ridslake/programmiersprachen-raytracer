#include "ray.hpp"

//default
Ray::Ray():
  origin {0, 0, 0},
  direction {0, 0, 0}
  {}

//custom
Ray::Ray(glm::vec3 const& origin, glm::vec3 const& direction):
  origin {origin},
  direction {direction}
  {}


