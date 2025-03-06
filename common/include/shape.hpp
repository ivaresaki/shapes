#pragma once

#include <string>
#include <ostream>

/// @brief Shape interface. Implementing classes must provide the following:
/// double get_area() const; 
class Shape
{
  private:
    std::string name;

  public:

    /// @brief Constructor
    /// @param name Name of the shape
    Shape(std::string name);

    /// @brief Destructor
    virtual ~Shape();

    /// @brief Returns the name of the shape
    std::string get_name() const;

    /// @brief Returns the area of the shape
    /// Needs to be overridden by implementing classes
    virtual double get_area() const = 0;

    /// @brief Prints the shape to the output stream
    /// @param os 
    /// @return 
    virtual std::ostream& print(std::ostream& os) const;

    /// @brief Overloading ostream operator to print the shape
    /// @param os 
    /// @param shape 
    /// @return 
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape);
};