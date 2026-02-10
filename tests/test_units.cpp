// File: tests/test_api_usage.cpp
// New Catch2-based unit tests demonstrating the API usage from your example.
// This file is additive — it does not modify any existing files.

#include <catch2/catch_all.hpp>
#include <type_traits>

#include "../include/physi/physi.hpp"

using namespace physi;
using namespace physi::literals;
using namespace Catch;

TEST_CASE("API: literals, conversions, mixed-precision arithmetic and "
          "mass/volume examples") {
    // create quantities using literals
    length_f l_m = 2.0_m;

    // 2 meters -> feet (approx 6.56168 ft)
    float l_ft = l_m.ft();
    REQUIRE(l_ft == Approx(6.56168f).epsilon(1e-5f));

    // static factory from feet: 100 ft -> 30.48 m
    float c = 100.0f;
    length_d l_ft2 = length_d::ft(c);
    REQUIRE(l_ft2.m() == Approx(30.48).epsilon(1e-12));

    // implicit conversion between precisions (float -> double)
    length_d l_ft3 = l_m; // float length -> double length
    REQUIRE(l_ft3.m() == Approx(2.0).epsilon(1e-12));

    // mass literal and lb conversion (20 oz == 1.25 lb)
    mass_f m1 = 20_oz;
    REQUIRE(m1.lb() == Approx(1.25f).epsilon(1e-6f));

    // mixed-precision arithmetic: double + double -> long double when combined
    // with long double
    length_ld ll = l_ft2 + l_ft3;
    REQUIRE(ll.m() == Approx(32.48L).epsilon(1e-12L));

    // converting down to float (mixed addition where result is converted to
    // float alias)
    length_f ll2 = l_ft2 + ll;
    REQUIRE(ll2.m() == Approx(62.96f).epsilon(1e-5f));

    // round-trip ft/m consistency for the float result
    float ft_back = ll2.ft();
    REQUIRE(ft_back == Approx(ll2.m() * 3.28084f).epsilon(1e-4f));

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
            Approx(static_cast<double>(1.5f) + 2.25).epsilon(1e-12));

    auto sum_abc = a + b + c; // should be length<long double>
    REQUIRE(
        sum_abc.m() ==
        Approx(static_cast<long double>(1.5f) + 2.25L + 3.75L).epsilon(1e-12L));

    // compound assignment works with other precisions
    length_d d = 1.0_m;
    d += a; // add length_f to length_d
    REQUIRE(d.m() == Approx(1.0 + static_cast<double>(1.5f)).epsilon(1e-12));

    // scalar multiplication and division (including scalar first)
    auto scaled1 = 2.0 * a; // scalar * quantity
    REQUIRE(scaled1.m() == Approx(3.0).epsilon(1e-6));

    auto scaled2 = b * 0.5; // quantity * scalar
    REQUIRE(scaled2.m() == Approx(1.125).epsilon(1e-12));

    auto ratio =
        b / a; // quantity / quantity -> scalar (double/float -> double)
    REQUIRE(ratio == Approx(2.25 / 1.5).epsilon(1e-6));
}

TEST_CASE("Temperature conversions") {

    temperature_f t1 = 100.0_K;
    REQUIRE(t1.K() == Approx(100.0));

    // Water freezing point: 0°C = 273.15 K
    temperature_f t2 = temperature_f::C(0);
    REQUIRE(t2.K() == Approx(273.15));

    // Water boiling point: 100°C = 373.15 K
    temperature_f t3 = temperature_f::C(100);
    REQUIRE(t3.K() == Approx(373.15));

    // Absolute zero: -273.15°C = 0 K
    temperature_f t4 = temperature_f::C(-273.15);
    REQUIRE(t4.K() == Approx(0.0).margin(0.01));

    // Water freezing point: 32°F = 273.15 K
    temperature_f t5 = temperature_f::F(32);
    REQUIRE(t5.K() == Approx(273.15));

    // Water boiling point: 212°F = 373.15 K
    temperature_f t6 = temperature_f::F(212);
    REQUIRE(t6.K() == Approx(373.15));

    // Absolute zero: -459.67°F = 0 K
    temperature_f t7 = temperature_f::F(-459.67);
    REQUIRE(t7.K() == Approx(0.0).margin(0.01));

    // Room temperature: 68°F ≈ 293.15 K (20°C)
    temperature_f t8 = temperature_f::F(68);
    REQUIRE(t8.K() == Approx(293.15).margin(0.1));
}

