#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(electric_current)

PHYSI_UNIT(electric_current, A, 1.0)
PHYSI_UNIT(electric_current, mA, 0.001)
PHYSI_UNIT(electric_current, uA, 0.000001)
PHYSI_UNIT(electric_current, kA, 1000.0)

PHYSI_QUANTITY_END(electric_current)

namespace literals {

PHYSI_LITERAL(electric_current_ld, A)
PHYSI_LITERAL(electric_current_ld, mA)
PHYSI_LITERAL(electric_current_ld, uA)
PHYSI_LITERAL(electric_current_ld, kA)

} // namespace literals

} // namespace physi