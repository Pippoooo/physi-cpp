# physi — minimal header-only units library

This repository is a small header-only C++ library providing physics unit types and literals. It includes tests using Catch2 + CTest.

## Features

- **Strong Typing:** Distinct types for Length, Mass, Speed, Acceleration, Force, Energy, etc.
- **Precision Control:** Explicit aliases for `float` (`_f`), `double` (`_d`), and `long double` (`_ld`) representations.
- **User-Defined Literals:** Intuitive syntax like `2.0_m`, `20_oz`, `100_km_h`.
- **Mixed-Precision Arithmetic:** Seamlessly add `float` quantities to `double` quantities with correct type promotion.
- **Dimensional Analysis:** Derive complex quantities from basic ones (e.g., `speed = length / time`).
- **Zero-Overhead:** Compile-time dimensional analysis and static type checking.

## Usage

### Basic Literals and Conversions

Initialize quantities using SI literals or static factory methods. Access converted values using named member functions.

```cpp
#include "physi/physi.hpp"

void example() {
    // Initialize using literals (float precision)
    length_f l_m = 2.0_m;

    // Convert to feet
    float l_ft = l_m.ft(); // Returns approx 6.56168

    // Initialize using static factory (double precision)
    length_d l_ft2 = length_d::ft(100.0);

    // Convert to meters
    double meters = l_ft2.m(); // Returns 30.48

    // Mass examples
    mass_f m1 = 20_oz;
    float pounds = m1.lb(); // Returns 1.25
}
```

### Implicit Promotions and Type Safety

The library handles implicit conversions safely. You can assign lower-precision quantities to higher-precision variables, but not vice versa without explicit casting.

```cpp
length_f l_float = 2.0_m;
length_d l_double = l_float; // OK: Implicit float -> double conversion
```

### Arithmetic and Compound Assignment

Perform arithmetic operations on quantities. The result type automatically promotes to the highest precision involved in the operation.

```cpp
length_f a = 1.5_m;
length_d b = 2.25_m;
length_ld c = 3.75_m;

// Mixed addition: float + double -> double
auto sum_ab = a + b;
// sum_ab is length_d (3.75 m)

// Mixed addition: float + double + long double -> long double
auto sum_abc = a + b + c;
// sum_abc is length_ld
```

### Scalar Operations

Multiply or divide quantities by scalars, or divide two quantities to result in a raw scalar ratio.

```cpp
length_f x = 1.5_m;
length_d y = 2.25_m;

// Scalar multiplication
auto scaled1 = 2.0 * x; // 3.0 m
auto scaled2 = y * 0.5; // 1.125 m

// Ratio (Quantity / Quantity -> Scalar)
double ratio = y / x; // 1.5
```

### Derived Quantities

Combine basic quantities to create derived quantities like speed, acceleration, force, and energy using natural operators.

```cpp
// Speed from distance and time
speed_f s1 = 100_m / 10_s;        // 10 m/s
float km_per_h = s1.km_h();       // 36 km/h

// Acceleration from speed and time
acceleration_f a1 = s1 / 5_s;     // 2 m/s²

// Acceleration from distance and time directly
acceleration_f a2 = 100_m / 10_s / 10_s;  // 1 m/s²

// Mixed units
acceleration_f a3 = 36_km_h / 10_s;       // 1 m/s²

// Force from mass and acceleration
force_f f = 10_kg * a1;           // 20 N

// Energy from force and distance
energy_f e = f * 5_m;             // 100 J
```

### Unit Conversions

All quantities support conversion between compatible units.

```cpp
// Speed conversions
speed_f v = 60_mi / 1_hr;
float kmh = v.km_h();             // ~96.56 km/h
float ms = v.m_s();               // ~26.82 m/s

// Acceleration conversions
acceleration_f a = 100_cm_s2;
float m_s2 = a.m_s2();            // 1.0 m/s²

// Energy conversions
energy_f e = 1_kWh;
float joules = e.J();             // 3,600,000 J
float kcal = e.kcal();            // ~860 kcal
```

### Real-World Examples

```cpp
// Car acceleration: 0 to 100 km/h in 8 seconds
speed_f final_speed = 100_km_h;
time_f time = 8_s;
acceleration_f accel = final_speed / time;  // ~0.35 g

// Kinetic energy calculation
mass_f car_mass = 1500_kg;
speed_f car_speed = 100_km_h;
energy_f kinetic = 0.5 * car_mass * car_speed * car_speed;

// Power consumption
energy_f consumed = 2.5_kWh;
time_f duration = 1_hr;
power_f avg_power = consumed / duration;  // 2.5 kW
```