TEST_CASE("Speed conversions and ations") {

    SECTION("Basic speed from length/time") {
        speed_f s = 10_m / 10_s;
        REQUIRE(s.base_value() == Approx(1.0f)); // 1 m/s
    }

    SECTION("Speed unit conversions") {
        speed_f s1 = 10_m / 1_s;
        REQUIRE(s1.km_h() == Approx(36.0f)); // 10 m/s = 36 km/h

        speed_f s2 = 100_km / 1_hr;
        REQUIRE(s2.base_value() ==
                Approx(27.7778f).margin(0.001f)); // ~27.78 m/s
        REQUIRE(s2.km_h() == Approx(100.0f));

        speed_f s3 = 60_mi / 1_hr;
        REQUIRE(s3.km_h() ==
                Approx(96.56f).margin(0.1f)); // 60 mph ≈ 96.56 km/h
    }

    SECTION("Speed with different literal types") {
        speed_f s1 = 1000_m / 10_s;
        speed_f s2 = 1_km / 10_s;
        REQUIRE(s1.base_value() == Approx(s2.base_value()));
    }
}

TEST_CASE("Acceleration conversions and ations") {

    SECTION("Acceleration from speed/time") {
        speed_f s = 10_m / 1_s;
        acceleration_f a = s / 10_s;
        REQUIRE(a.base_value() == Approx(1.0f)); // 1 m/s²
    }

    SECTION("Acceleration from length/time/time") {
        acceleration_f a1 = 10_m / 10_s / 1_s;
        REQUIRE(a1.base_value() == Approx(1.0f)); // 1 m/s²

        acceleration_f a2 = 100_m / 10_s / 10_s;
        REQUIRE(a2.base_value() == Approx(1.0f)); // 1 m/s²
    }

    SECTION("Acceleration from different speed units") {
        acceleration_f a1 = 36_km_h / 10_s;
        REQUIRE(a1.base_value() ==
                Approx(1.0f).margin(0.01f)); // 36 km/h / 10s = 1 m/s²

        acceleration_f a2 = 10_m_s / 1_s;
        REQUIRE(a2.base_value() == Approx(10.0f)); // 10 m/s²
    }

    SECTION("Acceleration unit conversions") {
        acceleration_f a1 = 1_m_s2;
        REQUIRE(a1.base_value() == Approx(1.0f));

        acceleration_f a2 = 1_km_s2;
        REQUIRE(a2.base_value() == Approx(1000.0f));
        REQUIRE(a2.m_s2() == Approx(1000.0f));

        acceleration_f a3 = 100_cm_s2;
        REQUIRE(a3.base_value() == Approx(1.0f)); // 100 cm/s² = 1 m/s²
        REQUIRE(a3.m_s2() == Approx(1.0f));

        acceleration_f a4 = 1_ft_s2;
        REQUIRE(a4.base_value() == Approx(0.3048f));
        REQUIRE(a4.m_s2() == Approx(0.3048f));
    }
}

TEST_CASE("Speed and acceleration combined") {

    SECTION("Velocity after constant acceleration") {
        acceleration_f a = 2_m_s2;
        time_f t = 5_s;
        speed_f v = a * t;
        REQUIRE(v.base_value() == Approx(10.0f)); // v = at
    }

    SECTION("Car acceleration example") {
        // Car accelerates from 0 to 100 km/h in 10 seconds
        speed_f v_final = 100_km_h;
        time_f t = 10_s;
        acceleration_f a = v_final / t;

        REQUIRE(a.base_value() == Approx(2.7778f).margin(0.001f)); // ~2.78 m/s²
        REQUIRE(a.m_s2() == Approx(2.7778f).margin(0.001f));
        REQUIRE(a.km_s2() == Approx(0.0027778f).margin(0.00001f));
    }
}

