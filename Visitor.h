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

class TypeNameVisitor {
public:
    std::string operator()(StockData* data) { return data->typeName; }
    std::string operator()(CallableBondData* data) { return data->typeName; }
    std::string operator()(ConvertibleBondData* data) { return data->typeName; }
}; 

class PricerNameVisitor {
private:
    PricerVisitor& visitor;
public:
    PricerNameVisitor(PricerVisitor& v) : visitor(v) {}
    
    std::string operator()(StockData* data) { return visitor.stockPricer.getName(); }
    std::string operator()(CallableBondData* data) { return visitor.callablePricer.getName(); }
    std::string operator()(ConvertibleBondData* data) { return visitor.convertiblePricer.getName(); }
};