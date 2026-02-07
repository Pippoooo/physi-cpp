#pragma once

#include "../../core/quantity.hpp"
#include "../electric_current.hpp"
#include "voltage.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(resistance)

PHYSI_UNIT(resistance, ohm, 1.0)
PHYSI_UNIT(resistance, kohm, 1000.0)
PHYSI_UNIT(resistance, Mohm, 1000000.0)
PHYSI_UNIT(resistance, milliohm, 0.001)

PHYSI_QUANTITY_END(resistance)

namespace literals {

PHYSI_LITERAL(resistance_ld, ohm)
PHYSI_LITERAL(resistance_ld, kohm)
PHYSI_LITERAL(resistance_ld, Mohm)
PHYSI_LITERAL(resistance_ld, milliohm)

} // namespace literals

} // namespace physi