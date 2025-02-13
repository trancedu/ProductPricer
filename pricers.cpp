#include "pricers.h"

double BondPricerBase::calculateBaseBondValue(double bond_value) const {
    return bond_value * 0.9;
}

std::string StockPricer::getName() const { return "Stock Pricer"; }
double StockPricer::price(const StockModel& model) const {
    return model.calculate() * 1.1;
}

std::string BondPricer::getName() const { return "Bond Pricer"; }
double BondPricer::price(const BondModel& model) const {
    return calculateBaseBondValue(model.calculate());
}

std::string ConvertibleBondPricer::getName() const { return "Convertible Bond Pricer"; }
double ConvertibleBondPricer::price(const ConvertibleBondModel& model) const {
    return calculateBaseBondValue(model.calculate()) * 0.95;
} 