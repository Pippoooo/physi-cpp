#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(time)

PHYSI_UNIT(time, s, 1.0)
PHYSI_UNIT(time, ms, 0.001)
PHYSI_UNIT(time, us, 0.000001)
PHYSI_UNIT(time, ns, 0.000000001)
PHYSI_UNIT(time, min, 60.0)
PHYSI_UNIT(time, hr, 3600.0)
PHYSI_UNIT(time, day, 86400.0)
PHYSI_UNIT(time, wk, 604800.0)
PHYSI_UNIT(time, yr, 31557600.0)

PHYSI_QUANTITY_END(time)

namespace literals {

PHYSI_LITERAL(time_ld, s)
PHYSI_LITERAL(time_ld, ms)
PHYSI_LITERAL(time_ld, us)
PHYSI_LITERAL(time_ld, ns)
PHYSI_LITERAL(time_ld, min)
PHYSI_LITERAL(time_ld, hr)
PHYSI_LITERAL(time_ld, day)
PHYSI_LITERAL(time_ld, wk)
PHYSI_LITERAL(time_ld, yr)

} // namespace literals

} // namespace physi