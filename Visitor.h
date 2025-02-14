#pragma once
#include "StockPricer.h"
#include "BondPricers.h"
#include "ProductVariant.h"

class PricerVisitor {
public:
    StockPricer stockPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;
    JunkStockPricer junkStockPricer;

    double operator()(StockData* data) { return stockPricer.calculatePrice(data); }
    double operator()(CallableBondData* data) { return callablePricer.calculatePrice(data); }
    double operator()(ConvertibleBondData* data) { return convertiblePricer.calculatePrice(data); }
    
    double calculateJunkPrice(StockData* data) { return junkStockPricer.calculatePrice(data); }
}; 