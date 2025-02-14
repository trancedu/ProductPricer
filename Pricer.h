#pragma once

template <typename Derived, typename DataType>
class Pricer {
public:
    double calculatePrice(DataType* data) {
        return static_cast<Derived*>(this)->calculatePriceImpl(data);
    }
};

template <typename Derived, typename BondType>
class BondPricer : public Pricer<Derived, BondType> {
public:
    double commonBondFunction(BondType* bond) {
        return bond->bond_specific_value * 0.02;
    }
}; 