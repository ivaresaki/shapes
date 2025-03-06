#include <iostream>
#include <dlfcn.h>
#include <string>

#include "shape.hpp"

typedef Shape* (*CreateShapeFunc1)(double);
typedef Shape* (*CreateShapeFunc2)(double, double);

int main() 
{

  #ifdef __APPLE__
    const std::string rectangleLib = "./librectangle.dylib";
    const std::string circleLib = "./libcircle.dylib";
    #elif __LINUX__
    const std::string rectangleLib = "./librectangle.so";
    const std::string circleLib = "./libcircle.so";
  #endif

  // load rectangle plugin
  void* rectangle_handle = dlopen(rectangleLib.c_str(), RTLD_LAZY);

  if(!rectangle_handle)
  {
    std::cerr << "Cannot load library: " << dlerror() << std::endl;
    return 1;
  }

  // get create shape function
  CreateShapeFunc2 create_rectangle = (CreateShapeFunc2)dlsym(rectangle_handle, "create_shape");

  if(!create_rectangle)
  {
    std::cerr << "Cannot load symbom create: " << dlerror() << std::endl;
    return 1;
  }

  // load circle plugin
  void* circle_handle = dlopen(circleLib.c_str(), RTLD_LAZY);

  if(!circle_handle)
  {
    std::cerr << "Cannot load library: " << dlerror() << std::endl;
    return 1;
  }


  // get create shape function
  CreateShapeFunc1 create_circle = (CreateShapeFunc1)dlsym(circle_handle, "create_shape");

  if(!create_circle)
  {
    std::cerr << "Cannot load symbom create: " << dlerror() << std::endl;
    return 1;
  }


  // create rectangle
  Shape* rectangle = create_rectangle(2, 4);
  std::cout << *rectangle << std::endl;
  delete rectangle;

  Shape* circle = create_circle(3);
  std::cout << *circle << std::endl;
  delete circle;

  dlclose(rectangle_handle);
  dlclose(circle_handle);
  
  return 0;
}