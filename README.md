# physi — minimal header-only units library

This repository is a small header-only C++ library providing physics unit types and literals. It includes tests using Catch2 + CTest.

## Features

- **Strong Typing:** Distinct types for Length, Mass, etc.
- **Precision Control:** Explicit aliases for `float` (`_f`), `double` (`_d`), and `long double` (`_ld`) representations.
- **User-Defined Literals:** Intuitive syntax like `2.0_m`, `20_oz`.
- **Mixed-Precision Arithmetic:** Seamlessly add `float` quantities to `double` quantities with correct type promotion.
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