using namespace physi;
using namespace physi::literals;

TEST_CASE("Vector construction") {

    SECTION("Default constructor") {
        vec3<length_f> v;
        REQUIRE(v.x().base_value() == Approx(0.0f));
        REQUIRE(v.y().base_value() == Approx(0.0f));
        REQUIRE(v.z().base_value() == Approx(0.0f));
    }

    SECTION("Component constructor") {
        vec3<length_f> v(10_m, 20_m, 30_m);
        REQUIRE(v.x().base_value() == Approx(10.0f));
        REQUIRE(v.y().base_value() == Approx(20.0f));
        REQUIRE(v.z().base_value() == Approx(30.0f));
    }

    SECTION("Initializer list constructor") {
        vec3<length_f> v = {1_m, 2_m, 3_m};
        REQUIRE(v.x().base_value() == Approx(1.0f));
        REQUIRE(v.y().base_value() == Approx(2.0f));
        REQUIRE(v.z().base_value() == Approx(3.0f));
    }

    SECTION("Broadcast constructor") {
        vec3<length_f> v(5_m);
        REQUIRE(v.x().base_value() == Approx(5.0f));
        REQUIRE(v.y().base_value() == Approx(5.0f));
        REQUIRE(v.z().base_value() == Approx(5.0f));
    }

    SECTION("2D vector") {
        vec2<speed_f> v(10_m_s, 20_m_s);
        REQUIRE(v.x().base_value() == Approx(10.0f));
        REQUIRE(v.y().base_value() == Approx(20.0f));
    }
}

TEST_CASE("Vector addition and subtraction") {

    SECTION("Addition") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        vec3<length_f> sum = a + b;

        REQUIRE(sum.x().base_value() == Approx(5.0f));
        REQUIRE(sum.y().base_value() == Approx(7.0f));
        REQUIRE(sum.z().base_value() == Approx(9.0f));
    }

    SECTION("Subtraction") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        vec3<length_f> diff = a - b;

        REQUIRE(diff.x().base_value() == Approx(-3.0f));
        REQUIRE(diff.y().base_value() == Approx(-3.0f));
        REQUIRE(diff.z().base_value() == Approx(-3.0f));
    }

    SECTION("Compound addition") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        a += b;

        REQUIRE(a.x().base_value() == Approx(5.0f));
        REQUIRE(a.y().base_value() == Approx(7.0f));
        REQUIRE(a.z().base_value() == Approx(9.0f));
    }

    SECTION("Compound subtraction") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        a -= b;

        REQUIRE(a.x().base_value() == Approx(-3.0f));
        REQUIRE(a.y().base_value() == Approx(-3.0f));
        REQUIRE(a.z().base_value() == Approx(-3.0f));
    }
}

TEST_CASE("Vector unary operators") {

    SECTION("Unary plus") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> result = +a;

        REQUIRE(result.x().base_value() == Approx(1.0f));
        REQUIRE(result.y().base_value() == Approx(2.0f));
        REQUIRE(result.z().base_value() == Approx(3.0f));
    }

    SECTION("Unary minus") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> result = -a;

        REQUIRE(result.x().base_value() == Approx(-1.0f));
        REQUIRE(result.y().base_value() == Approx(-2.0f));
        REQUIRE(result.z().base_value() == Approx(-3.0f));
    }
}

