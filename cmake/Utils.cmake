function(verbose_message content)
  if(${PROJECT_NAME}_VERBOSE_OUTPUT)
    message(STATUS ${content})
  endif()
endfunction()

function(add_clang_format_target)
  if(NOT ${PROJECT_NAME}_CLANG_FORMAT_BINARY)
    find_program(${PROJECT_NAME}_CLANG_FORMAT_BINARY clang-format)
  endif()

  if(${PROJECT_NAME}_CLANG_FORMAT_BINARY)
    add_custom_target(
      clang-format
      COMMAND ${${PROJECT_NAME}_CLANG_FORMAT_BINARY} -i ${SOURCES} ${HEADERS}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    message(
      STATUS
        "Format the project using the `clang-format` target (i.e: cmake --build build --target clang-format).\n"
    )
  endif()
endfunction()

function(add_executable_target target_name sources)
  add_executable(${target_name} ${sources})
  target_compile_features(${target_name} PRIVATE cxx_std_17)
  target_link_libraries(${target_name} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
  set_target_properties(
    ${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                              "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
endfunction()

function(add_executable_target target_name sources)
  if(${PROJECT_NAME}_BUILD_EXECUTABLE)
    add_executable(${target_name} ${sources})
    if(${PROJECT_NAME}_VERBOSE_OUTPUT)
      message(STATUS "Adding executable target: ${target_name}")
      verbose_message("Found the following sources:")
      foreach(source IN LISTS sources)
        verbose_message("* ${source}")
      endforeach()
    endif()
    target_compile_features(${target_name} PRIVATE cxx_std_17)
    target_include_directories(
      ${target_name}
      PRIVATE $<INSTALL_INTERFACE:include>
              $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    set_target_properties(
      ${target_name}
      PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
                 "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                 LIBRARY_OUTPUT_DIRECTORY
                 "${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}"
                 RUNTIME_OUTPUT_DIRECTORY
                 "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}")
  endif()
endfunction()
