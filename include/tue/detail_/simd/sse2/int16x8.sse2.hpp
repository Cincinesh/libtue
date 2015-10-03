//                Copyright Jo Bates 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//     Please report any bugs, typos, or suggestions to
//         https://github.com/Cincinesh/tue/issues

#pragma once

#include <emmintrin.h>

#include <cstdint>
#include <type_traits>

#include "../../../simd.hpp"

namespace tue
{
    template<>
    class alignas(sizeof(std::int16_t) * 8) simd<std::int16_t, 8>
    {
        __m128i underlying_;

    private:
        template<typename U>
        static int16x8 explicit_cast(const simd<U, 8>& s) noexcept
        {
            int16x8 result;
            for (int i = 0; i < 8; ++i)
            {
                result.data()[i] = std::int16_t(s.data()[i]);
            }
            return result;
        }

        inline static int16x8 explicit_cast(const bool16x8& s) noexcept;

        inline static int16x8 explicit_cast(const uint16x8& s) noexcept;

    public:
        using component_type = std::int16_t;

        static constexpr int component_count = 8;

        static constexpr bool is_accelerated = true;

        simd() noexcept = default;

        explicit simd(std::int16_t x) noexcept
        :
            underlying_(_mm_set1_epi16(x))
        {
        }

        template<int M = 8, typename = std::enable_if_t<M == 2>>
        inline simd(std::int16_t x, std::int16_t y) noexcept;

        template<int M = 8, typename = std::enable_if_t<M == 4>>
        inline simd(
            std::int16_t x,
            std::int16_t y,
            std::int16_t z,
            std::int16_t w) noexcept;

        template<typename U>
        explicit simd(const simd<U, 8>& s) noexcept
        {
            *this = explicit_cast(s);
        }

        simd(__m128i underlying) noexcept
        :
            underlying_(underlying)
        {
        }

        operator __m128i() const noexcept
        {
            return underlying_;
        }

        static int16x8 zero() noexcept
        {
            return _mm_setzero_si128();
        }

        static int16x8 load(const std::int16_t* data) noexcept
        {
            return _mm_load_si128(reinterpret_cast<const __m128i*>(data));
        }

        static int16x8 loadu(const std::int16_t* data) noexcept
        {
            return _mm_loadu_si128(reinterpret_cast<const __m128i*>(data));
        }

        void store(std::int16_t* data) const noexcept
        {
            _mm_store_si128(reinterpret_cast<__m128i*>(data), underlying_);
        }

        void storeu(std::int16_t* data) const noexcept
        {
            _mm_storeu_si128(reinterpret_cast<__m128i*>(data), underlying_);
        }

        const std::int16_t* data() const noexcept
        {
            return reinterpret_cast<const std::int16_t*>(&underlying_);
        }

        std::int16_t* data() noexcept
        {
            return reinterpret_cast<std::int16_t*>(&underlying_);
        }
    };
}

#include "bool16x8.sse2.hpp"
#include "uint16x8.sse2.hpp"

namespace tue
{
    inline int16x8 int16x8::explicit_cast(const bool16x8& s) noexcept
    {
        return __m128i(s);
    }

    inline int16x8 int16x8::explicit_cast(const uint16x8& s) noexcept
    {
        return __m128i(s);
    }

    namespace detail_
    {
        template<typename T>
        inline int16x8 unary_plus_operator_s(const int16x8& s) noexcept
        {
            return s;
        }

        template<typename T>
        inline int16x8& pre_increment_operator_s(int16x8& s) noexcept
        {
            return s = _mm_add_epi16(s, int16x8(1));
        }

        template<typename T>
        inline int16x8 post_increment_operator_s(int16x8& s) noexcept
        {
            const auto result = s;
            s = _mm_add_epi16(s, int16x8(1));
            return result;
        }

        template<typename T>
        inline int16x8 unary_minus_operator_s(const int16x8& s) noexcept
        {
            return _mm_add_epi16(_mm_xor_si128(s, int16x8(0xFFFF)), int16x8(1));
        }

        template<typename T>
        inline int16x8& pre_decrement_operator_s(int16x8& s) noexcept
        {
            return s = _mm_sub_epi16(s, int16x8(1));
        }

