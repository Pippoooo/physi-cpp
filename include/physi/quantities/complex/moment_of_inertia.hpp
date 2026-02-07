#pragma once

#include "../../core/quantity.hpp"
#include "../mass.hpp"
#include "area.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(moment_of_inertia)

PHYSI_UNIT(moment_of_inertia, kg_m2, 1.0)
PHYSI_UNIT(moment_of_inertia, g_cm2, 0.0000001)
PHYSI_UNIT(moment_of_inertia, lb_ft2, 0.0421401)

PHYSI_QUANTITY_END(moment_of_inertia)

namespace literals {

PHYSI_LITERAL(moment_of_inertia_ld, kg_m2)
PHYSI_LITERAL(moment_of_inertia_ld, g_cm2)
PHYSI_LITERAL(moment_of_inertia_ld, lb_ft2)

} // namespace literals

PHYSI_BINARY_OP(moment_of_inertia, mass, MUL, area)

} // namespace physi