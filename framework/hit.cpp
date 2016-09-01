#include <limits>
#include "hit.hpp"
#include "shape.hpp"

//Intersection
//numeric_limits infinity = gitb positiven unendlichen Wert zurück (floating Value)
//kein Hit
Hit::Hit():
hit_{false},
distance_{std::numeric_limits<float>::infinity()},
target_{std::numeric_limits<float>::infinity(),
std::numeric_limits<float>::infinity(),
std::numeric_limits<float>::infinity()},
normal_{std::numeric_limits<float>::infinity(),
std::numeric_limits<float>::infinity(),
std::numeric_limits<float>::infinity()},
sptr_{nullptr} 
{}

//bei Hit
Hit::Hit(bool hit, float dis, glm::vec3 const& intersection,
    glm::vec3 const& norm, Shape* sptr) :
hit_{hit},
distance_{dis},
target_{intersection},
normal_{norm},
sptr_{sptr} 
{}

//setzt zb hit auf hit2 usw.
bool Hit::operator==(Hit const& hit2) const
{
	return ((hit_ == hit2.hit_) && (distance_ == hit2.distance_) && (target_ == hit2.target_) && (normal_ == hit2.normal_) && (sptr_ == hit2.sptr_));
}
//Ausgabe zur Überprüfung
std::ostream& operator<<(std::ostream& os, Hit const& hit) {
    os << "(Hit)Intersect: " << hit.hit_ << std::endl;
    if (hit.hit_ == true) {
           os << "Distanz: " << hit.distance_ << std::endl
           << "Trifft: ("
           << hit.target_.x << ", "
           << hit.target_.y << ", "
           << hit.target_.z << ")" << std::endl
           << "Normalisieren: ("
           << hit.normal_.x << ", "
           << hit.normal_.y << ", "
           << hit.normal_.z << ")" << std::endl;
        return os;
    }
    return os;
}
