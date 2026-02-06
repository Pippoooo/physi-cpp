#pragma once

#include "../core/quantity.hpp"

namespace physi {

PHYSI_QUANTITY_BEGIN(amount_of_substance)

PHYSI_UNIT(amount_of_substance, mol, 1.0)
PHYSI_UNIT(amount_of_substance, mmol, 0.001)
PHYSI_UNIT(amount_of_substance, umol, 0.000001)
PHYSI_UNIT(amount_of_substance, kmol, 1000.0)

PHYSI_QUANTITY_END(amount_of_substance)

namespace literals {

PHYSI_LITERAL(amount_of_substance_ld, mol)
PHYSI_LITERAL(amount_of_substance_ld, mmol)
PHYSI_LITERAL(amount_of_substance_ld, umol)
PHYSI_LITERAL(amount_of_substance_ld, kmol)

} // namespace literals

} // namespace physi