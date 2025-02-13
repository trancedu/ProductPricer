#pragma once
#include <string>
#include "data.h"
#include "models.h"

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
    double price(const StockModel& model) const;
};

class BondPricer : public BondPricerBase {
public:
    std::string getName() const override;
    double price(const BondModel& model) const;
};

class ConvertibleBondPricer : public BondPricerBase {
public:
    std::string getName() const override;
    double price(const ConvertibleBondModel& model) const;
}; 