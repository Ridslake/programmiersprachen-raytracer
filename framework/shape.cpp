#include <shape.hpp>

//default
Shape::Shape():
  name_ (""),
  mat {}
  {}

//custom
Shape::Shape(std::string const& name_, Color const& color_):
  name_ (name_),
  mat (mat)
  {}

//destructor
Shape::~Shape()
{
  std::cout <<"destruct shape"<<std::endl;
}

//getter
  //name
std::string Shape::get_name_() const
{
  return name_;
}
  //color
Color Shape::get_material() const
{
  return mat;
}

std::ostream& Shape::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << mat << std::endl;
} 

std::ostream& operator <<(std::ostream& os, Shape const& s)
{
  return s.print(os);
}

