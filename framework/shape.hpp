#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "ray.hpp"
#include "material.hpp"

class Shape
{
public:
//default constructor
  Shape();

//custom constructor
  Shape(std::string const&, Material const&);

//destructor
  virtual ~Shape();

//virtual methods
  virtual float area() const = 0;	//pure virtual, no implementation on this level, override needed

  virtual float volume() const = 0;	//pure virtual, no implementation on this level, override needed

  virtual std::ostream& print(std::ostream&) const;  //task 5.4	//virtual, override possible

  virtual bool intersect(Ray const& ray, float& t) = 0; //task 6.3

//The = 0; is also known as the "pure specifier". The virtual function does not have the value of 0 now.

//getter
  std::string get_name_() const;
  Material get_material() const;

protected:
  std::string name_;
  Material mat;

};

std::ostream& operator <<(std::ostream&, Shape const&);

#endif //#define SHAPE_HPP
