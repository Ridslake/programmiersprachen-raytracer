#include "material.hpp"

Material::Material(): //def
  name {""},
  ka ({0, 0 ,0}),
  kd ({0, 0 ,0}),
  ks ({0, 0 ,0}),
  m_ {0}
  {}

Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float const& m): //cus
  name {name},
  ka {ka},
  kd {kd},
  ks {ks},
  m_ {m}
  {}

//print
std::ostream& Material::print(std::ostream& os) const
{
  os << name << "\n"
  << ka << "\n"
  << kd << "\n"
  << ks << "\n"
  << m  << "\n";
  return os;

//<< operator
std::ostream& operator << (std::ostream& os, Material const& mat) {
	return mat.print(os);
}
