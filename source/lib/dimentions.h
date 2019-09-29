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
    double value;
    using value_type = UnitType;

    explicit Value(double value):
        value(value) {}
    Value():
        Value(0) {}

    template<typename InType, typename OutType =
        Value<Unit<value_type::m - InType::value_type::m,
            value_type::k - InType::value_type::k,
            value_type::s - InType::value_type::s>>>
    OutType operator / (InType other){
	    OutType result(value/other.value);
	    return result;
    }

};

using Second = Value<Unit<0, 0, 1>>;
using Meter = Value<Unit<1, 0, 0>>;
using Speed = Value<Unit<1, 0, -1>>;
using Acceleration = Value<Unit<1, 0, -2>>;

}