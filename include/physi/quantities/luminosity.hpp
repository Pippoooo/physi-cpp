#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(luminous_intensity)

PHYSI_UNIT(luminous_intensity, cd, 1.0)

PHYSI_QUANTITY_END(luminous_intensity)

namespace literals {

PHYSI_LITERAL(luminous_intensity_ld, cd)

} // namespace literals

} // namespace physi