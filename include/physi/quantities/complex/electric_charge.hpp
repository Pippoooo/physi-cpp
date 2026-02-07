#pragma once

#include "../../core/quantity.hpp"
#include "../electric_current.hpp"
#include "../time.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(electric_charge)

PHYSI_UNIT(electric_charge, C, 1.0)
PHYSI_UNIT(electric_charge, mC, 0.001)
PHYSI_UNIT(electric_charge, uC, 0.000001)
PHYSI_UNIT(electric_charge, nC, 0.000000001)
PHYSI_UNIT(electric_charge, Ah, 3600.0)
PHYSI_UNIT(electric_charge, mAh, 3.6)

PHYSI_QUANTITY_END(electric_charge)

namespace literals {

PHYSI_LITERAL(electric_charge_ld, C)
PHYSI_LITERAL(electric_charge_ld, mC)
PHYSI_LITERAL(electric_charge_ld, uC)
PHYSI_LITERAL(electric_charge_ld, nC)
PHYSI_LITERAL(electric_charge_ld, Ah)
PHYSI_LITERAL(electric_charge_ld, mAh)

} // namespace literals

PHYSI_BINARY_OP(electric_charge, electric_current, MUL, time)

} // namespace physi