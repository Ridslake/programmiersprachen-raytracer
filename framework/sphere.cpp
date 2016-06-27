#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "sphere.hpp"
#define M_PI 3.14159265358979323846

//default constructor
Sphere::Sphere():
  Shape (std::string ("sphere"), {}),
  center ({0, 0, 0}),
  radius (0)
  {}

//custom contructor
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
glm::vec3& Sphere::get_spherecenter()
{
  return center;
}

  //volume
float Sphere::volume() const
{
  return (4/3*M_PI*radius*radius*radius);
}

  //area
float Sphere::area() const
{
  return (4*M_PI*radius*radius);
}

std::ostream& Sphere::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << mat << std::endl;
 os << radius << std::endl;
} 
  //5.6
bool Sphere::intersect(Ray const& ray, float distance)
{
  return  glm::intersectRaySphere(ray.origin, ray.direction, center, radius, 		  distance);
}
