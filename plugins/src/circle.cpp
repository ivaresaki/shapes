#include "circle.hpp"

#ifdef _WIN32
extern "C" __declspec(dllexport) Shape* create_shape(double radius)
#else
extern "C" Shape* create_shape(double radius)
#endif
{
  return new Circle(radius);
}

Circle::Circle(double radius)
  : Shape("Circle"), radius(radius) {
}

Circle::~Circle() {}

double Circle::get_radius() const
{
  return this->radius;
}

double Circle::get_area() const
{
  return this->PI * this->get_radius() * this->get_radius();
}

double Circle::get_perimeter() const
{
  return 2 * this->PI * this->get_radius();
}

std::ostream& Circle::print(std::ostream& os) const
{
  Shape::print(os);
  os << "Radius: " << this->get_radius() << std::endl;
  return os;
}