#ifndef SHAPE_HPP
#define SHAPE_HPP

class shape
{
public:
  virtual void area() const = 0;	//pure virtual, no implementation on this level, override needed

  virtual void volume() const = 0;	//pure virtual, no implementation on this level, override needed

//The = 0; is also known as the "pure specifier". The virtual function does not have the value of 0 now.

//...
  virtual std::ostream& print(std::ostream& os) const;  //virtual, override possible
//...

};







std::ostream& operator<<(std::ostream& os, Shape const& s)
{
  //not implemented yet
}

#endif //#define SHAPE_HPP
