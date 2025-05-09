set(sources
  src/math/math.cpp
  src/math/ray.cpp

  src/geometry/sphere.cpp

  src/image/color.cpp
  src/image/color_format.cpp

  src/file/ppm_writer.cpp

  src/core/object3d.cpp
  src/core/material.cpp
  src/core/world.cpp

  src/light/light.cpp
  src/light/point_light.cpp
)

set(main_sources
  src/main.cpp
  ${sources}
)

set(clock_sources
  src/clock.cpp
  ${sources}
)
set(trajectory_sources
  src/trajectory.cpp
  ${sources}
)
set(projection_sources
  src/projection.cpp
  ${sources}
)
set(shading_sources
  src/shaded_sphere.cpp
  ${sources}
)

set(headers
  include/yart/simd.h
  include/yart/math/math.h

  include/yart/core/ray.h
  include/yart/core/object3d.h
  
  include/yart/geometry/transform.h
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
  src/surface_normal_test.cpp
  src/shading_test.cpp
)
