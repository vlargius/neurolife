#pragma once
/*
    type rich dimentions infrastructure
*/
#include <math.h>

namespace trd {

template <int M, int K, int S>
struct Unit {
    static constexpr int m = M;  // meter
    static constexpr int k = K;  // kilogram
    static constexpr int s = S;  // second
};

template <typename UnitType>
struct Value {
    using value_type = Value<UnitType>;
    using unit_type = UnitType;

    double value;

    explicit Value(double value) : value(value) {}

    Value() : Value(0) {}

    bool operator==(value_type other) const { return value == other.value; }

    bool operator!=(value_type other) const { return !(*this == other); }

    bool operator>(value_type other) const { return value > other.value; }

    bool operator<(value_type other) const { return value < other.value; }

    bool operator>=(value_type other) const { return value >= other.value; }

    bool operator<=(value_type other) const { return value <= other.value; }

    template <typename InType,
              typename OutType = Value<Unit<unit_type::m - InType::unit_type::m,
                                            unit_type::k - InType::unit_type::k,
                                            unit_type::s - InType::unit_type::s>>>
    OutType operator/(InType other) const {
        return OutType(value / other.value);
    }

    value_type operator+(value_type other) const {
        return value_type(value + other.value);
    }

    value_type operator-(value_type other) const {
        return value_type(value - other.value);
    }

    value_type& operator+=(const value_type& other) {
        value += other.value;
        return *this;
    }

    value_type& operator-=(const value_type& other) {
        value -= other.value;
        return *this;
    }

    value_type& operator*=(const value_type& other) {
        value *= other.value;
        return *this;
    }

    value_type& operator/=(const value_type& other) {
        value /= other.value;
        return *this;
    }

    value_type operator-() const { return value_type(-value); }

    value_type operator+() const { return value_type(value); }

    value_type operator*(double k) const { return value_type(value * k); }

    value_type operator/(double k) const { return value_type(value / k); }

    value_type& operator*=(double k) {
        value *= k;
        return *this;
    }

    value_type& operator/=(double k) {
        value /= k;
        return *this;
    }
};

constexpr int minus_if_not_zero(int a, int b)
{
    return a != 0 ? a - 2: a;
}

template<class UnitType,
         typename OutType = Value<Unit<minus_if_not_zero(UnitType::m, 2),
                                        minus_if_not_zero(UnitType::k, 2),
                                        minus_if_not_zero(UnitType::s, 2)>>>
OutType sqrt(const Value<UnitType>& value) {
    return value;
}


template <class UnitType>
struct Vec2 {
    using value_type = Value<UnitType>;
    using unit_type = UnitType;
    using vec2_type = Vec2<UnitType>;

    value_type x;
    value_type y;

    Vec2(const value_type& x, const value_type& y) : x(x), y(y) {}

    Vec2() : x(value_type{0}), y(value_type{0}) {}

