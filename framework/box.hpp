#ifndef BOX_HPP
#define BOX_HPP

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape
{
public:
//d
  Box();

  Box(glm::vec3 const& min, glm::vec3 const& max);

//c
  Box(std::string const&, Material const&, glm::vec3 const&, glm::vec3 const&);
//const& points directly at the object, no copy!

//getter
Hit intersect(Ray const& ray) override;
glm::vec3 const& min() const;
glm::vec3 const& max() const;
std::ostream& print(std::ostream& os) const override;

private:
//variablen
  glm::vec3 min_;
  glm::vec3 max_;
};

#endif //#define BOX_HPP
