# include common headers
include_directories(${CMAKE_SOURCE_DIR}/common/include)


# build rectangle plugin
add_library(rectangle SHARED src/rectangle.cpp)
target_link_libraries(rectangle shape)
target_include_directories(rectangle PUBLIC ${CMAKE_SOURCE_DIR}/plugins/include)

# build circle plugin
add_library(circle SHARED src/circle.cpp)
target_link_libraries(circle shape)
target_include_directories(circle PUBLIC ${CMAKE_SOURCE_DIR}/plugins/include)

if(APPLE)
  set_target_properties(rectangle PROPERTIES
    OUTPUT_NAME "rectangle"
    SUFFIX ".dylib"
    INSTALL_NAME_DIR "@rpath"
  )
  set_target_properties(circle PROPERTIES
    OUTPUT_NAME "circle"
    SUFFIX ".dylib"
    INSTALL_NAME_DIR "@rpath"
  )
elseif(WIN32)
  set_target_properties(rectangle PROPERTIES
    OUTPUT_NAME "rectangle"
    SUFFIX ".dll"
  )
  set_target_properties(circle PROPERTIES
    OUTPUT_NAME "circle"
    SUFFIX ".dll"
  )
else()
  set_target_properties(rectangle PROPERTIES OUTPUT_NAME "rectangle")
  set_target_properties(circle PROPERTIES OUTPUT_NAME "circle")
endif()