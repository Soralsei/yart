cmake_minimum_required(VERSION 3.15)

project(
  "Yart"
  VERSION 0.1.0
  LANGUAGES CXX)

include(cmake/StandardSettings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Utils.cmake)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...\n")

if(UNIX)
  add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")
endif()

string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASE)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.\n"
  )
endif()

#
# Library target
#

include(cmake/SourcesAndHeaders.cmake)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
             "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
             LIBRARY_OUTPUT_DIRECTORY
             "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")

message(STATUS "Added all header and implementation files.\n")

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_NAME})

verbose_message(
  "Applied compiler warnings. Using standard ${CMAKE_CXX_STANDARD}.\n")

include(cmake/Doxygen.cmake)

#
# Dependencies
#

find_package(glm 1.0.2 REQUIRED)
message(STATUS "Found glm at ${GLM_INCLUDE_DIRS}")
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(PNG 1.6)
if(PNG_FOUND)
  message(STATUS "Found libpng: ${PNG_LIBRARIES}")
  add_compile_definitions(${PROJECT_NAME_UPPERCASE}_USE_LIBPNG)
  target_include_directories(${PROJECT_NAME} PRIVATE ${PNG_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${PNG_LIBRARIES})
endif()

if(${PROJECT_NAME}_ENABLE_OPENMP)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

verbose_message("Successfully added all dependencies and linked against them.")

#
# Alias and subdirectories
#

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

verbose_message("Project is now aliased as ${PROJECT_NAME}::${PROJECT_NAME}.\n")

add_subdirectory(src)
add_subdirectory(examples)

add_clang_format_target()

#
# Install
#

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  DESTINATION include
  PUBLIC_HEADER DESTINATION include)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
               include/${PROJECT_NAME_LOWERCASE}/version.hpp @ONLY)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}/version.hpp
  DESTINATION include/${PROJECT_NAME_LOWERCASE})

install(DIRECTORY include/${PROJECT_NAME_LOWERCASE} DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

message(STATUS "Finished building requirements for installing the package.\n")

#
# Unit testing
#

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  enable_testing()
  message(
    STATUS
      "Build unit tests for the project. Tests should always be found in the test folder\n"
  )
  add_subdirectory(test)
endif()
