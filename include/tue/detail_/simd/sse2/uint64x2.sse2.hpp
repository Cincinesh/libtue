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
    class alignas(sizeof(std::uint64_t) * 2) simd<std::uint64_t, 2>
    {
        __m128i underlying_;

    private:
        template<typename U>
        static uint64x2 explicit_cast(const simd<U, 2>& s) noexcept
        {
            return {
                std::uint64_t(s.data()[0]),
                std::uint64_t(s.data()[1]),
            };
        }

        inline static uint64x2 explicit_cast(const bool64x2& s) noexcept;

        inline static uint64x2 explicit_cast(const int64x2& s) noexcept;

    public:
        using component_type = std::uint64_t;

        static constexpr int component_count = 2;

        static constexpr bool is_accelerated = true;

        simd() noexcept = default;

        explicit simd(std::uint64_t x) noexcept
        :
            underlying_(_mm_set1_epi64x(x))
        {
        }

        template<int M = 2, typename = std::enable_if_t<M == 2>>
        simd(std::uint64_t x, std::uint64_t y) noexcept
        :
            underlying_(_mm_setr_epi64x(x, y))
        {
        }

        template<int M = 2, typename = std::enable_if_t<M == 2>>
        inline simd(
            std::uint64_t x,
            std::uint64_t y,
            std::uint64_t z,
            std::uint64_t w) noexcept;

        template<typename U>
        explicit simd(const simd<U, 2>& s) noexcept
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

        static uint64x2 zero() noexcept
        {
            return _mm_setzero_si128();
        }

        static uint64x2 load(const std::uint64_t* data) noexcept
        {
            return _mm_load_si128(reinterpret_cast<const __m128i*>(data));
        }

        static uint64x2 loadu(const std::uint64_t* data) noexcept
        {
            return _mm_loadu_si128(reinterpret_cast<const __m128i*>(data));
        }

        void store(std::uint64_t* data) const noexcept
        {
            _mm_store_si128(reinterpret_cast<__m128i*>(data), underlying_);
        }

        void storeu(std::uint64_t* data) const noexcept
        {
            _mm_storeu_si128(reinterpret_cast<__m128i*>(data), underlying_);
        }

        const std::uint64_t* data() const noexcept
        {
            return reinterpret_cast<const std::uint64_t*>(&underlying_);
        }

        std::uint64_t* data() noexcept
        {
            return reinterpret_cast<std::uint64_t*>(&underlying_);
        }
    };
}

#include "bool64x2.sse2.hpp"
#include "int64x2.sse2.hpp"

namespace tue
{
    inline uint64x2 uint64x2::explicit_cast(const bool64x2& s) noexcept
    {
        return __m128i(s);
    }

    inline uint64x2 uint64x2::explicit_cast(const int64x2& s) noexcept
    {
        return __m128i(s);
    }

    namespace detail_
    {
        inline uint64x2& pre_increment_operator_s(uint64x2& s) noexcept
        {
            return s = _mm_add_epi64(s, uint64x2(1));
        }

        inline uint64x2 post_increment_operator_s(uint64x2& s) noexcept
        {
            const auto result = s;
            s = _mm_add_epi64(s, uint64x2(1));
            return result;
        }

        inline uint64x2& pre_decrement_operator_s(uint64x2& s) noexcept
        {
            return s = _mm_sub_epi64(s, uint64x2(1));
        }

        inline uint64x2 post_decrement_operator_s(uint64x2& s) noexcept
        {
            const auto result = s;
            s = _mm_sub_epi64(s, uint64x2(1));
            return result;
        }

        inline uint64x2 bitwise_not_operator_s(const uint64x2& s) noexcept
        {
            return _mm_xor_si128(s, uint64x2(~0ull));
        }

        inline uint64x2 addition_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_add_epi64(lhs, rhs);
        }

        inline uint64x2 subtraction_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_sub_epi64(lhs, rhs);
        }

        /*inline uint64x2 multiplication_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline uint64x2 division_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline uint64x2 modulo_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }*/

        inline uint64x2 bitwise_and_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_and_si128(lhs, rhs);
        }

        inline uint64x2 bitwise_or_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_or_si128(lhs, rhs);
        }

        inline uint64x2 bitwise_xor_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_xor_si128(lhs, rhs);
        }

        inline uint64x2 bitwise_shift_left_operator_si(
            const uint64x2& lhs, int rhs) noexcept
        {
            return _mm_slli_epi64(lhs, rhs);
        }

        inline uint64x2 bitwise_shift_right_operator_si(
            const uint64x2& lhs, int rhs) noexcept
        {
            return _mm_srli_epi64(lhs, rhs);
        }

        inline uint64x2& addition_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return lhs = _mm_add_epi64(lhs, rhs);
        }

        inline uint64x2& subtraction_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return lhs = _mm_sub_epi64(lhs, rhs);
        }

        /*inline uint64x2& multiplication_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline uint64x2& division_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline uint64x2& modulo_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }*/

        inline uint64x2& bitwise_and_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return lhs = _mm_and_si128(lhs, rhs);
        }

        inline uint64x2& bitwise_or_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return lhs = _mm_or_si128(lhs, rhs);
        }

        inline uint64x2& bitwise_xor_assignment_operator_ss(
            uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return lhs = _mm_xor_si128(lhs, rhs);
        }

        inline uint64x2& bitwise_shift_left_assignment_operator_si(
            uint64x2& lhs, int rhs) noexcept
        {
            return lhs = _mm_slli_epi64(lhs, rhs);
        }

        inline uint64x2& bitwise_shift_right_assignment_operator_si(
            uint64x2& lhs, int rhs) noexcept
        {
            return lhs = _mm_srli_epi64(lhs, rhs);
        }

        inline bool equality_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_movemask_epi8(_mm_cmpeq_epi64(lhs, rhs)) == 0xFFFF;
        }

        inline bool inequality_operator_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_movemask_epi8(_mm_cmpeq_epi64(lhs, rhs)) != 0xFFFF;
        }

        inline uint64x2 abs_s(const uint64x2& s) noexcept
        {
            return s;
        }

        /*inline uint64x2 min_ss(
            const uint64x2& s1, const uint64x2& s2) noexcept
        {
            // TODO
        }

        inline uint64x2 max_ss(
            const uint64x2& s1, const uint64x2& s2) noexcept
        {
            // TODO
        }*/

        inline uint64x2 mask_ss(
            const bool64x2& conditions,
            const uint64x2& values) noexcept
        {
            return _mm_and_si128(conditions, values);
        }

        inline uint64x2 select_sss(
            const bool64x2& conditions,
            const uint64x2& values,
            const uint64x2& otherwise) noexcept
        {
            return _mm_or_si128(
                _mm_and_si128(conditions, values),
                _mm_andnot_si128(conditions, otherwise));
        }

        /*inline bool64x2 less_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline bool64x2 less_equal_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline bool64x2 greater_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }

        inline bool64x2 greater_equal_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            // TODO
        }*/

        inline bool64x2 equal_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            const auto cmp = _mm_cmpeq_epi32(lhs, rhs);
            const auto hi = _mm_shuffle_epi32(cmp, _MM_SHUFFLE(3, 3, 1, 1));
            const auto lo = _mm_shuffle_epi32(cmp, _MM_SHUFFLE(2, 2, 0, 0));
            return _mm_and_si128(hi, lo);
        }

        inline bool64x2 not_equal_ss(
            const uint64x2& lhs, const uint64x2& rhs) noexcept
        {
            return _mm_xor_si128(equal_ss(lhs, rhs), uint64x2(~0ull));
        }
    }
}