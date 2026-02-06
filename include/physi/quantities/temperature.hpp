#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(temperature)

PHYSI_UNIT(temperature, K, 1.0)

PHYSI_QUANTITY_END(temperature)

namespace literals {

PHYSI_LITERAL(temperature_ld, K)

} // namespace literals

} // namespace physi