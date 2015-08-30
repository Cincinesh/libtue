//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#pragma once

#include "vec.hpp"

namespace tue
{
    /*!
     * \brief     A quaternion.
     * \details   `quat` has the same size and alignment requirements as `T[4]`.
     *            The first three components represent the vector part of the
     *            quaternion. The fourth component represents the scalar part.
     *
     * \tparam T  The component type.
     */
    template<typename T>
    class quat;

    /*!
     * \brief  A quaternion with `float` components.
     */
    using fquat = quat<float>;

    /*!
     * \brief  A quaternion with `double` components.
     */
    using dquat = quat<double>;

    /**/
    template<typename T>
    class quat
    {
        struct { T data[4]; } impl_;

    public:
        /*!
         * \brief  This `quat` type's component type.
         */
        using component_type = T;

        /*!
         * \brief  This `quat` type's component count.
         */
        static constexpr int component_count = 4;

        /*!
         * \brief  Default constructs each component.
         */
        quat() noexcept = default;

        /*!
         * \brief    Constructs each component with the value of the
         *           corresponding argument.
         *
         * \param x  The value to construct the first component with.
         * \param y  The value to construct the second component with.
         * \param z  The value to construct the third component with.
         * \param w  The value to construct the fourth component with.
         */
        constexpr quat(
            const T& x, const T& y, const T& z, const T& w) noexcept :
            impl_({{ x, y, z, w }})
        {
        }

        /*!
         * \brief    Constructs each component with the value of the
         *           corresponding argument.
         * \param v  The values to construct the first three components with.
         * \param s  The value to construct the fourth component with.
         */
        constexpr quat(const vec3<T>& v, const T& s) noexcept :
            impl_({{ v[0], v[1], v[2], s }})
        {
        }

        /*!
         * \brief     Explicitly casts another `quat` to a new component type.
         * \tparam U  The component type of parameter `q`.
         * \param q   The `quat` to cast from.
         */
        template<typename U>
        explicit constexpr quat(const quat<U>& q) noexcept :
            impl_({{ T(q[0]), T(q[1]), T(q[2]), T(q[3]) }})
        {
        }

        /*!
         * \brief     Implicitly casts this `quat` to a new component type.
         * \tparam U  The new component type.
         * \return    A new `quat` with the new component type.
         */
        template<typename U>
        constexpr operator quat<U>() const noexcept
        {
            return {
                this->impl_.data[0],
                this->impl_.data[1],
                this->impl_.data[2],
                this->impl_.data[3],
            };
        }

        /*!
         * \brief   Returns a `quat` with the fourth component set to `1` and
         *          all other components set to `0`.
         *
         * \return  A `quat` with the fourth component set to `1` and all other
         *          components set to `0`.
         */
        static constexpr quat<T> identity() noexcept
        {
            return { T(0), T(0), T(0), T(1) };
        }

        /*!
         * \brief     Returns a reference to the component at the given index.
         * \details   No bounds checking is performed.
         * \tparam I  The index type.
         * \param i   The index.
         * \return    A reference to the component at the given index.
         */
        template<typename I>
        constexpr const T& operator[](const I& i) const noexcept
        {
            return this->impl_.data[i];
        }

        /*!
         * \brief     Returns a reference to the component at the given index.
         * \details   No bounds checking is performed.
         * \tparam I  The index type.
         * \param i   The index.
         * \return    A reference to the component at the given index.
         */
        template<typename I>
        T& operator[](const I& i) noexcept
        {
            return this->impl_.data[i];
        }

        /*!
         * \brief   Returns a pointer to this `quat`'s underlying component
         *          array.
         *
         * \return  A pointer to this `quat`'s underlying component array.
         */
        const T* data() const noexcept
        {
            return this->impl_.data;
        }

        /*!
         * \brief   Returns a pointer to this `quat`'s underlying component
         *          array.
         *
         * \return  A pointer to this `quat`'s underlying component array.
         */
        T* data() noexcept
        {
            return this->impl_.data;
        }
    };

    /*!
     * \brief      Determines whether or not two `quat`'s compare equal.
     *
     * \tparam T   The component type of `lhs`.
     * \tparam U   The component type of `rhs`.
     *
     * \param lhs  The left-hand side operand.
     * \param rhs  The right-hand side operand.
     *
     * \return     `true` if all the corresponding pairs of components compare
     *             equal and `false` otherwise.
     */
    template<typename T, typename U>
    inline constexpr bool operator==(
        const quat<T>& lhs, const quat<U>& rhs) noexcept
    {
        return lhs[0] == rhs[0]
            && lhs[1] == rhs[1]
            && lhs[2] == rhs[2]
            && lhs[3] == rhs[3];
    }

    /*!
     * \brief      Determines whether or not two `quat`'s compare not equal.
     *
     * \tparam T   The component type of `lhs`.
     * \tparam U   The component type of `rhs`.
     *
     * \param lhs  The left-hand side operand.
     * \param rhs  The right-hand side operand.
     *
     * \return     `true` if at least one of the corresponding pairs of
     *             components compares not equal and `false` otherwise.
     */
    template<typename T, typename U>
    inline constexpr bool operator!=(
        const quat<T>& lhs, const quat<U>& rhs) noexcept
    {
        return lhs[0] != rhs[0]
            || lhs[1] != rhs[1]
            || lhs[2] != rhs[2]
            || lhs[3] != rhs[3];
    }
}
