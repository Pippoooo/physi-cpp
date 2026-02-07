#pragma once

#include "../../core/quantity.hpp"
#include "../time.hpp"
#include "speed.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(acceleration)

PHYSI_UNIT(acceleration, m_s2, 1.0)
PHYSI_UNIT(acceleration, km_s2, 1000.0)
PHYSI_UNIT(acceleration, cm_s2, 0.01)
PHYSI_UNIT(acceleration, ft_s2, 0.3048)

PHYSI_QUANTITY_END(acceleration)

namespace literals {

PHYSI_LITERAL(acceleration_ld, m_s2)
PHYSI_LITERAL(acceleration_ld, km_s2)
PHYSI_LITERAL(acceleration_ld, cm_s2)
PHYSI_LITERAL(acceleration_ld, ft_s2)

} // namespace literals

PHYSI_BINARY_OP(acceleration, speed, DIV, time)

} // namespace physi