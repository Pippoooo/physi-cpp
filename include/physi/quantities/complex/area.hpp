#pragma once

#include "../../core/quantity.hpp"
#include "../length.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(area)

PHYSI_UNIT(area, m2, 1.0)
PHYSI_UNIT(area, km2, 1000000.0)
PHYSI_UNIT(area, cm2, 0.0001)
PHYSI_UNIT(area, mm2, 0.000001)
PHYSI_UNIT(area, ft2, 0.092903)
PHYSI_UNIT(area, in2, 0.00064516)
PHYSI_UNIT(area, acre, 4046.86)
PHYSI_UNIT(area, hectare, 10000.0)

PHYSI_QUANTITY_END(area)

namespace literals {

PHYSI_LITERAL(area_ld, m2)
PHYSI_LITERAL(area_ld, km2)
PHYSI_LITERAL(area_ld, cm2)
PHYSI_LITERAL(area_ld, mm2)
PHYSI_LITERAL(area_ld, ft2)
PHYSI_LITERAL(area_ld, in2)
PHYSI_LITERAL(area_ld, acre)
PHYSI_LITERAL(area_ld, hectare)

} // namespace literals

template <typename U, typename N>
[[nodiscard]] constexpr area<std::common_type_t<U, N>>
operator*(const length<U> &lhs, const length<N> &rhs) noexcept {
    using R = std::common_type_t<U, N>;
    return area<R>(static_cast<R>(lhs.base_value()) *
                   static_cast<R>(rhs.base_value()));
}

template <typename U, typename N>
[[nodiscard]] constexpr length<std::common_type_t<U, N>>
operator/(const area<U> &lhs, const length<N> &rhs) noexcept {
    using R = std::common_type_t<U, N>;
    return length<R>(static_cast<R>(lhs.base_value()) /
                     static_cast<R>(rhs.base_value()));
}

} // namespace physi