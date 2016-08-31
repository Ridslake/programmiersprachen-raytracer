#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <cmath>

#include "hit.hpp"
#include "sphere.hpp"
#define M_PI 3.14159265358979323846

//d
Sphere::Sphere():
  Shape (std::string ("sphere"), {}),
  center ({0, 0, 0}),
  radius (0)
  {}

//c
Sphere::Sphere(std::string const& name_, Material const& mat, glm::vec3 const& center, float radius):
  Shape (name_, mat),
  center (center),
  radius (radius)
  {}

//destructor
Sphere::~Sphere()
{
  std::cout <<"destruct sphere"<<std::endl;
}
  

//getter
  //radius
float Sphere::get_sphereradius() const
{
  return radius;
}

  //center
glm::vec3 const& Sphere::get_spherecenter() const
{
  return center;
}

std::ostream& Sphere::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << mat << std::endl;
 os << radius << std::endl;
} 

Hit Sphere::intersect(Ray const& ray)
{
  Hit s_hit;

  s_hit.hit_ = glm::intersectRaySphere(
  ray.origin,
  glm::normalize(ray.direction),
  center, radius,
  s_hit.target_, s_hit.normal_
  );

  s_hit.distance_ = glm::distance(ray.origin, s_hit.target_);

  s_hit.sptr_ = this;

  return s_hit;
}
