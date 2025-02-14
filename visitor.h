#pragma once
#include <iostream>
#include "data.h"
#include "pricers.h"
#include "models.h"
#include "model_factory.h"

struct PricerVisitor {
    // Change to pointers for dynamic switching
    const StockPricer* stock_pricer;
    const BondPricer* bond_pricer;
    const ConvertibleBondPricer* cb_pricer;
    const ModelFactory* model_factory;

    // Setters for runtime changes
    void setStockPricer(const StockPricer* pricer) { stock_pricer = pricer; }
    void setBondPricer(const BondPricer* pricer) { bond_pricer = pricer; }
    void setConvertibleBondPricer(const ConvertibleBondPricer* pricer) { cb_pricer = pricer; }
    void setModelFactory(const ModelFactory* factory) { model_factory = factory; }

    void operator()(const StockData& data) const;
    void operator()(const BondData& data) const;
    void operator()(const ConvertibleBondData& data) const;
}; 