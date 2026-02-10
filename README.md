# physi — minimal header-only units & vectors library

A compact, header-only C++ library providing strongly-typed physics quantities (length, mass, time, force, energy, …), user-friendly unit literals, safe mixed-precision arithmetic, and small `vec2`/`vec3` containers that interoperate with `glm::vec*`. Zero-overhead, compile-time dimensional checks and expressive, natural syntax.

---

## Table of contents

- [Why physi](#why-physi)
- [Quick start](#quick-start)
- [Core concepts & most useful features (ordered)](#core-concepts--most-useful-features-ordered)
  - [1. Literals and factories (fast to use)](#1-literals-and-factories-fast-to-use)
  - [2. Dimensional arithmetic & inverses (safety + convenience)](#2-dimensional-arithmetic--inverses-safety--convenience)
  - [3. Mixed-precision & type promotion (no surprises)](#3-mixed-precision--type-promotion-no-surprises)
  - [4. Conversions and named accessors (human-friendly)](#4-conversions-and-named-accessors-human-friendly)
  - [5. `vec2` / `vec3` (small vector types with physics units)](#5-vec2--vec3-small-vector-types-with-physics-units)

- [Building, testing, installing](#building-testing-installing)
- [API reference (quick)](#api-reference-quick)

---

## Why physi

- Gives compile-time dimensional checks so you can’t accidentally add incompatible units.
- Expressive literals like `2.0_m`, `100_km_h`, `20_oz`.
- Header-only — drop into a project easily.
- Small `vec` helpers so your physical vectors carry units (no spreadsheet of scalars!).
- Works with `glm` for low-level vector math (raw access & conversions).

---

## Quick start

Add the repository to your project (one of the options below).

**As a local dependency**

```cmake
add_subdirectory(path/to/physi)
target_link_libraries(myapp PRIVATE physi::physi)
```

**If installed system-wide**

```cmake
find_package(physi CONFIG REQUIRED)
target_link_libraries(myapp PRIVATE physi::physi)
```

`physi` is header-only; linking the interface target is enough. The project bundles GLM headers (so downstream users don’t need to preinstall GLM).

---

## Core concepts & most useful features (ordered)

### 1. Literals and factories (fast to use)

Create quantities with UDLs or static factories.

```cpp
using namespace physi;
using namespace physi::literals;

length_f d = 2.0_m;         // 2 meters (float alias)
time_f   t = 10_s;          // 10 seconds
mass_f   m = 20_oz;         // ounces -> mass
length_d d2 = length_d::ft(100.0); // 100 ft as double
```

### 2. Dimensional arithmetic & inverses (safety + convenience)

Operators are dimension-aware:

```cpp
speed_f v = 100_m / 10_s;   // length / time -> speed
length_f traveled = v * 10_s; // speed * time -> length
time_f   travel_time = 100_m / v; // length / speed -> time
```

(Algebraic inverses are provided so `a/b -> c` implies overloads for `c*b -> a` and `a/c -> b` when meaningful.)

### 3. Mixed-precision & type promotion (no surprises)

Operations promote with `std::common_type` semantics:

```cpp
length_f  f = 1.5_m;   // float
length_d  d = 2.25_m;  // double
auto sum = f + d;      // promoted to length_d (double)
```

Assignments to higher precision are implicit; narrowing requires an explicit cast.

### 4. Conversions and named accessors (human-friendly)

Every quantity exposes easy conversion helpers:

```cpp
float feet = d.ft();       // meters -> feet (float)
double meters = d2.m();    // double result
float kmh = (100_km / 1_hr).km_h();
```

### 5. `vec2` / `vec3` (small vector types with physics units)

Vectors carry units on each component and support vector ops, dot/cross, magnitude, normalization, and raw `glm` interoperability.

```cpp
vec3<length_f> pos = {1_m, 2_m, 3_m};
vec3<speed_f> vel = {5_m_s, 10_m_s, 0_m_s};

vec3<length_f> newpos = pos + vel * 0.1_s; // vector arithmetic with units

// dot/cross
area_f area = vec3<length_f>{3_m,0,0}.dot(vec3<length_f>{0,4_m,0});
vec3<area_f> torque = vec3<length_f>{1_m,0,0}.cross(vec3<force_f>{0,10_N,0});

// raw glm interoperability:
glm::vec3 raw = pos.base_value();   // glm::vec3 of base (floating) values
const float *ptr = pos.data_ptr();
```

---

## Building, testing, installing

This project uses CMake + Catch2 + CTest. The repository bundles a `examples/` and `tests/` folder.

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
ctest --output-on-failure
```

If you are using `FetchContent` for dependencies (e.g., GLM), the top-level CMake file already fetches what is needed; the install step copies GLM headers into the install include dir so consumers need not preinstall them.

---

## API reference (quick)

> Note: this is a compact reference — the code headers contain fuller docs and unit tests demonstrate many more combinations.

### Quantity types

Type aliases are provided for common precisions:

- `length_f`, `length_d`, `length_ld`
- `time_f`, `time_d`, `time_ld`
- `mass_f`, `force_f`, `energy_f`, `power_f`, `speed_f`, `acceleration_f`, `area_f`, `volume_f`, …

### Literal syntax

- `2.0_m`, `10_s`, `100_km`, `60_mi`, `20_oz`, `1_kWh`, `100_km_h`, `1_m_s2`, etc.

### Conversions

Member functions return values in chosen units:

- `l.m()`, `l.ft()`, `s.km_h()`, `e.J()`, `e.kcal()`, `a.m_s2()`, …

### Arithmetic & semantics

- `length / time -> speed`
- `speed * time -> length`
- `length / speed -> time`
- `mass * acceleration -> force`
- `force * length -> energy`
- Mixed-precision math uses `std::common_type` for result precision.
- `Quantity / Quantity` can return a plain scalar ratio (built-in type).

### `vec2<T>` / `vec3<T>`

- Constructors: default, component-wise, broadcast, initializer-list.
- Component accessors: `.x()`, `.y()`, `.z()` return quantity references.
- Arithmetic: `+`, `-`, component-wise `*` (Hadamard), component-wise `/`.
- Compound assignment: `+=`, `-=`, `*=`, `/=` with scalars and vectors.
- Dot product: `a.dot(b)` producing a derived quantity.
- Cross product: `a.cross(b)` (3D only) producing oriented-area quantities.
- Magnitude/normalize: `.length()`, `.magnitude_squared()`, `.normalized()` (returns unitless direction vector).
- Raw access: `.base_value()` returns `glm::vec*` of the stored base values; `.data_ptr()` gives pointer to raw scalar array.

---

## Tests & stability

Tests are implemented with Catch2 in `tests/` and run via CTest. Example tests show coverage for:

- UDL and factory correctness
- Conversions & tolerances
- Mixed-precision arithmetic
- Vector ops, dot/cross, magnitude
- Derived-quantity correctness (force, energy, acceleration, etc.)
