#include "light.hpp"
//d
Light::Light():
  lightname{"Lightname"},
  lightpos{},
  ld({})
  {}
//c
//light für beleuchtung definiert
Light::Light(std::string const& lightname, glm::vec3 const& lightpos, 
Color const& lightla, Color const& lightld):
  lightname(lightname),
  lightpos(lightpos),
  ld(lightld)
  {}

//Ueberpruefen
std::ostream& operator<<(std::ostream& os, Light const& light)
  {
    os << "\nLight: "
       << light.lightname
       << "\nPosition: (" 
       << light.lightpos.x 
       << "," 
       << light.lightpos.y 
       << "," 
       << light.lightpos.z 
       << ")\n"
       << "Farbe: "
       << light.ld 
       << "\n\n";
    return os;
  }
