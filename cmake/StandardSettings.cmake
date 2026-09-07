#
# Project settings
#

option(${PROJECT_NAME}_WARNINGS_AS_ERRORS "Treat compiler warnings as errors."
       OFF)

#
# Unit testing
#

option(${PROJECT_NAME}_ENABLE_UNIT_TESTING
       "Enable unit tests for the projects (from the `test` subfolder)." ON)

#
# Static analyzers
#
# Currently supporting: Clang-Tidy, Cppcheck.

option(${PROJECT_NAME}_ENABLE_CLANG_TIDY
       "Enable static analysis with Clang-Tidy." OFF)
option(${PROJECT_NAME}_ENABLE_CPPCHECK "Enable static analysis with Cppcheck."
       OFF)

#
# Code coverage
#

option(${PROJECT_NAME}_ENABLE_CODE_COVERAGE "Enable code coverage through GCC."
       OFF)

#
# Doxygen
#

option(${PROJECT_NAME}_ENABLE_DOXYGEN
       "Enable Doxygen documentation builds of source." OFF)

#
# Miscellaneous options
#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(
  ${PROJECT_NAME}_VERBOSE_OUTPUT
  "Enable verbose output, allowing for a better understanding of each step taken."
  ON)

option(${PROJECT_NAME}_ENABLE_LTO
       "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)."
       ON)
if(${PROJECT_NAME}_ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)
  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}.")
  endif()
endif()

option(${PROJECT_NAME}_ENABLE_CCACHE
       "Enable the usage of Ccache, in order to speed up rebuild times." ON)
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

option(${PROJECT_NAME}_ENABLE_ASAN
       "Enable Address Sanitize to detect memory error." OFF)
if(${PROJECT_NAME}_ENABLE_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

option(${PROJECT_NAME}_ENABLE_OPENMP "Enable OpenMP for parallel computing" OFF)
if(${PROJECT_NAME}_ENABLE_OPENMP)
  find_package(OpenMP REQUIRED)
  message(
    STATUS
      "Found OpenMP, adding flags '${OpenMP_CXX_FLAGS}' to compiler and linker")
  add_compile_options(${OpenMP_CXX_FLAGS})
  add_link_options(${OpenMP_CXX_FLAGS})
endif()

option(${PROJECT_NAME}_PROGRESS "Enable a progress bar for rendering" ON)
if(${PROJECT_NAME}_PROGRESS)
  add_compile_definitions(USE_PROGRESS_BAR)
  message(STATUS "Adding a progress bar to the rendering routine")
endif()

add_compile_options(-march=native)

find_package(PkgConfig REQUIRED)
