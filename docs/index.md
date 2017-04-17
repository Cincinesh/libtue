The Tuesday C++ Vector Math and SIMD Library
============================================
The Tuesday C++ Vector Math and SIMD Library is a library of template classes
and math functions with a focus on physics and graphics applications. It
provides data types commonly used in games and other simulations such as
vectors, quaternions, and matrices, SIMD intrinsic wrapper classes completely
separate from (but compatible with) the other types, operator overloads for
combining and manipulating all these types, as well as some other common
mathematical functions. It was written to match the style of the C++ Standard
Library and uses modern C++ features (i.e., C++14) extensively.

Major Features
--------------
Tuesday provides the following unique features over other similar libraries such
as [GLM](https://github.com/g-truc/glm):

- The dimensions of vector and matrix types are template parameters,
  unlike GLM where, e.g., `tvec2`, `tvec3`, and `tvec4` are separate types. By
  making the dimensions template parameters, it's possible to write one template
  function that can operate on and/or produce vectors or matrices of multiple
  dimensions. For example, the transformation matrix generation functions
  (`translation_mat`, `rotation_mat`, etc.) can produce matrices of multiple
  sizes so long as they meet the minimum requirements of each transformation and
  are, at the largest, 4x4.

- It makes heavy use of `decltype` in return types. This makes it possible for
  composite types to behave much more like their component types when it comes
  to things like implicit type conversions. For example, `fvec3 + dvec3` results
  in a `dvec3` just as `float + double` results in a `double`.

- It uses `constexpr` whenever possible which, as it turns out, is often.

- SIMD types are completely separate from vector types. This may seem
  counter-intuitive, but SIMD vectors aren't very efficient when used as
  traditional 3D vectors. The fourth component of an SIMD vector would often go
  to waste, and functions where multiple components interact (such as the
  `length` function, `dot` product, or `cross` product) would be horribly
  inefficient with SIMD intrinsics. Instead, SIMD instructions should be used to
  perform the same logic on multiple vectors in parallel. Tuesday is designed
  for this use case. For example, `vec3<float32x4> v` could be thought of as 4
  parallel 3D vectors (4 x-values, followed by 4 y-values, and finally 4
  z-values). Something like `math::dot(v)` would then compute a single
  `float32x4` containing the dot products of those 4 parallel vectors without
  any inefficient component shuffling. See
  [this answer](http://stackoverflow.com/a/11620369/1195206) to a naive question
  I asked on Stack Overflow a few years back for some more rationale.

- The SIMD system supports a huge number of types. You can create 2, 4, 8, 16,
  32, and 64-component vectors of all the major arithmetic types (`float`,
  `double`, `int8_t`, `int16_t`, `int32_t`, `int64_t`, `uint8_t`, `uint16_t`,
  `uint32_t`, and `uint64_t`) along with sized boolean types (`bool8`, `bool16`,
  `bool32` and `bool64`). If SIMD-intrinsic acceleration isn't available for a
  particular type, there's a standard C++-compliant fallback. If a vector has
  too many components for acceleration, but a smaller vector with the same
  component type can be accelerated, then the larger vector is simply the
  composite of two smaller vectors. For example, if `float32x4` is accelerated
  but `float32x8` isn't, then `float32x8` will at least be partially-accelerated
  in that it's made of two `float32x4`'s.

Requirements
------------
Tuesday requires Visual Studio 2015 or a fully C++14 compliant compiler such as
GCC 5 or Clang 3.4.

Usage
-----
Tuesday is a header-only library. Simply make sure the `include` directory in
the root of this project is on your include path. For GCC and Clang, you might
have to provide the compiler option `-std=c++14` or higher as well.

Here's a small usage example:
~~~{.cpp}
# include <tue/mat.hpp>
# include <tue/quat.hpp>
# include <tue/simd.hpp>
# include <tue/transform.hpp>
# include <tue/vec.hpp>

using namespace tue;

void UpdatePose(
    fvec3& translation,
    fquat& rotation,
    fmat3x4& matrix,
    const fvec3& linearVelocity,
    const fvec3& angularVelocity,
    float deltaTime)
{
    translation += linearVelocity * deltaTime;
    rotation *= transform::rotation_quat(angularVelocity * deltaTime);
    matrix = transform::rotation_mat<float, 4, 4>(rotation)
        * transform::translation_mat<float, 3, 4>(translation);
}

void SimdUpdatePoses(
    vec3<float32x4>& translations,
    quat<float32x4>& rotations,
    mat3x4<float32x4>& matrices,
    const vec3<float32x4>& linearVelocities,
    const vec3<float32x4>& angularVelocities,
    float deltaTime)
{
    const float32x4 deltaTimes(deltaTime);
    translations += linearVelocities * deltaTimes;
    rotations *= transform::rotation_quat(angularVelocities * deltaTimes);
    matrices = transform::rotation_mat<float32x4, 4, 4>(rotations)
        * transform::translation_mat<float32x4, 3, 4>(translations);
}
~~~

License
-------
Copyright Jo Bates 2015.

Distributed under the Boost Software License, Version 1.0.

See accompanying file [LICENSE_1_0.txt](LICENSE_1_0.txt) or copy at
http://www.boost.org/LICENSE_1_0.txt.

Bug Reporting
-------------
Please report any bugs, typos, or suggestions to
https://github.com/Cincinesh/tue/issues.
