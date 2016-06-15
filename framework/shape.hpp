#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "color.hpp"

class Shape
{
public:
//default constructor
  Shape();

//custom constructor
  Shape(std::string const&, Color const&);

//virtual methods
  virtual float area() const = 0;	//pure virtual, no implementation on this level, override needed

  virtual float volume() const = 0;	//pure virtual, no implementation on this level, override needed

//The = 0; is also known as the "pure specifier". The virtual function does not have the value of 0 now.

//getter
std::string get_name_() const;
Color get_color_() const;

protected:
  std::string name_;
  Color color_;

//Aufgabe 5.4 
  virtual std::ostream& print(std::ostream& os) const;  //virtual, override possible

};

std::ostream& operator <<(std::ostream&, Shape const&);

#endif //#define SHAPE_HPP
