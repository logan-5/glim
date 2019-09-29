#ifndef GLIM_FWD_HPP
#define GLIM_FWD_HPP

#include <cm/vec.hpp>

#include <cstddef>
#include <cstdint>

#define GLIM_ENABLE_ASSERTS true

#if GLIM_ENABLE_ASSERTS
#include <cassert>
#define GLIM_ASSERT(...) assert(__VA_ARGS__)
#else
#define GLIM_ASSERT(...) \
    do {                 \
    } while (false)
#endif

namespace glim {
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using usize = std::size_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using f32 = float;
static_assert(sizeof(float) == 4);
using f64 = double;
static_assert(sizeof(double) == 8);

using Color3 = cm::vec3;
using Color4 = cm::vec4;

}  // namespace glim

#endif