    bool operator==(Vec2<value_type> other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(Vec2<value_type> other) const { return !(*this == other); }

    template <typename InType,
              typename OutType = Vec2<Unit<unit_type::m + InType::unit_type::m,
                                           unit_type::k + InType::unit_type::k,
                                           unit_type::s + InType::unit_type::s>>>
    OutType operator*(const InType& other) const {
        return OutType{x * other, y * other};
    }

    template <typename InType,
              typename OutType = Vec2<Unit<unit_type::m + InType::m,
                                           unit_type::k + InType::k,
                                           unit_type::s + InType::s>>>
    OutType operator*(const Value<InType>& other) const {
        return OutType{x * other, y * other};
    }

    template <typename InType,
              typename OutType = Vec2<Unit<unit_type::m - InType::m,
                                           unit_type::k - InType::k,
                                           unit_type::s - InType::s>>>
    OutType operator/(const Value<InType>& other) const {
        return OutType{x / other, y / other};
    }

    vec2_type operator+(vec2_type other) const {
        return vec2_type{x + other.x, y + other.y};
    }

    vec2_type operator-(vec2_type other) const {
        return vec2_type{x - other.x, y - other.y};
    }

    vec2_type& operator+=(const vec2_type& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2_type& operator-=(const vec2_type& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // vec2_type& operator*=(const vec2_type& other) {
    //     x *= other.x;
    //     y *= other.y;
    //     return *this;
    // }

    // vec2_type& operator/=(const vec2_type& other) {
    //     x /= other.x;
    //     y /= other.y;
    //     return *this;
    // }

    vec2_type operator-() const { return value_type{-x, -y}; }

    vec2_type operator+() const { return value_type{x, y}; }

    vec2_type operator*(double k) const { return value_type{k * x, k * y}; }

    vec2_type operator/(double k) const { return value_type{k / x, k / y}; }

    vec2_type& operator*=(double k) {
        x *= k;
        y *= k;
        return *this;
    }

    vec2_type& operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }

    // value_type norm() const {
    //     return sqrt(x * x + y * y);
    // }
};

template <typename Vec2Type>
Vec2<Vec2Type> operator*(double value, const Vec2<Vec2Type>& vec) {
    return {vec.x * value, vec.y * value};
}

template <typename UnitType, typename Vec2Type,
          typename OutType =
              Vec2<Unit<UnitType::m + Vec2Type::m,
                        UnitType::k + Vec2Type::k,
                        UnitType::s + Vec2Type::s>>>
OutType operator*(const Value<UnitType>& value, const Vec2<Vec2Type>& vec) {
    return OutType{vec.x * value, vec.y * value};
}

// template <typename LeftType, typename RightType,
//           typename OutType = Value<Unit<LeftType::m - RightType::m,
//                                         LeftType::k - RightType::k,
//                                         LeftType::s - RightType::s>>>
// OutType operator/(const Vec2<LeftType>& left, const Vec2<RightType>& right) {
//     return OutType(
//         {
//             left.x / right.x,
//             left.y / right.y
//         }
//     );
// }


template <typename LeftType, typename RightType,
          typename OutType = Value<Unit<LeftType::m + RightType::m,
                                        LeftType::k + RightType::k,
                                        LeftType::s + RightType::s>>>
OutType operator*(Value<LeftType> left, Value<RightType> right) {
    return OutType(left.value * right.value);
}

template <typename InType,
          typename OutType = Value<Unit<-InType::m,
                                        -InType::k,
                                        -InType::s>>>
OutType operator/(double k, const Value<InType>& right) {
    return OutType(k / right.value);
}

}  // namespace trd

using Second = trd::Value<trd::Unit<0, 0, 1>>;
using Hertz = trd::Value<trd::Unit<0, 0, -1>>;
using Meter = trd::Value<trd::Unit<1, 0, 0>>;
using MeterPerSec = trd::Value<trd::Unit<1, 0, -1>>;
using MeterPerSec2 = trd::Value<trd::Unit<1, 0, -2>>;
using Kilogram = trd::Value<trd::Unit<0, 1, 0>>;
using Newton = trd::Value<trd::Unit<1, 1, -2>>;

template <class ValueType>
double to_double(const trd::Value<ValueType>& value) {
    return value.value;
}

template <class UnitType>
double dot(const trd::Vec2<UnitType>& left, const trd::Vec2<UnitType>& right) {
    return to_double(left.x * right.x + left.y * right.y);
}

template <typename InType>
trd::Value<InType> norm(const trd::Vec2<InType>& vec2) {
    // return trd::sqrt(vec2.x * vec2.x + vec2.y * vec2.y);
    return trd::Value<InType>{sqrt(vec2.x.value * vec2.x.value + vec2.y.value * vec2.y.value)};
}

template<class InType>
trd::Value<InType> operator*(double k, const trd::Value<InType>& right) { return right * k; }

using Position = trd::Vec2<Meter::unit_type>;
using Velocity = trd::Vec2<MeterPerSec::unit_type>;
using Acceleration = trd::Vec2<MeterPerSec2::unit_type>;
using Force = trd::Vec2<Newton::unit_type>;

const trd::Value<trd::Unit<3, -1, -2>> G = trd::Value<trd::Unit<3, -1, -2>>(0.01);