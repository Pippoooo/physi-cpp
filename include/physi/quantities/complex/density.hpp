#pragma once

#include "../../core/quantity.hpp"
#include "../mass.hpp"
#include "volume.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(density)

PHYSI_UNIT(density, kg_m3, 1.0)
PHYSI_UNIT(density, g_cm3, 1000.0)
PHYSI_UNIT(density, kg_L, 1000.0)
PHYSI_UNIT(density, g_mL, 1000.0)
PHYSI_UNIT(density, lb_ft3, 16.0185)
PHYSI_UNIT(density, lb_gal, 119.826)

PHYSI_QUANTITY_END(density)

namespace literals {

PHYSI_LITERAL(density_ld, kg_m3)
PHYSI_LITERAL(density_ld, g_cm3)
PHYSI_LITERAL(density_ld, kg_L)
PHYSI_LITERAL(density_ld, g_mL)
PHYSI_LITERAL(density_ld, lb_ft3)
PHYSI_LITERAL(density_ld, lb_gal)

} // namespace literals

PHYSI_BINARY_OP(density, mass, DIV, volume)

} // namespace physi