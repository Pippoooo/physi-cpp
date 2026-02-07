#pragma once

#include "../../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(power)

PHYSI_UNIT(power, W, 1.0)
PHYSI_UNIT(power, kW, 1000.0)
PHYSI_UNIT(power, MW, 1000000.0)
PHYSI_UNIT(power, GW, 1000000000.0)
PHYSI_UNIT(power, mW, 0.001)
PHYSI_UNIT(power, hp, 745.7)
PHYSI_UNIT(power, BTU_per_h, 0.293071)

PHYSI_QUANTITY_END(power)

namespace literals {

PHYSI_LITERAL(power_ld, W)
PHYSI_LITERAL(power_ld, kW)
PHYSI_LITERAL(power_ld, MW)
PHYSI_LITERAL(power_ld, GW)
PHYSI_LITERAL(power_ld, mW)
PHYSI_LITERAL(power_ld, hp)
PHYSI_LITERAL(power_ld, BTU_per_h)

} // namespace literals

} // namespace physi