#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#define PHYSI_QUANTITY_BEGIN(Name)                                             \
    template <typename T = double> struct Name : quantity<Name, T> {           \
        using quantity<Name, T>::quantity;                                     \
                                                                               \
      public:

// Close the struct and create the three precision aliases: _f, _d, _ld
#define PHYSI_QUANTITY_END(Name)                                               \
    }                                                                          \
    ;                                                                          \
    using Name##_f = Name<float>;                                              \
    using Name##_d = Name<double>;                                             \
    using Name##_ld = Name<long double>;

#define PHYSI_UNIT(QuantityType, unit_name, to_base_multiplier)                \
    constexpr double unit_name() const {                                       \
        return this->value_ / (to_base_multiplier);                            \
    }                                                                          \
    static constexpr QuantityType unit_name(double v) {                        \
        return QuantityType(v * (to_base_multiplier));                         \
    }

#define PHYSI_UNIT_INCREASE(QuantityType, unit_name, to_base_multiplier,       \
                            base_increase)                                     \
    constexpr double unit_name() const {                                       \
        return this->value_ / (to_base_multiplier) - base_increase;            \
    }                                                                          \
    static constexpr QuantityType unit_name(double v) {                        \
        return QuantityType((v + base_increase) * (to_base_multiplier));       \
    }

#define PHYSI_LITERAL(QuantityType, unit_name)                                 \
    constexpr QuantityType operator""_##unit_name(long double v) {             \
        return QuantityType::unit_name(v);                                     \
    }                                                                          \
    constexpr QuantityType operator""_##unit_name(unsigned long long v) {      \
        return QuantityType::unit_name(static_cast<long double>(v));           \
    }

namespace physi {

// CRTP base for a *dimension* quantity where the Derived is a template:
//   template<typename> struct Length;
//   using length_f = Length<float>;
//   using length_d = Length<double>;
// Works: length_f + length_d, length_d = length_f, etc.
//
// Derived must be a template taking one typename parameter.
// T is the underlying scalar type (default double).
template <template <typename> class Derived, typename T = double>
struct quantity {
    static_assert(std::is_arithmetic_v<T>,
                  "Underlying type T must be arithmetic");

  protected:
    T value_;

  public:
    using value_type = T;
    using derived_t = Derived<T>;

    // default / copy / move
    constexpr quantity() noexcept = default;
    constexpr quantity(const quantity &) noexcept = default;
    constexpr quantity(quantity &&) noexcept = default;
    ~quantity() noexcept = default;

    // explicit value constructor (keep it explicit to avoid accidental implicit
    // conversions from raw scalars)
    explicit constexpr quantity(T v) noexcept : value_(v) {}

    // implicit converting constructor between underlying scalar types for the
    // same Derived
    template <typename U>
        requires std::is_arithmetic_v<U>
    constexpr quantity(const quantity<Derived, U> &other) noexcept
        : value_(static_cast<T>(other.base_value())) {}

    // accessors
    [[nodiscard]] constexpr T base_value() const noexcept { return value_; }

    // unary
    [[nodiscard]] constexpr derived_t operator+() const noexcept {
        return derived_t(value_);
    }
    [[nodiscard]] constexpr derived_t operator-() const noexcept {
        return derived_t(-value_);
    }

    // arithmetic with same-dimension quantities (promotes to common_type)
    template <typename U>
        requires std::is_arithmetic_v<U>
    [[nodiscard]] constexpr Derived<std::common_type_t<T, U>>
    operator+(const Derived<U> &other) const noexcept {
        using R = std::common_type_t<T, U>;
        return Derived<R>(static_cast<R>(value_) +
                          static_cast<R>(other.base_value()));
    }

    template <typename U>
        requires std::is_arithmetic_v<U>
    [[nodiscard]] constexpr Derived<std::common_type_t<T, U>>
    operator-(const Derived<U> &other) const noexcept {
        using R = std::common_type_t<T, U>;
        return Derived<R>(static_cast<R>(value_) -
                          static_cast<R>(other.base_value()));
    }

    // scalar multiply/divide
    template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
    [[nodiscard]] constexpr Derived<std::common_type_t<T, Scalar>>
    operator*(Scalar s) const noexcept {
        using R = std::common_type_t<T, Scalar>;
        return Derived<R>(static_cast<R>(value_) * static_cast<R>(s));
    }

    template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
    [[nodiscard]] constexpr Derived<std::common_type_t<T, Scalar>>
    operator/(Scalar s) const noexcept {
        using R = std::common_type_t<T, Scalar>;
        return Derived<R>(static_cast<R>(value_) / static_cast<R>(s));
    }

    // scalar * quantity
    template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
    friend constexpr Derived<std::common_type_t<T, Scalar>>
    operator*(Scalar s, const Derived<T> &q) noexcept {
        using R = std::common_type_t<T, Scalar>;
        return Derived<R>(static_cast<R>(s) * static_cast<R>(q.base_value()));
    }

    // quantity / quantity -> scalar
    template <typename U>
    friend constexpr std::common_type_t<T, U>
    operator/(const Derived<T> &a, const Derived<U> &b) noexcept {
        using R = std::common_type_t<T, U>;
        return static_cast<R>(a.base_value()) / static_cast<R>(b.base_value());
    }

    // compound assignment (keeps underlying type T)
    template <typename U>
    constexpr Derived<T> &operator+=(const Derived<U> &other) noexcept {
        value_ += static_cast<T>(other.base_value());
        return static_cast<Derived<T> &>(*this);
    }

    template <typename U>
    constexpr Derived<T> &operator-=(const Derived<U> &other) noexcept {
        value_ -= static_cast<T>(other.base_value());
        return static_cast<Derived<T> &>(*this);
    }

    template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
    constexpr Derived<T> &operator*=(Scalar s) noexcept {
        value_ *= static_cast<T>(s);
        return static_cast<Derived<T> &>(*this);
    }

    template <typename Scalar>
        requires std::is_arithmetic_v<Scalar>
    constexpr Derived<T> &operator/=(Scalar s) noexcept {
        value_ /= static_cast<T>(s);
        return static_cast<Derived<T> &>(*this);
    }

    // comparisons
    template <typename U>
    [[nodiscard]] constexpr bool
    operator==(const Derived<U> &other) const noexcept {
        using R = std::common_type_t<T, U>;
        return static_cast<R>(value_) == static_cast<R>(other.base_value());
    }

    template <typename U>
    [[nodiscard]] constexpr bool
    operator!=(const Derived<U> &other) const noexcept {
        return !(*this == other);
    }

    template <typename U>
    [[nodiscard]] constexpr bool
    operator<(const Derived<U> &other) const noexcept {
        using R = std::common_type_t<T, U>;
        return static_cast<R>(value_) < static_cast<R>(other.base_value());
    }

    template <typename U>
    [[nodiscard]] constexpr bool
    operator<=(const Derived<U> &other) const noexcept {
        return !(other < *this);
    }

    template <typename U>
    [[nodiscard]] constexpr bool
    operator>(const Derived<U> &other) const noexcept {
        return other < *this;
    }

    template <typename U>
    [[nodiscard]] constexpr bool
    operator>=(const Derived<U> &other) const noexcept {
        return !(*this < other);
    }
};

} // namespace physi