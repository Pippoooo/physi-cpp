#include "physi/physi.hpp"
#include <iostream>

int main() {
    using namespace physi;
    using namespace physi::literals;

    // create quantities using literals and factories
    length_f l_m = 2.0_m;  // 2 meters (float)
    float l_ft = l_m.ft(); // convert to feet (float)

    float c = 100.0f;
    length_d l_ft2 = length_d::ft(c); // 100 ft as double
    length_d l_ft3 = l_m;             // implicit float->double conversion

    mass_f m1 = 20_oz; // mass literal (ounces)

    length_ld ll = l_ft2 + l_ft3; // mixed-precision arithmetic -> long double
    length_f ll2 = l_ft2 + ll;    // converts down to float alias

    std::cout << ll2.m() << " m, " << m1.lb() << " lb, " << ll.ft() << " ft\n";

    return 0;
}