TEST_CASE("Vector scalar multiplication and division") {

    SECTION("Multiply by scalar") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> scaled = a * 2.0f;

        REQUIRE(scaled.x().base_value() == Approx(2.0f));
        REQUIRE(scaled.y().base_value() == Approx(4.0f));
        REQUIRE(scaled.z().base_value() == Approx(6.0f));
    }

    SECTION("Scalar multiply (commutative)") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> scaled = 2.0f * a;

        REQUIRE(scaled.x().base_value() == Approx(2.0f));
        REQUIRE(scaled.y().base_value() == Approx(4.0f));
        REQUIRE(scaled.z().base_value() == Approx(6.0f));
    }

    SECTION("Divide by scalar") {
        vec3<length_f> a = {2_m, 4_m, 6_m};
        vec3<length_f> half = a / 2.0f;

        REQUIRE(half.x().base_value() == Approx(1.0f));
        REQUIRE(half.y().base_value() == Approx(2.0f));
        REQUIRE(half.z().base_value() == Approx(3.0f));
    }

    SECTION("Compound multiply") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        a *= 3.0f;

        REQUIRE(a.x().base_value() == Approx(3.0f));
        REQUIRE(a.y().base_value() == Approx(6.0f));
        REQUIRE(a.z().base_value() == Approx(9.0f));
    }

    SECTION("Compound divide") {
        vec3<length_f> a = {6_m, 9_m, 12_m};
        a /= 3.0f;

        REQUIRE(a.x().base_value() == Approx(2.0f));
        REQUIRE(a.y().base_value() == Approx(3.0f));
        REQUIRE(a.z().base_value() == Approx(4.0f));
    }
}

TEST_CASE("Vector dimensional operations") {

    SECTION("Divide by time to get velocity") {
        vec3<length_f> a = {10_m, 20_m, 30_m};
        time_f t = 2_s;
        vec3<speed_f> velocity = a / t;

        REQUIRE(velocity.x().base_value() == Approx(5.0f));
        REQUIRE(velocity.y().base_value() == Approx(10.0f));
        REQUIRE(velocity.z().base_value() == Approx(15.0f));
    }

    SECTION("Multiply velocity by time to get displacement") {
        vec3<speed_f> velocity = {5_m_s, 10_m_s, 15_m_s};
        time_f t = 2_s;
        vec3<length_f> displacement = velocity * t;

        REQUIRE(displacement.x().base_value() == Approx(10.0f));
        REQUIRE(displacement.y().base_value() == Approx(20.0f));
        REQUIRE(displacement.z().base_value() == Approx(30.0f));
    }

    SECTION("Time multiply velocity (commutative)") {
        vec3<speed_f> velocity = {5_m_s, 10_m_s, 15_m_s};
        time_f t = 2_s;
        vec3<length_f> displacement = velocity * t;

        REQUIRE(displacement.x().base_value() == Approx(10.0f));
        REQUIRE(displacement.y().base_value() == Approx(20.0f));
        REQUIRE(displacement.z().base_value() == Approx(30.0f));
    }

    SECTION("Force times distance equals work") {
        vec3<force_f> force = {10_N, 0_N, 0_N};
        length_f distance = 5_m;
        vec3<energy_f> work_vec = force * distance;

        REQUIRE(work_vec.x().base_value() == Approx(50.0f));
        REQUIRE(work_vec.y().base_value() == Approx(0.0f));
        REQUIRE(work_vec.z().base_value() == Approx(0.0f));
    }
}

TEST_CASE("Vector dot product") {

    SECTION("Work = Force · displacement") {
        vec3<force_f> F = {10_N, 0_N, 0_N};
        vec3<length_f> displacement = {5_m, 0_m, 0_m};
        energy_f work = F.dot(displacement);

        REQUIRE(work.base_value() == Approx(50.0f));
    }

    SECTION("Same direction vectors") {
        vec3<length_f> a = {3_m, 0_m, 0_m};
        vec3<length_f> b = {4_m, 0_m, 0_m};
        area_f result = a.dot(b);

        REQUIRE(result.base_value() == Approx(12.0f));
    }

    SECTION("Perpendicular vectors") {
        vec3<length_f> a = {1_m, 0_m, 0_m};
        vec3<length_f> b = {0_m, 1_m, 0_m};
        area_f result = a.dot(b);

        REQUIRE(result.base_value() == Approx(0.0f));
    }

    SECTION("General dot product") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        area_f result = a.dot(b);

        // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
        REQUIRE(result.base_value() == Approx(32.0f));
    }
}