        template<typename T>
        inline int16x8 post_decrement_operator_s(int16x8& s) noexcept
        {
            const auto result = s;
            s = _mm_sub_epi16(s, int16x8(1));
            return result;
        }

        template<typename T>
        inline int16x8 bitwise_not_operator_s(const int16x8& s) noexcept
        {
            return _mm_xor_si128(s, int16x8(0xFFFF));
        }

        template<typename T>
        inline int16x8 addition_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_add_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8 subtraction_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_sub_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8 multiplication_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_mullo_epi16(lhs, rhs);
        }

        /*template<typename T>
        inline int16x8 division_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            // TODO
        }

        template<typename T>
        inline int16x8 modulo_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            // TODO
        }*/

        template<typename T>
        inline int16x8 bitwise_and_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_and_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8 bitwise_or_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_or_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8 bitwise_xor_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_xor_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8 bitwise_shift_left_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_slli_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8 bitwise_shift_right_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_srli_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8& addition_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_add_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8& subtraction_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_sub_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8& multiplication_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_mullo_epi16(lhs, rhs);
        }

        /*template<typename T>
        inline int16x8& division_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            // TODO
        }

        template<typename T>
        inline int16x8& modulo_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            // TODO
        }*/

        template<typename T>
        inline int16x8& bitwise_and_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_and_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8& bitwise_or_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_or_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8& bitwise_xor_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_xor_si128(lhs, rhs);
        }

        template<typename T>
        inline int16x8& bitwise_shift_left_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_slli_epi16(lhs, rhs);
        }

        template<typename T>
        inline int16x8& bitwise_shift_right_assignment_operator_ss(
            int16x8& lhs, const int16x8& rhs) noexcept
        {
            return lhs = _mm_srli_epi16(lhs, rhs);
        }

        template<typename T>
        inline bool equality_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_movemask_epi8(_mm_cmpeq_epi16(lhs, rhs)) == 0xFFFF;
        }

        template<typename T>
        inline bool inequality_operator_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_movemask_epi8(_mm_cmpeq_epi16(lhs, rhs)) != 0xFFFF;
        }

        template<typename T>
        inline int16x8 abs_s(const int16x8& s) noexcept
        {
            const auto nmask = _mm_cmplt_epi16(s, _mm_setzero_si128());
            return _mm_or_si128(
                _mm_and_si128(nmask, unary_minus_operator_s(s)),
                _mm_andnot_si128(nmask, s));
        }

        template<typename T>
        inline int16x8 min_ss(
            const int16x8& s1, const int16x8& s2) noexcept
        {
            return _mm_min_epi16(s1, s2);
        }

        template<typename T>
        inline int16x8 max_ss(
            const int16x8& s1, const int16x8& s2) noexcept
        {
            return _mm_max_epi16(s1, s2);
        }

        template<typename T, typename U>
        inline int16x8 mask_ss(
            const bool16x8& conditions,
            const int16x8& values) noexcept
        {
            return _mm_and_si128(conditions, values);
        }

        template<typename T, typename U>
        inline int16x8 select_sss(
            const bool16x8& conditions,
            const int16x8& values,
            const int16x8& otherwise) noexcept
        {
            return _mm_or_si128(
                _mm_and_si128(conditions, values),
                _mm_andnot_si128(conditions, otherwise));
        }

        template<typename T>
        inline bool16x8 less_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_cmplt_epi16(lhs, rhs);
        }

        template<typename T>
        inline bool16x8 less_equal_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_xor_si128(_mm_cmpgt_epi16(lhs, rhs), int16x8(0xFFFF));
        }

        template<typename T>
        inline bool16x8 greater_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_cmpgt_epi16(lhs, rhs);
        }

        template<typename T>
        inline bool16x8 greater_equal_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_xor_si128(_mm_cmplt_epi16(lhs, rhs), int16x8(0xFFFF));
        }

        template<typename T>
        inline bool16x8 equal_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_cmpeq_epi16(lhs, rhs);
        }

        template<typename T>
        inline bool16x8 not_equal_ss(
            const int16x8& lhs, const int16x8& rhs) noexcept
        {
            return _mm_xor_si128(_mm_cmpeq_epi16(lhs, rhs), int16x8(0xFFFF));
        }
    }
}
