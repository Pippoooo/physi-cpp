#pragma once

#include <glm/glm.hpp>

namespace physi {

template <typename T> struct is_vec : std::false_type {};

template <typename Quantity, glm::length_t N> struct vec {
    glm::vec<N, typename Quantity::value_type> data;

    using value_type = typename Quantity::value_type;

    template <typename Q, glm::length_t M> friend struct vec;

    // ---------------------------------------------------------------------------------------------

  private:
    explicit constexpr vec(const glm::vec<N, value_type> &v) noexcept
        : data(v) {}

  public:
    // Default constructor (zero-initialized)
    constexpr vec() noexcept : data(0) {}

    // Construct from individual Quantity components
    constexpr vec(Quantity x, Quantity y) noexcept
        requires(N == 2)
        : data(x.base_value(), y.base_value()) {}

    constexpr vec(Quantity x, Quantity y, Quantity z) noexcept
        requires(N == 3)
        : data(x.base_value(), y.base_value(), z.base_value()) {}

    constexpr vec(Quantity x, Quantity y, Quantity z, Quantity w) noexcept
        requires(N == 4)
        : data(x.base_value(), y.base_value(), z.base_value(), w.base_value()) {
    }

    // Construct from initializer list
    constexpr vec(std::initializer_list<Quantity> list) noexcept {
        auto it = list.begin();
        for (glm::length_t i = 0; i < N && it != list.end(); ++i, ++it) {
            data[i] = it->base_value();
        }
    }

    explicit constexpr vec(Quantity scalar) noexcept
        : data(scalar.base_value()) {}

    constexpr vec(const vec &) noexcept = default;
    constexpr vec &operator=(const vec &) noexcept = default;

    // ========== Vector + Vector (same quantity) ==========
    [[nodiscard]] constexpr vec operator+(const vec &other) const noexcept {
        return vec{data + other.data};
    }

    [[nodiscard]] constexpr vec operator-(const vec &other) const noexcept {
        return vec{data - other.data};
    }

    constexpr vec &operator+=(const vec &other) noexcept {
        data += other.data;
        return *this;
    }

    constexpr vec &operator-=(const vec &other) noexcept {
        data -= other.data;
        return *this;
    }

    // ========== Unary operators ==========
    [[nodiscard]] constexpr vec operator+() const noexcept { return *this; }

    [[nodiscard]] constexpr vec operator-() const noexcept {
        return vec{-data};
    }

    // ========== Vector * Scalar (dimensionless) ==========
    [[nodiscard]] constexpr vec operator*(value_type scalar) const noexcept {
        return vec{data * scalar};
    }

    [[nodiscard]] constexpr vec operator/(value_type scalar) const noexcept {
        return vec{data / scalar};
    }

    constexpr vec &operator*=(value_type scalar) noexcept {
        data *= scalar;
        return *this;
    }

    constexpr vec &operator/=(value_type scalar) noexcept {
        data /= scalar;
        return *this;
    }

    // Friend for scalar * vector (commutative)
    [[nodiscard]] friend constexpr vec operator*(value_type scalar,
                                                 const vec &v) noexcept {
        return vec{scalar * v.data};
    }

    // ========== Vector * Quantity (dimensional) ==========
    template <typename Q2>
        requires(!is_vec<Q2>::value) // Exclude other vec types
    [[nodiscard]] constexpr auto operator*(Q2 scalar) const noexcept {
        using Result = decltype(Quantity() * Q2());
        return vec<Result, N>{data * scalar.base_value()};
    }

    template <typename Q2>
        requires(!is_vec<Q2>::value) // Exclude other vec types
    [[nodiscard]] constexpr auto operator/(Q2 scalar) const noexcept {
        using Result = decltype(Quantity() / Q2());
        return vec<Result, N>{data / scalar.base_value()};
    }

    // Friend for quantity * vector (commutative)
    template <typename Q2>
        requires(!is_vec<Q2>::value) // Exclude other vec types
    [[nodiscard]] friend constexpr auto operator*(Q2 scalar,
                                                  const vec &v) noexcept {
        using Result = decltype(Q2() * Quantity());
        return vec<Result, N>{scalar.base_value() * v.data};
    }
    // ========== Component-wise Vector * Vector (Hadamard product) ==========
    template <typename Q2>
    [[nodiscard]] constexpr auto
    operator*(const vec<Q2, N> &other) const noexcept {
        using Result = decltype(Quantity() * Q2());
        return vec<Result, N>{data * other.data};
    }

    template <typename Q2>
    [[nodiscard]] constexpr auto
    operator/(const vec<Q2, N> &other) const noexcept {
        using Result = decltype(Quantity() / Q2());
        if constexpr (std::is_arithmetic_v<Result>) {
            return data / other.data;
        } else {
            return vec<Result, N>{data / other.data};
        }
    }

    // ========== Dot Product ==========
    template <typename Q2>
    [[nodiscard]] constexpr auto dot(const vec<Q2, N> &other) const noexcept {
        using Result = decltype(Quantity() * Q2());
        return Result(glm::dot(data, other.data));
    }

    // ========== Cross Product (3D only) ==========
    template <typename Q2>
    [[nodiscard]] constexpr auto cross(const vec<Q2, 3> &other) const noexcept
        requires(N == 3)
    {
        using Result = decltype(Quantity() * Q2());
        return vec<Result, 3>{glm::cross(data, other.data)};
    }

    // ========== Magnitude (Pythagorean length) ==========
    [[nodiscard]] constexpr Quantity length() const noexcept {
        return Quantity(glm::length(data));
    }

    // Squared magnitude (avoids sqrt, useful for comparisons)
    [[nodiscard]] constexpr auto magnitude_squared() const noexcept {
        using Result = decltype(Quantity() * Quantity());
        return Result(glm::dot(data, data));
    }

    // ========== Normalization (returns unitless direction) ==========
    [[nodiscard]] constexpr auto normalized() const noexcept {
        return glm::normalize(data);
    }

    // ========== Distance between two position vectors ==========
    [[nodiscard]] constexpr Quantity distance(const vec &other) const noexcept {
        return (*this - other).length();
    }

    // ========== Comparison operators ==========
    [[nodiscard]] constexpr bool operator==(const vec &other) const noexcept {
        return data == other.data;
    }

    [[nodiscard]] constexpr bool operator!=(const vec &other) const noexcept {
        return data != other.data;
    }

    // ========== Component access ==========
    [[nodiscard]] constexpr Quantity x() const noexcept {
        return Quantity(data.x);
    }
    [[nodiscard]] constexpr Quantity y() const noexcept {
        return Quantity(data.y);
    }
    [[nodiscard]] constexpr Quantity z() const noexcept
        requires(N >= 3)
    {
        return Quantity(data.z);
    }
    [[nodiscard]] constexpr Quantity w() const noexcept
        requires(N >= 4)
    {
        return Quantity(data.w);
    }

    // ========== Array-style access ==========
    [[nodiscard]] constexpr Quantity
    operator[](glm::length_t i) const noexcept {
        return Quantity(data[i]);
    }

    // ========== Raw data access ==========
    [[nodiscard]] constexpr auto base_value() const noexcept { return data; }
    [[nodiscard]] constexpr value_type *data_ptr() noexcept { return &data[0]; }
    [[nodiscard]] constexpr const value_type *data_ptr() const noexcept {
        return &data[0];
    }
};

template <typename Q, glm::length_t N>
struct is_vec<vec<Q, N>> : std::true_type {};

template <typename Quantity, glm::length_t N>
inline constexpr bool vec_layout_check =
    sizeof(vec<Quantity, N>) ==
    sizeof(glm::vec<N, typename Quantity::value_type>);

static_assert(vec_layout_check<length_f, 3>,
              "vec must have identical memory layout to glm::vec");
static_assert(vec_layout_check<length_d, 3>,
              "vec must have identical memory layout to glm::vec");
static_assert(vec_layout_check<length_ld, 3>,
              "vec must have identical memory layout to glm::vec");

template <typename Quantity> using vec2 = vec<Quantity, 2>;
template <typename Quantity> using vec3 = vec<Quantity, 3>;
template <typename Quantity> using vec4 = vec<Quantity, 4>;

} // namespace physi