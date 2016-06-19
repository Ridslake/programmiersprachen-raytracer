#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct Ray
{
//default
  Ray();
//custom
  Ray(glm::vec3 const&, glm::vec3 const&);

//variables
  glm::vec3 origin;
  glm::vec3 direction;

};

#endif
