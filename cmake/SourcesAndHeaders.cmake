set(sources
  src/math/math.cpp
  src/math/ray.cpp
  src/geometry/sphere.cpp
  src/image/color.cpp
  src/image/color_format.cpp
  src/file/ppm_writer.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/yart/simd.h
  include/yart/math/math.h
  include/yart/math/ray.h
  include/yart/math/transform.h

  include/yart/geometry/shape.h
  include/yart/geometry/sphere.h

  include/yart/image/canvas.h
  include/yart/image/color.h
  include/yart/image/color_format.h
  include/yart/file/ppm_writer.h
  include/yart/file/image_writer.h

  include/yart/util/vector.h
)

set(test_sources
  src/math_test.cpp
  src/ray_test.cpp
  src/color_test.cpp
  src/canvas_test.cpp
  src/ppm_test.cpp
  src/transform_test.cpp
)
