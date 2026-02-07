#pragma once

#include "../../core/quantity.hpp"
#include "electric_charge.hpp"
#include "voltage.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(capacitance)

PHYSI_UNIT(capacitance, F, 1.0)
PHYSI_UNIT(capacitance, mF, 0.001)
PHYSI_UNIT(capacitance, uF, 0.000001)
PHYSI_UNIT(capacitance, nF, 0.000000001)
PHYSI_UNIT(capacitance, pF, 0.000000000001)

PHYSI_QUANTITY_END(capacitance)

namespace literals {

PHYSI_LITERAL(capacitance_ld, F)
PHYSI_LITERAL(capacitance_ld, mF)
PHYSI_LITERAL(capacitance_ld, uF)
PHYSI_LITERAL(capacitance_ld, nF)
PHYSI_LITERAL(capacitance_ld, pF)

} // namespace literals

PHYSI_BINARY_OP(capacitance, electric_charge, DIV, voltage)

} // namespace physi