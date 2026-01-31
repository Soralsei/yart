[![MacOS](https://github.com/Soralsei/yart/actions/workflows/macos.yml/badge.svg)](https://github.com/Soralsei/yart/actions/workflows/macos.yml)
[![Windows](https://github.com/Soralsei/yart/actions/workflows/windows.yml/badge.svg)](https://github.com/Soralsei/yart/actions/workflows/windows.yml)
[![Ubuntu](https://github.com/Soralsei/yart/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/Soralsei/yart/actions/workflows/ubuntu.yml)
[![codecov](https://codecov.io/gh/Soralsei/yart/branch/master/graph/badge.svg)](https://codecov.io/gh/Soralsei/yart)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Soralsei/yart)](https://github.com/Soralsei/yart/releases)

# Yet Another Ray Tracer (YaRT)

A small, modern C++ CPU ray tracer. Implements a minimal scene pipeline (camera, rays, shapes, materials, transforms) and simple utilities to render images from a description in code.

This repository is the project's source — meant for experimentation, learning and incremental extension.

## Features
- Basic pinhole camera and ray generation
- Shape primitives and local/ world-space intersections & normals
- Material and basic shading support
- Simple progress output utility
- Uses GLM for math

## Requirements
- Linux (development tested)
- C++17 capable compiler (g++/clang++)
- CMake 3.15+
- GLM (header-only)
- Optional: image writing library (stb_image_write or similar) if you want PNG output
- Optional: GoogleTest for unit tests

## Quick build (Linux)
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j$(nproc)
```

Binaries will be placed in the build tree (check CMake output for exact path).

## Run
TODO

## Tests
If unit tests are enabled in CMake:
```bash
cd build
ctest -C Release -V
```

## Development notes
- Math uses GLM (vec/mat/transform). Keep transformations as glm::mat4 and convert between vec3/vec4 appropriately (w=1 for points, w=0 for vectors).
- Thread-safety: the progress bar uses a mutex; ensure shared data is protected if extending multi-threaded render loops.
- Code layout: core components live in `src/core/`, geometry in `src/geometry/`, utilities in `src/util/`.

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details
