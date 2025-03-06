# include common headers
include_directories(${CMAKE_SOURCE_DIR}/common/include)


# build rectangle plugin
add_library(rectangle SHARED src/rectangle.cpp)
target_link_libraries(rectangle shape)
target_include_directories(rectangle PUBLIC ${CMAKE_SOURCE_DIR}/plugins/include)

if(APPLE)
  set_target_properties(rectangle PROPERTIES
    OUTPUT_NAME "rectangle"
    SUFFIX ".dylib"
    INSTALL_NAME_DIR "@rpath"
  )
else()
  set_target_properties(rectangle PROPERTIES OUTPUT_NAME "rectangle")
endif()