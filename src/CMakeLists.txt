add_subdirectory(${CMAKE_SOURCE_DIR}/vendored ${CMAKE_BINARY_DIR}/vendored)

add_executable_target(${PROJECT_NAME}App "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(${PROJECT_NAME}App PRIVATE vendored)
