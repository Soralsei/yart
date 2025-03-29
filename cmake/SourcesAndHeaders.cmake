set(sources
  src/math/math.cpp
  src/math/vector3.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/yart/math/math.h
  include/yart/math/vector3.h
)

set(test_sources
  src/vector3_test.cpp
)
