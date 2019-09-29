#pragma once
// type rich dimentions infrastructure


namespace trd {

template<int M, int K, int S>
struct Unit {
    static constexpr int m = M; // meter
    static constexpr int k = K; // kilogram
    static constexpr int s = S; // second
};


template<typename UnitType>
struct Value {
    using ValueType = Value<UnitType>;
    using value_type = UnitType;

    double value;


    explicit Value(double value):
        value(value) {}

    Value():
        Value(0) {}

    template<typename InType, typename OutType =
        Value<Unit<value_type::m - InType::value_type::m,
            value_type::k - InType::value_type::k,
            value_type::s - InType::value_type::s>>>
    OutType operator/(InType other) const {
	    return OutType(value / other.value);
    }

    template<typename InType, typename OutType =
        Value<Unit<value_type::m + InType::value_type::m,
            value_type::k + InType::value_type::k,
            value_type::s + InType::value_type::s>>>
    OutType operator*(InType other) const {
	    return OutType(value * other.value);
    }

    ValueType operator+(ValueType other) const {
	    return ValueType(value + other.value);
    }

    ValueType operator-(ValueType other) const {
	    return ValueType(value - other.value);
    }

    ValueType& operator+=(const ValueType& other) {
	    value += other.value;
        return *this;
    }

    ValueType& operator-=(const ValueType& other) {
	    value -= other.value;
        return *this;
    }

    ValueType& operator*=(const ValueType& other) {
	    value *= other.value;
        return *this;
    }

    ValueType& operator/=(const ValueType& other) {
	    value /= other.value;
        return *this;
    }

    ValueType operator-() const {
	    return ValueType(-value);
    }

    ValueType operator+() const {
	    return ValueType(value);
    }

    ValueType operator*(double k) const {
	    return ValueType(value * k);
    }

    ValueType operator/(double k) const {
	    return ValueType(value / k);
    }

    ValueType& operator*=(double k) {
	    value *= k;
        return *this;
    }

    ValueType& operator/=(double k) {
	    value /= k;
        return *this;
    }
};

using Second = Value<Unit<0, 0, 1>>;
using Meter = Value<Unit<1, 0, 0>>;
using Speed = Value<Unit<1, 0, -1>>;
using Acceleration = Value<Unit<1, 0, -2>>;

}