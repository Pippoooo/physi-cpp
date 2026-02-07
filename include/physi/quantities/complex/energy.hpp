#pragma once

#include "../../core/quantity.hpp"
#include "../length.hpp"
#include "../time.hpp"
#include "electric_charge.hpp"
#include "force.hpp"
#include "power.hpp"
#include "voltage.hpp"

namespace physi {

// work, energy, heat all share the same dimension: ML²T⁻²
PHYSI_QUANTITY_BEGIN(energy)

PHYSI_UNIT(energy, J, 1.0)
PHYSI_UNIT(energy, kJ, 1000.0)
PHYSI_UNIT(energy, MJ, 1000000.0)
PHYSI_UNIT(energy, GJ, 1000000000.0)
PHYSI_UNIT(energy, mJ, 0.001)
PHYSI_UNIT(energy, cal, 4.184)
PHYSI_UNIT(energy, kcal, 4184.0)
PHYSI_UNIT(energy, Wh, 3600.0)
PHYSI_UNIT(energy, kWh, 3600000.0)
PHYSI_UNIT(energy, eV, 1.602176634e-19)
PHYSI_UNIT(energy, BTU, 1055.06)

PHYSI_QUANTITY_END(energy)

namespace literals {

PHYSI_LITERAL(energy_ld, J)
PHYSI_LITERAL(energy_ld, kJ)
PHYSI_LITERAL(energy_ld, MJ)
PHYSI_LITERAL(energy_ld, GJ)
PHYSI_LITERAL(energy_ld, mJ)
PHYSI_LITERAL(energy_ld, cal)
PHYSI_LITERAL(energy_ld, kcal)
PHYSI_LITERAL(energy_ld, Wh)
PHYSI_LITERAL(energy_ld, kWh)
PHYSI_LITERAL(energy_ld, eV)
PHYSI_LITERAL(energy_ld, BTU)

} // namespace literals

PHYSI_BINARY_OP(energy, force, MUL, length)
PHYSI_BINARY_OP(energy, power, MUL, time)
PHYSI_BINARY_OP(energy, voltage, MUL, electric_charge)

} // namespace physi