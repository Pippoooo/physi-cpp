#pragma once

#include "../../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(pressure)

PHYSI_UNIT(pressure, Pa, 1.0)
PHYSI_UNIT(pressure, kPa, 1000.0)
PHYSI_UNIT(pressure, MPa, 1000000.0)
PHYSI_UNIT(pressure, bar, 100000.0)
PHYSI_UNIT(pressure, mbar, 100.0)
PHYSI_UNIT(pressure, atm, 101325.0)
PHYSI_UNIT(pressure, psi, 6894.76)
PHYSI_UNIT(pressure, torr, 133.322)
PHYSI_UNIT(pressure, mmHg, 133.322)

PHYSI_QUANTITY_END(pressure)

namespace literals {

PHYSI_LITERAL(pressure_ld, Pa)
PHYSI_LITERAL(pressure_ld, kPa)
PHYSI_LITERAL(pressure_ld, MPa)
PHYSI_LITERAL(pressure_ld, bar)
PHYSI_LITERAL(pressure_ld, mbar)
PHYSI_LITERAL(pressure_ld, atm)
PHYSI_LITERAL(pressure_ld, psi)
PHYSI_LITERAL(pressure_ld, torr)
PHYSI_LITERAL(pressure_ld, mmHg)

} // namespace literals

} // namespace physi