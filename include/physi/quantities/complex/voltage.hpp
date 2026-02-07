#pragma once

#include "../../core/quantity.hpp"
#include "../electric_current.hpp"
#include "resistance.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(voltage)

PHYSI_UNIT(voltage, V, 1.0)
PHYSI_UNIT(voltage, mV, 0.001)
PHYSI_UNIT(voltage, kV, 1000.0)
PHYSI_UNIT(voltage, MV, 1000000.0)

PHYSI_QUANTITY_END(voltage)

namespace literals {

PHYSI_LITERAL(voltage_ld, V)
PHYSI_LITERAL(voltage_ld, mV)
PHYSI_LITERAL(voltage_ld, kV)
PHYSI_LITERAL(voltage_ld, MV)

} // namespace literals

PHYSI_BINARY_OP(voltage, resistance, MUL, electric_current)

} // namespace physi