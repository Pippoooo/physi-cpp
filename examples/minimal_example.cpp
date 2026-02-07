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

    time_f t = 10_s;

    speed_f s = 10_m / 10_s; // automatic unit conversion with operations.
    s.km_h();

    // inverse operations work too!
    length_f travel = s * 10_s;

    acceleration_f a = s / 10_s;
    acceleration_f a2 = 10_m / 10_s / 10_s;
    acceleration_f a3 = 10_km_h / 10_s;

    speed_f accellerated = a3 * 2.5_s;

    std::cout << ll2.m() << " m, " << m1.lb() << " lb, " << ll.ft() << " ft\n";

    return 0;
}
