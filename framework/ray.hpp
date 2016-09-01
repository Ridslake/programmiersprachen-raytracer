#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

struct Ray
{
//default
  Ray();

//custom
  Ray(glm::vec3 const&, glm::vec3 const&);

//os
  friend std::ostream& operator<<(std::ostream& os, Ray const& ray);

//Getter
  glm::vec3 getorigin() const {
	return origin;
	}

  Ray transformRay(glm::mat4 const& mat);

//variables
  glm::vec3 origin;
  glm::vec3 direction;
  glm::vec3 inv_direction;

};

Ray transformRay(glm::mat4 const& mat, Ray& ray);

#endif
