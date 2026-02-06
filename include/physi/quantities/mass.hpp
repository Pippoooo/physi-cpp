#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(mass)

PHYSI_UNIT(mass, kg, 1.0)
PHYSI_UNIT(mass, g, 0.001)
PHYSI_UNIT(mass, mg, 0.000001)
PHYSI_UNIT(mass, lb, 0.453592)
PHYSI_UNIT(mass, oz, 0.0283495)

PHYSI_QUANTITY_END(mass)

namespace literals {
PHYSI_LITERAL(mass_ld, kg)
PHYSI_LITERAL(mass_ld, g)
PHYSI_LITERAL(mass_ld, mg)
PHYSI_LITERAL(mass_ld, lb)
PHYSI_LITERAL(mass_ld, oz)

} // namespace literals

} // namespace physi