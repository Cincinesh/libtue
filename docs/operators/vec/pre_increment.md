[Tuesday](../../../README.md)/[`tue::vec`](../../headers/vec.md)/pre-increment
==============================================================================
Provided by header [`<tue/vec.hpp>`](../../headers/vec.md)

```c++
// ++v
template<typename T, int N>
vec<T, N>& operator++(vec<T, N>& v) noexcept;
```

Pre-increments each and every component of the given
[`vec`](../../headers/vec.md) and returns a reference to it.

License
-------
Copyright Jo Bates 2015.

Distributed under the Boost Software License, Version 1.0.

See accompanying file [LICENSE_1_0.txt](../../../LICENSE_1_0.txt) or copy at
http://www.boost.org/LICENSE_1_0.txt.