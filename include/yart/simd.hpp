#pragma once
#include <immintrin.h>

using SIMD_t = __m128;
using SIMDi_t = __m128i;
using SIMDd_t = __m256;
using SIMDll_t = __m256i;

inline void* malloc_simd(const size_t size) {
#if defined WIN32
  return _aligned_malloc(size, 16);
#elif defined __linux__
  void* ptr;
  posix_memalign(&ptr, 16, size);
  return ptr;
#elif defined __MACH__
  return malloc(size);
#else  // use page-aligned memory for other systems
  return valloc(size);
#endif
}

inline void free_simd(void* v) {
#if defined WIN32
  return _aligned_free(v);
#else
  return free(v);
#endif
}