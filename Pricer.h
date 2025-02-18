#pragma once
#include <string>
#include <concepts>

template <typename Derived, typename DataType>
class Pricer {
public:
    double calculatePrice(const DataType& data) {
        return static_cast<Derived*>(this)->calculatePriceImpl(data);
    }
    std::string getName() const {
        return static_cast<Derived*>(this)->getName();
    }
};

template<typename T, typename DataType>
concept PricerImpl = requires(T& t, const DataType& data) {
    { t.calculatePriceImpl(data) } -> std::convertible_to<double>;
    { t.getName() } -> std::convertible_to<std::string>;
};

template <typename Derived, typename DataType>
    requires PricerImpl<Derived, DataType>
class Pricer<Derived, DataType>;