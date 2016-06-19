#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"

class Sphere : public Shape
{
public:
//default Constructor
  Sphere();

//custom constructor
  Sphere(std::string const&, Color const&, glm::vec3 const&, float);

//destructor
  ~Sphere();
//getter
float get_sphereradius() const;
glm::vec3& get_spherecenter();

float volume() const override;
float area() const override;
std::ostream& print(std::ostream& os) const override;

//5.6 intersect
bool intersect(Ray const& ray, float distance);

//float get_spherediameter() const;
//float get_spherecircumference() const;

//setter
//float set_sphereradius(float nradius);
//glm::vec3 set_spherecenter(glm::vec3 center)

private:
//variablen
  float radius;
  glm::vec3 center;

};
#endif //#define SPHERE_HPP
