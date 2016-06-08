#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>

class Sphere
{
public:
//default Constructor
  Sphere();

//custom constructor
  Sphere(float radius);

//variablen
  float radius;

//getter
float get_spherediameter() const;
float get_spherecircumference89 const;
float get_sphereradius() const;
float get_spherevolume() const;

//setter
float set_sphereradius(float nradius);

};
#endif //#define SPHERE_HPP
