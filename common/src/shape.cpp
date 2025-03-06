#include "shape.hpp"

Shape::Shape(std::string name) : name(name) {}

Shape::~Shape() {}

std::string Shape::get_name() const
{
  return this->name;
}

std::ostream& Shape::print(std::ostream& os) const
{
  os << "Name: " << this->get_name() << std::endl;
  os << "Area: " << this->get_area() << std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
  // delegate printing to the shape object
  return shape.print(os);
}