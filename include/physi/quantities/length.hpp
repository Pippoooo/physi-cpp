#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(length)

PHYSI_UNIT(length, m, 1.0)
PHYSI_UNIT(length, km, 1000.0)
PHYSI_UNIT(length, cm, 0.01)
PHYSI_UNIT(length, mm, 0.001)
PHYSI_UNIT(length, ft, 0.3048)
PHYSI_UNIT(length, mi, 1609.34)
PHYSI_UNIT(length, in, 0.0254)

PHYSI_QUANTITY_END(length)

namespace literals {

PHYSI_LITERAL(length_ld, m)
PHYSI_LITERAL(length_ld, km)
PHYSI_LITERAL(length_ld, cm)
PHYSI_LITERAL(length_ld, mm)
PHYSI_LITERAL(length_ld, ft)
PHYSI_LITERAL(length_ld, mi)
PHYSI_LITERAL(length_ld, in)

} // namespace literals

} // namespace physi
