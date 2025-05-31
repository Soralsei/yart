set(sources
  src/math/math.cpp
  src/math/ray.cpp

  src/geometry/shape.cpp
  src/geometry/primitives/sphere.cpp
  src/geometry/primitives/plane.cpp
  src/geometry/hit.cpp
  src/geometry/intersection.cpp
  src/geometry/transform.cpp

  src/image/canvas.cpp
  src/image/color.cpp
  src/image/color_format.cpp

  src/file/ppm_writer.cpp

  src/core/object3d.cpp
  src/core/material.cpp
  src/core/world.cpp
  src/core/camera.cpp

  src/light/light.cpp
  src/light/point_light.cpp

  src/util/progress_bar.cpp
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
set(render_sources
  src/world_render.cpp
  ${sources}
)
set(plane_render_sources
  src/plane_render.cpp
  ${sources}
)

set(headers
  # include/yart/simd.hpp
  # include/yart/util/math.hpp

  # include/yart/core/ray.hpp
  # include/yart/core/object3d.hpp
  
  # include/yart/geometry/transform.hpp
  # include/yart/geometry/primitives/sphere.hpp

  # include/yart/image/canvas.hpp
  # include/yart/image/color.hpp
  # include/yart/image/color_format.hpp
  # include/yart/file/ppm_writer.hpp
  # include/yart/file/image_writer.hpp

  # include/yart/util/vector.hpp
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
  src/world_test.cpp
  src/camera_test.cpp
)
