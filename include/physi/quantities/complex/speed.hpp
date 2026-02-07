#pragma once

#include "../../core/quantity.hpp"
#include "../length.hpp"
#include "../time.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(speed)

PHYSI_UNIT(speed, m_s, 1.0)
PHYSI_UNIT(speed, km_h, 0.277778)
PHYSI_UNIT(speed, mph, 0.44704)
PHYSI_UNIT(speed, fps, 0.3048)
PHYSI_UNIT(speed, knot, 0.514444)
PHYSI_UNIT(speed, mach, 343.0)
PHYSI_UNIT(speed, c, 299792458.0)

PHYSI_QUANTITY_END(speed)

namespace literals {

PHYSI_LITERAL(speed_ld, m_s)
PHYSI_LITERAL(speed_ld, km_h)
PHYSI_LITERAL(speed_ld, mph)
PHYSI_LITERAL(speed_ld, fps)
PHYSI_LITERAL(speed_ld, knot)
PHYSI_LITERAL(speed_ld, mach)
PHYSI_LITERAL(speed_ld, c)

} // namespace literals

PHYSI_BINARY_OP(speed, length, DIV, time)

} // namespace physi
