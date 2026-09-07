add_subdirectory(SDL)
add_subdirectory(argparsepp)

add_library(vendored INTERFACE)

target_link_libraries(vendored INTERFACE SDL3::SDL3)
target_link_libraries(vendored INTERFACE argparse++)
