set(sources
  src/math/math.cpp
  src/math/vector3.cpp
  src/image/color.cpp
  src/image/color_format.cpp
  src/file/ppm_writer.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/yart/math/math.h
  include/yart/math/vector3.h
  include/yart/image/canvas.h
  include/yart/image/color.h
  include/yart/image/color_format.h
  include/yart/file/ppm_writer.h
  include/yart/file/image_writer.h
)

set(test_sources
  src/vector3_test.cpp
  src/math_test.cpp
  src/color_test.cpp
  src/canvas_test.cpp
  src/ppm_test.cpp
)
