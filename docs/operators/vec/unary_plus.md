[Tuesday](../../../README.md)/[`tue::vec`](../../headers/vec.md)/unary plus
===========================================================================
Provided by header [`<tue/vec.hpp>`](../../headers/vec.md)

```c++
// +v
template<typename T, int N>
constexpr auto operator+(const vec<T, N>& v) noexcept
    -> vec<decltype(+v[0]), N>;
```

Returns the result of performing a unary plus on each and every component of the
given [`vec`](../../headers/vec.md).

License
-------
Copyright Jo Bates 2015.

Distributed under the Boost Software License, Version 1.0.

See accompanying file [LICENSE_1_0.txt](../../../LICENSE_1_0.txt) or copy at
http://www.boost.org/LICENSE_1_0.txt.