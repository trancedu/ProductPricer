#pragma once

template <typename Derived, typename DataType>
class Pricer {
public:
    double calculatePrice(DataType* data) {
        return static_cast<Derived*>(this)->calculatePriceImpl(data);
    }
    std::string getName() const {
        return static_cast<Derived*>(this)->getName();
    }
};