#include "pricers.h"

double BondPricerBase::calculateBaseBondValue(double bond_value) const {
    return bond_value * 0.9;
}

std::string StockPricer::getName() const { return "Stock Pricer"; }
double StockPricer::price(const StockData* stockData) const {
    return stockData->stock_value * 1.1;
}

std::string BondPricer::getName() const { return "Bond Pricer"; }
double BondPricer::price(const BondData* bondData) const {
    return calculateBaseBondValue(bondData->bond_value);
}

std::string ConvertibleBondPricer::getName() const { return "Convertible Bond Pricer"; }
double ConvertibleBondPricer::price(const ConvertibleBondData* cbData) const {
    return calculateBaseBondValue(cbData->bond_value) * 0.95 * cbData->conversion_ratio;
} 