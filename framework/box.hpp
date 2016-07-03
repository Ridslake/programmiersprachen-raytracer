#ifndef BOX_HPP
#define BOX_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"

class Box : public Shape
{
public:
//default constructor
  Box();

//custom contructor
  Box(std::string const&, Material const&, glm::vec3 const&, glm::vec3 const&); //const& points directly at the object, no copy!

//getter
glm::vec3 get_boxmin() const;
glm::vec3 get_boxmax() const;
float get_boxlength() const;
float get_boxwidth() const;
float get_boxheight() const;

float volume() const override;
float area() const override;
std::ostream& print(std::ostream& os) const override;
bool intersect (Ray const&, float&) override;

private:
//variablen
  glm::vec3 min;
  glm::vec3 max;
};

#endif //#define BOX_HPP
