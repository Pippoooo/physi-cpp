// File: tests/test_api_usage.cpp
// New Catch2-based unit tests demonstrating the API usage from your example.
// This file is additive — it does not modify any existing files.

#include <catch2/catch_all.hpp>
#include <type_traits>

#include "../include/physi/physi.hpp"

using namespace physi;
using namespace physi::literals;

TEST_CASE("API: literals, conversions, mixed-precision arithmetic and "
          "mass/volume examples") {
    // create quantities using literals
    length_f l_m = 2.0_m;

    // 2 meters -> feet (approx 6.56168 ft)
    float l_ft = l_m.ft();
    REQUIRE(l_ft == Catch::Approx(6.56168f).epsilon(1e-5f));

    // static factory from feet: 100 ft -> 30.48 m
    float c = 100.0f;
    length_d l_ft2 = length_d::ft(c);
    REQUIRE(l_ft2.m() == Catch::Approx(30.48).epsilon(1e-12));

    // implicit conversion between precisions (float -> double)
    length_d l_ft3 = l_m; // float length -> double length
    REQUIRE(l_ft3.m() == Catch::Approx(2.0).epsilon(1e-12));

    // mass literal and lb conversion (20 oz == 1.25 lb)
    mass_f m1 = 20_oz;
    REQUIRE(m1.lb() == Catch::Approx(1.25f).epsilon(1e-6f));

    // mixed-precision arithmetic: double + double -> long double when combined
    // with long double
    length_ld ll = l_ft2 + l_ft3;
    REQUIRE(ll.m() == Catch::Approx(32.48L).epsilon(1e-12L));

    // converting down to float (mixed addition where result is converted to
    // float alias)
    length_f ll2 = l_ft2 + ll;
    REQUIRE(ll2.m() == Catch::Approx(62.96f).epsilon(1e-5f));

    // round-trip ft/m consistency for the float result
    float ft_back = ll2.ft();
    REQUIRE(ft_back == Catch::Approx(ll2.m() * 3.28084f).epsilon(1e-4f));

    // Some compile-time sanity checks on types / implicit conversions
    STATIC_REQUIRE(std::is_same_v<decltype(l_m), length_f>);
    STATIC_REQUIRE(std::is_same_v<decltype(l_ft2), length_d>);
    STATIC_REQUIRE(std::is_same_v<decltype(ll), length_ld>);
}

TEST_CASE("Arithmetic & compound assignments across precisions") {
    length_f a = 1.5_m;
    length_d b = 2.25_m;
    length_ld c = 3.75_m;

    // mixed additions produce common_type-based quantity types
    auto sum_ab = a + b; // should be length<double>
    REQUIRE(sum_ab.m() ==
            Catch::Approx(static_cast<double>(1.5f) + 2.25).epsilon(1e-12));

    auto sum_abc = a + b + c; // should be length<long double>
    REQUIRE(sum_abc.m() ==
            Catch::Approx(static_cast<long double>(1.5f) + 2.25L + 3.75L)
                .epsilon(1e-12L));

    // compound assignment works with other precisions
    length_d d = 1.0_m;
    d += a; // add length_f to length_d
    REQUIRE(d.m() ==
            Catch::Approx(1.0 + static_cast<double>(1.5f)).epsilon(1e-12));

    // scalar multiplication and division (including scalar first)
    auto scaled1 = 2.0 * a; // scalar * quantity
    REQUIRE(scaled1.m() == Catch::Approx(3.0).epsilon(1e-6));

    auto scaled2 = b * 0.5; // quantity * scalar
    REQUIRE(scaled2.m() == Catch::Approx(1.125).epsilon(1e-12));

    auto ratio =
        b / a; // quantity / quantity -> scalar (double/float -> double)
    REQUIRE(ratio == Catch::Approx(2.25 / 1.5).epsilon(1e-6));
}

TEST_CASE("Temperature conversions") {

    temperature_f t1 = 100.0_K;
    REQUIRE(t1.K() == Catch::Approx(100.0));

    // Water freezing point: 0°C = 273.15 K
    temperature_f t2 = temperature_f::C(0);
    REQUIRE(t2.K() == Catch::Approx(273.15));

    // Water boiling point: 100°C = 373.15 K
    temperature_f t3 = temperature_f::C(100);
    REQUIRE(t3.K() == Catch::Approx(373.15));

    // Absolute zero: -273.15°C = 0 K
    temperature_f t4 = temperature_f::C(-273.15);
    REQUIRE(t4.K() == Catch::Approx(0.0).margin(0.01));

    // Water freezing point: 32°F = 273.15 K
    temperature_f t5 = temperature_f::F(32);
    REQUIRE(t5.K() == Catch::Approx(273.15));

    // Water boiling point: 212°F = 373.15 K
    temperature_f t6 = temperature_f::F(212);
    REQUIRE(t6.K() == Catch::Approx(373.15));

    // Absolute zero: -459.67°F = 0 K
    temperature_f t7 = temperature_f::F(-459.67);
    REQUIRE(t7.K() == Catch::Approx(0.0).margin(0.01));

    // Room temperature: 68°F ≈ 293.15 K (20°C)
    temperature_f t8 = temperature_f::F(68);
    REQUIRE(t8.K() == Catch::Approx(293.15).margin(0.1));
}