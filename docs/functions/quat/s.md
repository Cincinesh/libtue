`tue::quat::s`
==============
Provided by header [`<tue/quat.hpp>`](../../headers/quat.md)

```c++
template<typename T>
constexpr T quat<T>::s() const noexcept;
```

Returns a copy of the fourth component (i.e. the scalar component, as opposed to
the vector component [`v()`](v.md)) of this [`quat`](../../headers/quat.md).

License
-------
Copyright Jo Bates 2015.

Distributed under the Boost Software License, Version 1.0.

See accompanying file [LICENSE_1_0.txt](../../../LICENSE_1_0.txt) or copy at
http://www.boost.org/LICENSE_1_0.txt.