TEST_CASE("Vector cross product") {

    SECTION("Area from perpendicular sides") {
        vec3<length_f> side_a = {3_m, 0_m, 0_m};
        vec3<length_f> side_b = {0_m, 4_m, 0_m};
        vec3<area_f> area_vec = side_a.cross(side_b);

        REQUIRE(area_vec.x().base_value() == Approx(0.0f));
        REQUIRE(area_vec.y().base_value() == Approx(0.0f));
        REQUIRE(area_vec.z().base_value() == Approx(12.0f));
    }

    SECTION("Torque = r × F") {
        vec3<length_f> side_a = {1_m, 0_m, 0_m};
        vec3<length_f> side_b = {0_m, 10_m, 0_m};
        vec3<area_f> area_vec = side_a.cross(side_b);

        REQUIRE(area_vec.x().base_value() == Approx(0.0f));
        REQUIRE(area_vec.y().base_value() == Approx(0.0f));
        REQUIRE(area_vec.z().base_value() == Approx(10.0f));
    }

    SECTION("Parallel vectors give zero") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {2_m, 4_m, 6_m};
        vec3<area_f> result = a.cross(b);

        REQUIRE(result.x().base_value() == Approx(0.0f));
        REQUIRE(result.y().base_value() == Approx(0.0f));
        REQUIRE(result.z().base_value() == Approx(0.0f));
    }

    SECTION("Standard basis cross products") {
        vec3<length_f> i = {1_m, 0_m, 0_m};
        vec3<length_f> j = {0_m, 1_m, 0_m};
        vec3<area_f> k = i.cross(j);

        REQUIRE(k.x().base_value() == Approx(0.0f));
        REQUIRE(k.y().base_value() == Approx(0.0f));
        REQUIRE(k.z().base_value() == Approx(1.0f));
    }
}

TEST_CASE("Vector component-wise multiplication (Hadamard)") {

    SECTION("Multiply two length vectors") {
        vec3<length_f> a = {2_m, 3_m, 4_m};
        vec3<length_f> b = {5_m, 6_m, 7_m};
        vec3<area_f> result = a * b;

        REQUIRE(result.x().base_value() == Approx(10.0f));
        REQUIRE(result.y().base_value() == Approx(18.0f));
        REQUIRE(result.z().base_value() == Approx(28.0f));
    }

    SECTION("Triple multiplication for volume") {
        vec3<length_f> dims = {2_m, 3_m, 4_m};
        vec3<volume_f> volume_vec = dims * dims * dims;

        REQUIRE(volume_vec.x().base_value() == Approx(8.0f));
        REQUIRE(volume_vec.y().base_value() == Approx(27.0f));
        REQUIRE(volume_vec.z().base_value() == Approx(64.0f));
    }

    SECTION("Component-wise division") {
        vec3<length_f> a = {10_m, 20_m, 30_m};
        vec3<length_f> b = {2_m, 4_m, 5_m};
        auto result = a / b;

        REQUIRE(result.x == Approx(5.0));
        REQUIRE(result.y == Approx(5.0));
        REQUIRE(result.z == Approx(6.0));
    }
}

TEST_CASE("Vector magnitude and normalization") {

    SECTION("Magnitude of length vector") {
        vec3<length_f> a = {3_m, 4_m, 0_m};
        length_f dist = a.length();

        REQUIRE(dist.base_value() == Approx(5.0f));
    }

    SECTION("Magnitude of velocity") {
        vec3<speed_f> velocity = {3_m_s, 4_m_s, 0_m_s};
        speed_f speed = velocity.length();

        REQUIRE(speed.base_value() == Approx(5.0f));
    }

    SECTION("Magnitude squared") {
        vec3<length_f> a = {3_m, 4_m, 0_m};
        area_f mag_sq = a.magnitude_squared();

        REQUIRE(mag_sq.base_value() == Approx(25.0f));
    }

    SECTION("Normalized vector (unitless direction)") {
        vec3<length_f> a = {3_m, 4_m, 0_m};
        auto dir = a.normalized();

        REQUIRE(dir.x == Approx(0.6));
        REQUIRE(dir.y == Approx(0.8));
        REQUIRE(dir.z == Approx(0.0));
    }

    SECTION("Normalized vector has magnitude 1") {
        vec3<length_f> a = {5_m, 12_m, 0_m};
        auto dir = a.normalized();

        double mag = std::sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        REQUIRE(mag == Approx(1.0));
    }
}

