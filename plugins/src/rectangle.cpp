#include "rectangle.hpp"

#ifdef _WIN32
extern "C" __declspec(dllexport) Shape* create_shape(double width, double height)
#else
extern "C" Shape* create_shape(double width, double height)
#endif
{
  return new Rectangle(width, height);
}

Rectangle::Rectangle(double width, double height)
  : Shape("Rectangle"), width(width), height(height) {
}

Rectangle::~Rectangle() {}

double Rectangle::get_width() const
{
  return this->width;
}

double Rectangle::get_height() const
{
  return this->height;
}

double Rectangle::get_area() const
{
  return this->get_width() * this->get_height();
}

double Rectangle::get_perimeter() const
{
  return 2 * (this->get_width() + this->get_height());
}

std::ostream& Rectangle::print(std::ostream& os) const
{
  Shape::print(os);
  os << "Width: " << this->get_width() << std::endl;
  os << "Height: " << this->get_height() << std::endl;
  return os;
}