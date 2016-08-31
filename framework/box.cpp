#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <algorithm>

#include "box.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "color.hpp"

Box::Box():
  Shape (std::string ("box"), {}),
  min_ ({0, 0, 0}),
  max_ ({0, 0, 0})
  {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape(),
min_( ),
max_( )
{
  min_.x = std::min(min.x, max.x);
  min_.y = std::min(min.y, max.y);
  min_.z = std::min(min.z, max.z);
  max_.x = std::max(min.x, max.x);
  max_.y = std::max(min.y, max.y);
  max_.z = std::max(min.z, max.z);
}

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
        os << "min: ("<<min_.x
	<< ", "<<min_.y
  	<< ", "<<min_.z
	<< ") max: ("<<max_.x
	<< ", "<<max_.y
	<< ", "<<max_.z << ")\n";
}

Hit Box::intersect(Ray const& ray) {

  float t1 = (min_.x - ray.origin.x)*ray.inv_direction.x;
  float t2 = (max_.x - ray.origin.x)*ray.inv_direction.x;
  float tmin = std::min(t1, t2);
  float tmax = std::max(t1, t2);

  t1 = (min_.y - ray.origin.y)*ray.inv_direction.y;
  t2 = (max_.y - ray.origin.y)*ray.inv_direction.y;
  tmin = std::max(tmin, std::min(t1, t2));
  tmax = std::min(tmax, std::max(t1, t2));

  t1 = (min_.z - ray.origin.z)*ray.inv_direction.z;
  t2 = (max_.z - ray.origin.z)*ray.inv_direction.z;
  tmin = std::max(tmin, std::min(t1, t2));
  tmax = std::min(tmax, std::max(t1, t2));

  // r.dir is unit direction vector of ray
  // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
  // r.org is origin of ray
  /*float t1 = (min_.x - ray.origin.x)*ray.inv_direction.x;
    float t2 = (max_.x - ray.origin.x)*ray.inv_direction.x;

    float t3 = (min_.y - ray.origin.y)*ray.inv_direction.y;
    float t4 = (max_.y - ray.origin.y)*ray.inv_direction.y;
    float t5 = (min_.z - ray.origin.z)*ray.inv_direction.z;
    float t6 = (max_.z - ray.origin.z)*ray.inv_direction.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));*/

  // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
  Hit b_hit;

  if (tmax > std::max(0.0f, tmin)) {
    b_hit.hit_ = true;
    b_hit.sptr_ = this;

    b_hit.distance_ = sqrt(tmin * tmin *
                         (ray.direction.x * ray.direction.x +
                          ray.direction.y * ray.direction.y +
                          ray.direction.z * ray.direction.z)
                        );

    b_hit.target_ = glm::vec3{
        ray.origin.x + tmin * ray.direction.x,
        ray.origin.y + tmin * ray.direction.y,
        ray.origin.z + tmin * ray.direction.z
    };

    glm::vec3 normal{
      std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::infinity()
    };

    float bias = 0.00009f;
    //getting the normal vec on the side of the intersection

    //std::cout << b_hit.target_.x << " " << b_hit.target_.y << " " << b_hit.target_.z << std::endl;

    if ((max_.x - b_hit.target_.x < bias) && (max_.x - b_hit.target_.x> -bias)) {
        normal = glm::vec3{1.0, 0.0, 0.0};
    }
    else if ((min_.x - b_hit.target_.x < bias) && (min_.x - b_hit.target_.x> -bias)) {
        normal = glm::vec3{-1.0, 0.0, 0.0};
        //std::cout << "ere we go! minx:" << min_.x << "targetx" <<abs(b_hit.target_.x) << "\n";
    }
    else if ((max_.y - b_hit.target_.y < bias) && (max_.y - b_hit.target_.y> -bias)) {
        normal = glm::vec3{0.0, 1.0, 0.0};
        //std::cout <<"ere we go" <<abs(abs(max_.y) - abs(b_hit.target_.y)) << "\n";
    }
    else if ((min_.y - b_hit.target_.y < bias) && (min_.y - b_hit.target_.y> -bias)) {
        normal = glm::vec3{0.0, -1.0, 0.0};
    }
    else if ((max_.z - b_hit.target_.z < bias) && (max_.z - b_hit.target_.z> -bias)) {
        normal = glm::vec3{0.0, 0.0, 1.0};
    }
    else if ((min_.z - b_hit.target_.z < bias) && (min_.z - b_hit.target_.z> -bias)) {
        normal = glm::vec3{0.0, 0.0, -1.0};
    }
    b_hit.normal_ = normal;

    // std::cout << "INTERSECT IS GOING ON: \n";
    // std::cout << b_hit.intersection_.x << std::endl;
    // std::cout << max_.x << std::endl;
    // std::cout << min_.x << std::endl;
    // std::cout << b_hit.intersection_.y << std::endl;
    // std::cout << max_.y << std::endl;
    // std::cout << min_.y << std::endl;
    // std::cout << b_hit.intersection_.z << std::endl;
    // std::cout << max_.z << std::endl;
    // std::cout << min_.z << std::endl;

  }

  return b_hit;
}
