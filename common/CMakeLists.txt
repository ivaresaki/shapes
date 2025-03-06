file(GLOB SRC_FILES src/*.cpp)

add_library(shape STATIC ${SRC_FILES})

target_include_directories(shape PUBLIC ${CMAKE_SOURCE_DIR}/common/include)
