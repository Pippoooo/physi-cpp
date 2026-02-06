#pragma once

#include "../core/quantity.hpp"
#include <iostream>

namespace physi {

PHYSI_QUANTITY_BEGIN(temperature)

PHYSI_UNIT(temperature, K, 1.0)
PHYSI_UNIT_INCREASE(temperature, C, 1.0, 273.15)
PHYSI_UNIT_INCREASE(temperature, F, 0.555556, 459.67)

PHYSI_QUANTITY_END(temperature)

namespace literals {

PHYSI_LITERAL(temperature_ld, K)

} // namespace literals

} // namespace physi