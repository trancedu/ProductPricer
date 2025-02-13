#pragma once
#include <iostream>
#include "data.h"
#include "pricers.h"
#include "models.h"

struct PricerVisitor {
    const StockPricer& stock_pricer;
    const BondPricer& bond_pricer;
    const ConvertibleBondPricer& cb_pricer;

    void operator()(const StockData& data) const;
    void operator()(const BondData& data) const;
    void operator()(const ConvertibleBondData& data) const;
}; 