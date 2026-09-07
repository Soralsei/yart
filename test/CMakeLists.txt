cmake_minimum_required(VERSION 3.15)

project(${CMAKE_PROJECT_NAME}Tests LANGUAGES CXX)

verbose_message("Adding tests under ${CMAKE_PROJECT_NAME}Tests...")

find_package(GTest REQUIRED)

foreach(file ${TEST_SOURCES})
  string(REGEX REPLACE "(.*/)([a-zA-Z0-9_ ]+)(\.cpp)" "\\2" test_name ${file})
  add_executable(${test_name}_Tests "${CMAKE_SOURCE_DIR}/${file}")
  target_compile_features(${test_name}_Tests PUBLIC cxx_std_17)

  if(${CMAKE_PROJECT_NAME}_ENABLE_CODE_COVERAGE)
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
    target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
    verbose_message("Code coverage is enabled and provided with GCC.")
  endif()

  target_link_libraries(
    ${test_name}_Tests
    PUBLIC
      GTest::GTest
      GTest::Main
      ${CMAKE_PROJECT_NAME})

  add_test(NAME ${test_name} COMMAND ${test_name}_Tests)
endforeach()

verbose_message("Finished adding unit tests for ${CMAKE_PROJECT_NAME}.")
