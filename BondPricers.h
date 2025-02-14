#pragma once
#include "Pricer.h"
#include "Data.h"

class CallableBondPricer : public BondPricer<CallableBondPricer, CallableBondData> {
public:
    double calculatePriceImpl(CallableBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->callable_premium + commonBondFunction(bond);
    }
};

class ConvertibleBondPricer : public BondPricer<ConvertibleBondPricer, ConvertibleBondData> {
public:
    double calculatePriceImpl(ConvertibleBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->conversion_ratio * 100 + commonBondFunction(bond);
    }
}; 