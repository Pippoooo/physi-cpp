#pragma once

#include "../../core/quantity.hpp"
#include "../mass.hpp"
#include "accelleration.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(force)

PHYSI_UNIT(force, N, 1.0)
PHYSI_UNIT(force, kN, 1000.0)
PHYSI_UNIT(force, mN, 0.001)
PHYSI_UNIT(force, MN, 1000000.0)
PHYSI_UNIT(force, dyn, 0.00001)
PHYSI_UNIT(force, lbf, 4.44822)
PHYSI_UNIT(force, kgf, 9.80665)

PHYSI_QUANTITY_END(force)

namespace literals {

PHYSI_LITERAL(force_ld, N)
PHYSI_LITERAL(force_ld, kN)
PHYSI_LITERAL(force_ld, mN)
PHYSI_LITERAL(force_ld, MN)
PHYSI_LITERAL(force_ld, dyn)
PHYSI_LITERAL(force_ld, lbf)
PHYSI_LITERAL(force_ld, kgf)

} // namespace literals

PHYSI_BINARY_OP(force, mass, MUL, acceleration)

} // namespace physi