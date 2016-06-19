#include <shape.hpp>

//default
Shape::Shape():
  name_ (""),
  color_ ({0, 0 ,0})
  {}

//custom
Shape::Shape(std::string const& name_, Color const& color_):
  name_(name_),
  color_ (color_)
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
Color Shape::get_color_() const
{
  return color_;
}

std::ostream& Shape::print(std::ostream& os) const
{
 os << name_ << std::endl;
 os << color_ << std::endl;
} 

std::ostream& operator <<(std::ostream& os, Shape const& s)
{
  return s.print(os);
}

