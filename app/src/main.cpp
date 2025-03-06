#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

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
#elif _WIN32
  const std::string rectangleLib = "rectangle.dll";
  const std::string circleLib = "circle.dll";

#endif


#ifdef _WIN32

  // load rectangle plugin
  HMODULE rectangle_handle = LoadLibrary(rectangleLib.c_str());
  if (!rectangle_handle)
  {
    std::cerr << "Cannot load library: " << GetLastError() << std::endl;
    //FreeLibrary(rectangle_handle);
    return 1;
  }

  CreateShapeFunc2 create_rectangle = (CreateShapeFunc2)GetProcAddress(rectangle_handle, "create_shape");
  if (!create_rectangle)
  {
    std::cerr << "Canno load symbol create: " << GetLastError() << std::endl;
    FreeLibrary(rectangle_handle);
    return 1;
  }

  // load circle plugin
  HMODULE circle_handle = LoadLibrary(circleLib.c_str());
  if (!circle_handle)
  {
    std::cerr << "Cannot load library: " << GetLastError() << std::endl;
    //FreeLibrary(circle_handle);
    return 1;
  }

  CreateShapeFunc1 create_circle = (CreateShapeFunc1)GetProcAddress(circle_handle, "create_shape");
  if (!create_circle)
  {
    std::cerr << "Canno load symbol create: " << GetLastError() << std::endl;
    FreeLibrary(circle_handle);
    return 1;
  }

#else
  // load rectangle plugin
  void* rectangle_handle = dlopen(rectangleLib.c_str(), RTLD_LAZY);

  if (!rectangle_handle)
  {
    std::cerr << "Cannot load library: " << dlerror() << std::endl;
    return 1;
  }

  // get create shape function
  CreateShapeFunc2 create_rectangle = (CreateShapeFunc2)dlsym(rectangle_handle, "create_shape");

  if (!create_rectangle)
  {
    std::cerr << "Cannot load symbom create: " << dlerror() << std::endl;
    return 1;
  }

  // load circle plugin
  void* circle_handle = dlopen(circleLib.c_str(), RTLD_LAZY);

  if (!circle_handle)
  {
    std::cerr << "Cannot load library: " << dlerror() << std::endl;
    return 1;
  }


  // get create shape function
  CreateShapeFunc1 create_circle = (CreateShapeFunc1)dlsym(circle_handle, "create_shape");

  if (!create_circle)
  {
    std::cerr << "Cannot load symbom create: " << dlerror() << std::endl;
    return 1;
  }

#endif

  // create rectangle
  Shape* rectangle = create_rectangle(2, 4);
  std::cout << *rectangle << std::endl;
  delete rectangle;

  Shape* circle = create_circle(3);
  std::cout << *circle << std::endl;
  delete circle;

#ifdef _WIN32
  FreeLibrary(rectangle_handle);
  FreeLibrary(circle_handle);
#else
  dlclose(rectangle_handle);
  dlclose(circle_handle);
#endif

  return 0;
}