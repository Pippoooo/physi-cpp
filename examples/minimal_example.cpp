#include "physi/physi.hpp"
#include <iomanip>
#include <iostream>

int main() {
    using namespace physi;
    using namespace physi::literals;

    std::cout << std::fixed << std::setprecision(6);

    {
        // -------------------------
        // scalar quantities & ops
        // -------------------------
        // create quantities using literals and factories
        length_f l_m = 2.0_m;  // 2 meters (float)
        float l_ft = l_m.ft(); // convert to feet (float)

        float c = 100.0f;
        length_d l_ft2 = length_d::ft(c); // 100 ft as double
        length_d l_ft3 = l_m;             // implicit float->double conversion

        mass_f m1 = 20_oz; // mass literal (ounces)

        length_ld ll =
            l_ft2 + l_ft3;         // mixed-precision arithmetic -> long double
        length_f ll2 = l_ft2 + ll; // converts down to float alias

        time_f t = 10_s;

        speed_f s = 10_m / 10_s; // automatic unit conversion with operations.
        float s_kmh = s.km_h();  // show in km/h

        // inverse operations work too!
        length_f travel = s * 10_s; // speed * time -> length

        acceleration_f a = s / 10_s; // speed / time -> acceleration
        acceleration_f a2 = 10_m / 10_s / 10_s;
        acceleration_f a3 = 10_km_h / 10_s;

        // print scalar examples
        std::cout << "=== Scalars / basic units ===\n";
        std::cout << "l_m = " << l_m.m() << " m  (=" << l_ft << " ft)\n";
        std::cout << "100 ft = " << l_ft2.m() << " m (double)\n";
        std::cout << "mixed long double ll = " << ll.m() << " m\n";
        std::cout << "ll2 (float alias) = " << ll2.m() << " m\n";
        std::cout << "mass m1 = " << m1.lb() << " lb (" << m1.base_value()
                  << " kg base_value())\n";
        std::cout << "speed s = " << s.base_value() << " m/s (" << s_kmh
                  << " km/h)\n";
        std::cout << "travel = s * 10s = " << travel.m() << " m\n";
        std::cout << "acceleration a = s / 10s = " << a.base_value()
                  << " m/s^2\n\n";
    }
    // -------------------------
    // vec construction & access
    // -------------------------
    std::cout << "=== Vectors (vec2/vec3) ===\n";

    // default / broadcast / component constructors
    vec3<length_f> v_default; // default ctor -> zeros
    vec3<length_f> v_components(10_m, 20_m, 30_m);
    vec3<length_f> v_broadcast(5_m);
    vec2<speed_f> v2_speed(10_m_s, 20_m_s);
    vec3<length_f> v_init = {1_m, 2_m, 3_m};

    std::cout << "v_components = (" << v_components.x().base_value() << ", "
              << v_components.y().base_value() << ", "
              << v_components.z().base_value() << ") m\n";

    std::cout << "v_broadcast = (" << v_broadcast.x().base_value() << ", "
              << v_broadcast.y().base_value() << ", "
              << v_broadcast.z().base_value() << ") m\n";

    // array-style access
    std::cout << "v_init[1] = " << v_init[1].base_value() << " m\n";

    // raw glm access
    glm::vec3 raw = v_components.base_value();
    std::cout << "raw glm vec from v_components = (" << raw.x << ", " << raw.y
              << ", " << raw.z << ")\n\n";

    // -------------------------
    // vec arithmetic
    // -------------------------
    std::cout << "=== Vector arithmetic ===\n";

    vec3<length_f> a = {1_m, 2_m, 3_m};
    vec3<length_f> b = {4_m, 5_m, 6_m};

    vec3<length_f> sum = a + b;
    vec3<length_f> diff = a - b;

    std::cout << "a + b = (" << sum.x().base_value() << ", "
              << sum.y().base_value() << ", " << sum.z().base_value()
              << ") m\n";
    std::cout << "a - b = (" << diff.x().base_value() << ", "
              << diff.y().base_value() << ", " << diff.z().base_value()
              << ") m\n";

    // compound ops
    vec3<length_f> aa = a;
    aa += b;
    std::cout << "a += b -> a = (" << aa.x().base_value() << ", "
              << aa.y().base_value() << ", " << aa.z().base_value() << ") m\n";

    // scalar multiply / divide
    vec3<length_f> scaled = a * 2.0f;
    vec3<length_f> scaled2 = 3.0f * a; // commutative
    std::cout << "a * 2 = (" << scaled.x().base_value() << ", "
              << scaled.y().base_value() << ", " << scaled.z().base_value()
              << ") m\n";
    std::cout << "3 * a = (" << scaled2.x().base_value() << ", "
              << scaled2.y().base_value() << ", " << scaled2.z().base_value()
              << ") m\n";

    // component-wise multiplication -> Hadamard (length * length -> area)
    vec3<area_f> hadamard = a * b;
    std::cout << "a * b (component-wise area) = (" << hadamard.x().base_value()
              << ", " << hadamard.y().base_value() << ", "
              << hadamard.z().base_value() << ") m^2\n";

    // component-wise division producing unitless components
    auto comp_div =
        vec3<length_f>{10_m, 20_m, 30_m} / vec3<length_f>{2_m, 4_m, 5_m};
    std::cout << "component-wise division (unitless): (" << comp_div.x << ", "
              << comp_div.y << ", " << comp_div.z << ")\n\n";

    // -------------------------
    // dot, cross, magnitude, normalize
    // -------------------------
    std::cout << "=== Dot / Cross / Magnitude / Normalized ===\n";

    vec3<force_f> F = {10_N, 0_N, 0_N};
    vec3<length_f> disp = {5_m, 0_m, 0_m};
    energy_f work = F.dot(disp);
    std::cout << "Work = F · displacement = " << work.base_value()
              << " J (energy)\n";

    vec3<length_f> aa3 = {3_m, 4_m, 0_m};
    length_f mag = aa3.length();
    std::cout << "length(3,4,0) = " << mag.base_value() << " m\n";

    auto dir = aa3.normalized(); // unitless direction vector
    std::cout << "normalized direction (unitless) = (" << dir.x << ", " << dir.y
              << ", " << dir.z << ")\n";

    vec3<length_f> p = {1_m, 2_m, 3_m};
    vec3<length_f> q = {4_m, 5_m, 6_m};
    vec3<area_f> cross_pq = p.cross(q);
    std::cout << "p x q = (" << cross_pq.x().base_value() << ", "
              << cross_pq.y().base_value() << ", " << cross_pq.z().base_value()
              << ") m^2\n\n";

    // -------------------------
    // physics-ish example with vectors
    // -------------------------
    std::cout << "=== Small physics demo: motion integration ===\n";

    vec3<length_f> position = {0_m, 10_m, 0_m};
    vec3<speed_f> velocity = {5_m_s, 10_m_s, 0_m_s};
    vec3<acceleration_f> gravity = {0_m_s2, -9.8_m_s2, 0_m_s2};
    time_f dt = 0.1_s;

    // update velocity: v = v + a * dt
    vec3<speed_f> new_vel = velocity + gravity * dt;
    std::cout << "initial vel = (" << velocity.x().base_value() << ", "
              << velocity.y().base_value() << ", " << velocity.z().base_value()
              << ") m/s\n";
    std::cout << "after dt vel = (" << new_vel.x().base_value() << ", "
              << new_vel.y().base_value() << ", " << new_vel.z().base_value()
              << ") m/s\n";

    // update position: s = s + v * dt
    vec3<length_f> new_pos = position + velocity * dt;
    std::cout << "new position = (" << new_pos.x().base_value() << ", "
              << new_pos.y().base_value() << ", " << new_pos.z().base_value()
              << ") m\n\n";

    // -------------------------
    // show vector raw pointer access
    // -------------------------
    const float *data_ptr = v_components.data_ptr();
    std::cout << "v_components.data_ptr(): [" << data_ptr[0] << ", "
              << data_ptr[1] << ", " << data_ptr[2] << "]\n";

    std::cout << "\n=== Done — physi vec examples ===\n";
    return 0;
}
