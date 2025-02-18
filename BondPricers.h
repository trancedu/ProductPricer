#pragma once
#include "Pricer.h"
#include "Data.h"

class BondPricer : public Pricer {
public:
    BondPricer(std::string name) : Pricer(std::move(name)) {}
    double commonBondFunction(BondData* bond) {
        return bond->bond_specific_value * 0.02;
    }
}; 

class CallableBondPricer : public BondPricer {
public:
    CallableBondPricer() : BondPricer("CallableBondPricer") {}
    double calculatePrice(CallableBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->callable_premium + commonBondFunction(bond);
    }
};

class ConvertibleBondPricer : public BondPricer {
public:
    ConvertibleBondPricer() : BondPricer("ConvertibleBondPricer") {}
    double calculatePrice(ConvertibleBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->conversion_ratio * 100 + commonBondFunction(bond);
    }
}; 