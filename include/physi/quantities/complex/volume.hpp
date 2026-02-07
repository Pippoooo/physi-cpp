#pragma once

#include "../../core/quantity.hpp"
#include "../length.hpp"
#include "area.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(volume)

PHYSI_UNIT(volume, m3, 1.0)
PHYSI_UNIT(volume, cm3, 0.000001)
PHYSI_UNIT(volume, mm3, 0.000000001)
PHYSI_UNIT(volume, L, 0.001)
PHYSI_UNIT(volume, mL, 0.000001)
PHYSI_UNIT(volume, ft3, 0.0283168)
PHYSI_UNIT(volume, in3, 0.0000163871)
PHYSI_UNIT(volume, gal, 0.00378541)
PHYSI_UNIT(volume, qt, 0.000946353)

PHYSI_QUANTITY_END(volume)

namespace literals {

PHYSI_LITERAL(volume_ld, m3)
PHYSI_LITERAL(volume_ld, cm3)
PHYSI_LITERAL(volume_ld, mm3)
PHYSI_LITERAL(volume_ld, L)
PHYSI_LITERAL(volume_ld, mL)
PHYSI_LITERAL(volume_ld, ft3)
PHYSI_LITERAL(volume_ld, in3)
PHYSI_LITERAL(volume_ld, gal)
PHYSI_LITERAL(volume_ld, qt)

} // namespace literals

PHYSI_BINARY_OP(volume, area, MUL, length)

} // namespace physi