TEST_CASE("Vector distance") {

    SECTION("Distance between two points") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 6_m, 8_m};
        length_f separation = a.distance(b);

        // sqrt((4-1)^2 + (6-2)^2 + (8-3)^2) = sqrt(9 + 16 + 25) = sqrt(50)
        // ≈ 7.071
        REQUIRE(separation.base_value() == Approx(7.071f).margin(0.001f));
    }

    SECTION("Distance to same point is zero") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        length_f separation = a.distance(a);

        REQUIRE(separation.base_value() == Approx(0.0f));
    }
}

TEST_CASE("Vector comparison operators") {

    SECTION("Equality") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {1_m, 2_m, 3_m};

        REQUIRE(a == b);
    }

    SECTION("Inequality") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};

        REQUIRE(a != b);
    }
}

TEST_CASE("Vector component access") {

    SECTION("Read components") {
        vec3<length_f> v = {10_m, 20_m, 30_m};

        REQUIRE(v.x().base_value() == Approx(10.0f));
        REQUIRE(v.y().base_value() == Approx(20.0f));
        REQUIRE(v.z().base_value() == Approx(30.0f));
    }

    SECTION("Array-style access") {
        vec3<length_f> v = {1_m, 2_m, 3_m};

        REQUIRE(v[0].base_value() == Approx(1.0f));
        REQUIRE(v[1].base_value() == Approx(2.0f));
        REQUIRE(v[2].base_value() == Approx(3.0f));
    }
}

TEST_CASE("Vector raw data access") {

    SECTION("Base value returns glm::vec") {
        vec3<length_f> v = {10_m, 20_m, 30_m};
        glm::vec3 raw = v.base_value();

        REQUIRE(raw.x == Approx(10.0f));
        REQUIRE(raw.y == Approx(20.0f));
        REQUIRE(raw.z == Approx(30.0f));
    }

    SECTION("Data pointer access") {
        vec3<length_f> v = {10_m, 20_m, 30_m};
        const float *ptr = v.data_ptr();

        REQUIRE(ptr[0] == Approx(10.0f));
        REQUIRE(ptr[1] == Approx(20.0f));
        REQUIRE(ptr[2] == Approx(30.0f));
    }
}

TEST_CASE("2D vector specific operations") {

    SECTION("2D construction") {
        vec2<length_f> v(3_m, 4_m);

        REQUIRE(v.x().base_value() == Approx(3.0f));
        REQUIRE(v.y().base_value() == Approx(4.0f));
    }

    SECTION("2D magnitude") {
        vec2<length_f> v(3_m, 4_m);
        length_f mag = v.length();

        REQUIRE(mag.base_value() == Approx(5.0f));
    }

    SECTION("2D addition") {
        vec2<length_f> a(1_m, 2_m);
        vec2<length_f> b(3_m, 4_m);
        vec2<length_f> sum = a + b;

        REQUIRE(sum.x().base_value() == Approx(4.0f));
        REQUIRE(sum.y().base_value() == Approx(6.0f));
    }

    SECTION("2D dot product") {
        vec2<length_f> a(3_m, 4_m);
        vec2<length_f> b(5_m, 6_m);
        area_f result = a.dot(b);

        // 3*5 + 4*6 = 15 + 24 = 39
        REQUIRE(result.base_value() == Approx(39.0f));
    }
}

