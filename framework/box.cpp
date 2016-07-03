#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>

#include "box.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "color.hpp"

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
  //intersect
bool Box::intersect (Ray const& ray, float& distance){
	float tnear,tfar;
	float tnear_x,tnear_y,tnear_z;
	distance = -1;

	if (ray.direction.x != 0.0)
	{
		float t0 = (min.x - ray.origin.x) / ray.direction.x;
		float t1 = (max.x - ray.origin.x) / ray.direction.x;
		tnear_x = std::min(t0, t1);
		tfar = std::max(t0,t1);
		tnear = std::min(t0,t1);
	}
	else 
	{
		if(min.x > ray.origin.x || max.x < ray.origin.x) {return false;}
	}

	if (ray.direction.y != 0.0)
	{
		float t0 = (min.y - ray.origin.y) / ray.direction.y;
		float t1 = (max.y - ray.origin.y) / ray.direction.y;
		tnear_y = std::min(t0, t1);
		float tnear = std::max(tnear, std::min(t0,t1));
		float tfar = std::min(tfar, std::max(t0,t1));
		if (tnear > tfar)
		{
			return false;
		}
	}
	else 
	{
		if(min.y > ray.origin.y || max.y < ray.origin.y) {return false;}
	}

	if (ray.direction.z != 0.0)
	{
		float t0 = (min.z - ray.origin.z) / ray.direction.z;
		float t1 = (max.z - ray.origin.z) / ray.direction.z;
		tnear_z = std::min(t0, t1);
		tnear = std::max(tnear, std::min(t0,t1));
		tfar = std::min(tfar, std::max(t0,t1));
		if (tnear > tfar)
		{
			return false;
		}
	}
	else 
	{
		if(min.z > ray.origin.z || max.z < ray.origin.z) {return false;}
	}


	distance = tnear*sqrt(ray.direction.x*ray.direction.x +
					      ray.direction.y*ray.direction.y +
					      ray.direction.z*ray.direction.z);
	return true;
}


std::ostream& Box::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << mat << std::endl;
} 
