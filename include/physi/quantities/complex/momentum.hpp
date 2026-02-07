#pragma once

#include "../../core/quantity.hpp"
#include "../mass.hpp"
#include "speed.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(momentum)

PHYSI_UNIT(momentum, kg_m_per_s, 1.0)
PHYSI_UNIT(momentum, g_m_per_s, 0.001)
PHYSI_UNIT(momentum, g_cm_per_s, 0.00001)
PHYSI_UNIT(momentum, lb_ft_per_s, 0.138255)

PHYSI_QUANTITY_END(momentum)

namespace literals {

PHYSI_LITERAL(momentum_ld, kg_m_per_s)
PHYSI_LITERAL(momentum_ld, g_m_per_s)
PHYSI_LITERAL(momentum_ld, g_cm_per_s)
PHYSI_LITERAL(momentum_ld, lb_ft_per_s)

} // namespace literals

PHYSI_BINARY_OP(momentum, mass, MUL, speed)

} // namespace physi