set(sources
  src/math/math.cpp
  src/math/vector3.cpp
  src/rendering/color.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/yart/math/math.h
  include/yart/math/vector3.h
  include/yart/rendering/color.h
)

set(test_sources
  src/vector3_test.cpp
  src/math_test.cpp
  src/color_test.cpp
)