TEST_CASE("Physics simulation examples") {

    SECTION("Projectile motion") {
        vec3<length_f> initial_pos = {0_m, 10_m, 0_m};
        vec3<speed_f> initial_vel = {5_m_s, 10_m_s, 0_m_s};
        vec3<acceleration_f> gravity = {0_m_s2, -9.8_m_s2, 0_m_s2};
        time_f dt = 0.1_s;

        // Update velocity: v = v0 + at
        vec3<speed_f> new_vel = initial_vel + gravity * dt;

        REQUIRE(new_vel.x().base_value() == Approx(5.0f));
        REQUIRE(new_vel.y().base_value() == Approx(9.02f));
        REQUIRE(new_vel.z().base_value() == Approx(0.0f));

        // Update position: s = s0 + vt
        vec3<length_f> new_pos = initial_pos + initial_vel * dt;

        REQUIRE(new_pos.x().base_value() == Approx(0.5f));
        REQUIRE(new_pos.y().base_value() == Approx(11.0f));
        REQUIRE(new_pos.z().base_value() == Approx(0.0f));
    }

    SECTION("Force and acceleration") {
        mass_f m = 10_kg;
        vec3<force_f> net_force = {100_N, 0_N, 0_N};
        vec3<acceleration_f> accel = net_force / m;

        REQUIRE(accel.x().base_value() == Approx(10.0f));
        REQUIRE(accel.y().base_value() == Approx(0.0f));
        REQUIRE(accel.z().base_value() == Approx(0.0f));
    }

    SECTION("Kinetic energy (work-energy theorem)") {
        vec3<force_f> force = {50_N, 0_N, 0_N};
        vec3<length_f> displacement = {10_m, 0_m, 0_m};
        energy_f kinetic_energy = force.dot(displacement);

        REQUIRE(kinetic_energy.base_value() == Approx(500.0f));
    }
}

TEST_CASE("Vector edge cases") {

    SECTION("Magnitude with negative components") {
        vec3<length_f> v = {-3_m, -4_m, 0_m};
        length_f mag = v.length();

        REQUIRE(mag.base_value() == Approx(5.0f)); // Should be positive
    }

    SECTION("Magnitude with all negative components") {
        vec3<speed_f> v = {-5_m_s, -12_m_s, 0_m_s};
        speed_f mag = v.length();

        REQUIRE(mag.base_value() == Approx(13.0f)); // Should be positive
    }

    SECTION("Distance between identical points") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        length_f dist = a.distance(a);

        REQUIRE(dist.base_value() == Approx(0.0f));
    }

    SECTION("Zero magnitude squared") {
        vec3<length_f> zero = {0_m, 0_m, 0_m};
        area_f mag_sq = zero.magnitude_squared();

        REQUIRE(mag_sq.base_value() == Approx(0.0f));
    }
}

TEST_CASE("Vector mathematical properties") {

    SECTION("Cross product anti-commutativity: a × b = -(b × a)") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        vec3<area_f> cross1 = a.cross(b);
        vec3<area_f> cross2 = b.cross(a);

        REQUIRE(cross1.x().base_value() == Approx(-cross2.x().base_value()));
        REQUIRE(cross1.y().base_value() == Approx(-cross2.y().base_value()));
        REQUIRE(cross1.z().base_value() == Approx(-cross2.z().base_value()));
    }

    SECTION("Dot product commutativity: a · b = b · a") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        area_f dot1 = a.dot(b);
        area_f dot2 = b.dot(a);

        REQUIRE(dot1.base_value() == Approx(dot2.base_value()));
    }

    SECTION("Cross product with itself is zero") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<area_f> result = a.cross(a);

        REQUIRE(result.x().base_value() == Approx(0.0f));
        REQUIRE(result.y().base_value() == Approx(0.0f));
        REQUIRE(result.z().base_value() == Approx(0.0f));
    }

    SECTION("Distributive property: a · (b + c) = a · b + a · c") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        vec3<length_f> c = {7_m, 8_m, 9_m};

        area_f left = a.dot(b + c);
        area_f right = a.dot(b) + a.dot(c);

        REQUIRE(left.base_value() == Approx(right.base_value()));
    }

    SECTION("Scalar multiplication distributive: (ka) · b = k(a · b)") {
        vec3<length_f> a = {1_m, 2_m, 3_m};
        vec3<length_f> b = {4_m, 5_m, 6_m};
        float k = 2.0f;

        area_f left = (a * k).dot(b);
        area_f right = (a.dot(b)) * k;

        REQUIRE(left.base_value() == Approx(right.base_value()));
    }
}