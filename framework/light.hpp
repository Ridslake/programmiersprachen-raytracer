#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/glm.hpp>

#include "color.hpp"


class Light{

public:
//d
  Light();

//c //Light name, position, colour
  Light(std::string const&, glm::vec3 const&, Color const&);

  friend std::ostream& operator<<(std::ostream& os, Light const& light);

//	glm::vec3 const& pos() const;
//	Color const& ld() const;
//	std::string const& name() const;
//	std::ostream& print(std::ostream& os) const;
//private:
	std::string lightname;
	glm::vec3 lightpos;
	Color ld;
};

#endif