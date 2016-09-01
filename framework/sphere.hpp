#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"


class Sphere : public Shape
{
public:
//d
  Sphere();

//c
  Sphere(std::string const&, Material const&, glm::vec3 const&, float);


//getter
float get_sphereradius() const;
glm::vec3 const& get_spherecenter() const;
std::ostream& print(std::ostream& os) const override;
Hit intersect(Ray const& ray) override;

private:
//variablen
  float radius;
  glm::vec3 center;

};
#endif //#define SPHERE_HPP
