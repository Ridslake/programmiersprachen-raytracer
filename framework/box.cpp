#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <algorithm>
#include <catch.hpp>

#include "box.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "color.hpp"


//Default Constructor
Box::Box():
  Shape (std::string ("box"), {}),
  min_ ({0.0f, 0.0f, 0.0f}),
  max_ ({0.0f, 0.0f, 0.0f})
  {}
//Custom 1
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape(),
min_( ),
max_( )
{//Min und Maxsseite, damit man weiß, was min und max ist
  min_.x = std::min(min.x, max.x);
  min_.y = std::min(min.y, max.y);
  min_.z = std::min(min.z, max.z);
  max_.x = std::max(min.x, max.x);
  max_.y = std::max(min.y, max.y);
  max_.z = std::max(min.z, max.z);
}
//Custom 2
Box::Box(std::string const& name_, Material const& mat, glm::vec3 const& min, glm::vec3 const& max):
  Shape(name_, mat),
  min_ ( ),
  max_ ( )
  {
  min_.x = std::min(min.x, max.x);
  min_.y = std::min(min.y, max.y);
  min_.z = std::min(min.z, max.z);
  max_.x = std::max(min.x, max.x);
  max_.y = std::max(min.y, max.y);
  max_.z = std::max(min.z, max.z);
  }

glm::vec3 const& Box::min() const
{
  return min_;
}

glm::vec3 const& Box::max() const
{
  return max_;
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
        os << "minimum: ("<<min_.x
	<< ", "<<min_.y
  	<< ", "<<min_.z
	<< ") maximum: ("<<max_.x
	<< ", "<<max_.y
	<< ", "<<max_.z << ")\n";
}

Hit Box::intersect(Ray const& ray) {
  //Wann trifft der Strahl auf die Box?
  //Minimum der Box - Rayorigin mal inverse Strahlrichtung
  float t1 = (min_.x - ray.origin.x)*ray.inv_direction.x;
  //Maximum der Box - Rayorigin mal inverse Strahlrichtung
  float t2 = (max_.x - ray.origin.x)*ray.inv_direction.x;
  float tmin = std::min(t1, t2);
  float tmax = std::max(t1, t2);

  t1 = (min_.y - ray.origin.y)*ray.inv_direction.y;
  t2 = (max_.y - ray.origin.y)*ray.inv_direction.y;

  //ermitteln minimum und maximum von t1 und t2 (2 float werte)
  tmin = std::max(tmin, std::min(t1, t2));
  tmax = std::min(tmax, std::max(t1, t2));

  t1 = (min_.z - ray.origin.z)*ray.inv_direction.z;
  t2 = (max_.z - ray.origin.z)*ray.inv_direction.z;
  tmin = std::max(tmin, std::min(t1, t2));
  tmax = std::min(tmax, std::max(t1, t2));

  //intersection (hit)
  Hit b_hit;

  if (tmax > std::max(0.0f, tmin))
  {
    //sptr = strong pointer zu this behält pointer wenn außerhalb der scope gebraucht
    b_hit.hit_ = true;
    b_hit.sptr_ = this;
    
    //Abstand zum Intersect
    b_hit.distance_ = sqrt(tmin * tmin *
                         (ray.direction.x * ray.direction.x +
                          ray.direction.y * ray.direction.y +
                          ray.direction.z * ray.direction.z));
    //Getroffener Punkt am Objekt
    b_hit.target_ = glm::vec3{
	ray.origin.x + tmin * ray.direction.x,
	ray.origin.y + tmin * ray.direction.y,
	ray.origin.z + tmin * ray.direction.z
    };
    glm::vec3 normal {};

    if (b_hit.target_.x == Approx(min_.x)) {normal = glm::vec3{1.0, 0.0, 0.0};}
    else if (b_hit.target_.x == Approx(max_.x)) {normal = glm::vec3{-1.0, 0.0, 0.0};}
    else if (b_hit.target_.y == Approx(min_.y)) {normal = glm::vec3{0.0, 1.0, 0.0};}
    else if (b_hit.target_.y == Approx(max_.y)) {normal = glm::vec3{0.0, -1.0, 0.0};}
    else if (b_hit.target_.z == Approx(min_.z)) {normal = glm::vec3{0.0, 0.0, 1.0};}
    else if (b_hit.target_.z == Approx(max_.z)) {normal = glm::vec3{0.0, 0.0, -1.0};}
    b_hit.normal_ = normal;
  }
  return b_hit;
}
