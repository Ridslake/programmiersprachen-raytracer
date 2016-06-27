#include "box.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <shape.hpp>

Box::Box():
  Shape (std::string ("box"), {}),
  min ({0, 0, 0}),
  max ({0, 0, 0})
  {}

Box::Box(std::string const& name_, Material const& mat, glm::vec3 const& min, glm::vec3 const& max):
  Shape(name_, mat),
  min (min),
  max (max)
  {}

//getter
  //min
glm::vec3 Box::get_boxmin() const
{
  return min;
}

  //max
glm::vec3 Box::get_boxmax() const
{
  return max;
}

  //volume
float Box::volume() const
{
	float x = abs(max.x - min.x);
	float y = abs(max.y - min.y);
	float z = abs(max.z - min.z);

	return x*y*z;
}

  //area
float Box::area() const
{
	float x = abs(max.x - min.x);
	float y = abs(max.y - min.y);
	float z = abs(max.z - min.z);

	return 2*(x*y + x*z + y*z);
}

std::ostream& Box::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << color_ << std::endl;
} 
