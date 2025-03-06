#include <iostream>
#include <dlfcn.h>
#include <string>

#include "shape.hpp"

typedef Shape* (*CreateShapeFunc)(double, double);
typedef Shape* (*CreateShapeFUnc)(double);

int main() 
{

  #ifdef __APPLE__
    const std::string rectangleLib = "./librectangle.dylib";
    #elif __LINUX__
    const std::string rectangleLib = "./librectangle.so";
  #endif

  // load rectangle plugin
  void* rectangle_handle = dlopen(rectangleLib.c_str(), RTLD_LAZY);

  if(!rectangle_handle)
  {
    std::cerr << "Cannot load library: " << dlerror() << std::endl;
    return 1;
  }

  // get create shape function
  CreateShapeFunc create_rectangle = (CreateShapeFunc)dlsym(rectangle_handle, "create_shape");

  if(!create_rectangle)
  {
    std::cerr << "Cannot load symbom create: " << dlerror() << std::endl;
    return 1;
  }

  // create rectangle
  Shape* rectangle = create_rectangle(2, 4);
  std::cout << *rectangle << std::endl;
  delete rectangle;

  dlclose(rectangle_handle);
  
  return 0;
}