#pragma once
#include <string>
#include "data.h"

class BasePricer {
public:
    virtual ~BasePricer() = default;
    virtual std::string getName() const = 0;
};

class BondPricerBase : public BasePricer {
public:
    virtual double calculateBaseBondValue(double bond_value) const;
};

class StockPricer : public BasePricer {
public:
    std::string getName() const override;
    double price(const StockData* stockData) const;
};

class BondPricer : public BondPricerBase {
public:
    std::string getName() const override;
    double price(const BondData* bondData) const;
};

class ConvertibleBondPricer : public BondPricerBase {
public:
    std::string getName() const override;
    double price(const ConvertibleBondData* cbData) const;
}; 