#include <limits>
#include "hit.hpp"
#include "shape.hpp"

Hit::Hit():
hit_{false},
distance_{std::numeric_limits<float>::infinity()},
target_{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()},
normal_{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()},
sptr_{nullptr} {}

Hit::Hit(bool hit, float dis, glm::vec3 const& intersection,
    glm::vec3 const& norm, Shape* sptr) :
hit_{hit},
distance_{dis},
target_{intersection},
normal_{norm},
sptr_{sptr} {}

/*Hit& Hit::operator=(Hit const& hit) {
    if (this == &hit) {
        return *this;
    }

    hit_ = hit.hit_;
    distance_ = hit.distance_;
    target_ = hit.target_;
    normal_ = hit.normal_;
    sptr_ = hit.sptr_;

    return *this;
}*/

bool Hit::operator==(Hit const& hit2) const{
      return ((hit_ == hit2.hit_) && (distance_ == hit2.distance_) && (target_ == hit2.target_) && (normal_ == hit2.normal_) && (sptr_ == hit2.sptr_));
    }

std::ostream& operator<<(std::ostream& os, Hit const& hit) {
    os << "Hit: " << hit.hit_ << std::endl;
    if (hit.hit_ == true) {
           os << "Distanz: " << hit.distance_ << std::endl
           << "Intersection: ("
           << hit.target_.x << ", "
           << hit.target_.y << ", "
           << hit.target_.z << ")" << std::endl
           << "Normal: ("
           << hit.normal_.x << ", "
           << hit.normal_.y << ", "
           << hit.normal_.z << ")" << std::endl;
        return os;
    }
    return os;
}
