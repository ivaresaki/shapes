include_directories(
  ${CMAKE_SOURCE_DIR}/common/include 
  ${CMAKE_SOURCE_DIR}/plugins/include
)

add_executable(app src/main.cpp)

target_link_libraries(app shape)

# check for dl library
find_library(DL_LIBRARY dl)
if(NOT DL_LIBRARY)
  message(FATAL_ERROR "dl library not found")
endif()

target_link_libraries(app ${DL_LIBRARY})

if(APPLE)
  set_target_properties(app PROPERTIES
    INSTALL_RPATH "@loader_path"
  )

  add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/lib/librectangle.dylib
    ${CMAKE_BINARY_DIR}/lib/libcircle.dylib
    $<TARGET_FILE_DIR:app>
  )

else()
  # ensure plugins are available at runtime
  add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/lib/librectangle.so
    ${CMAKE_BINARY_DIR}/lib/libcircle.so
    $<TARGET_FILE_DIR:app>
  )

endif()

#install targets
install(TARGETS app DESTINATION bin)
install(TARGETS rectangle DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/common/include/ DESTINATION include)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/plugins/include/ DESTINATION include)