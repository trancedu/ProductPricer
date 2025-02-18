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

    double operator()(const StockData& data) { return stockPricer.calculatePrice(data); }
    double operator()(const CallableBondData& data) { return callablePricer.calculatePrice(data); }
    double operator()(const ConvertibleBondData& data) { return convertiblePricer.calculatePrice(data); }
    
    double calculateJunkPrice(const StockData& data) { return junkStockPricer.calculatePrice(data); }
};

class TypeNameVisitor {
public:
    std::string operator()(const StockData& data) { return data.typeName; }
    std::string operator()(const CallableBondData& data) { return data.typeName; }
    std::string operator()(const ConvertibleBondData& data) { return data.typeName; }
}; 

class PricerNameVisitor {
private:
    PricerVisitor& visitor;
public:
    PricerNameVisitor(PricerVisitor& v) : visitor(v) {}
    
    std::string operator()(const StockData&) { return visitor.stockPricer.getName(); }
    std::string operator()(const CallableBondData&) { return visitor.callablePricer.getName(); }
    std::string operator()(const ConvertibleBondData&) { return visitor.convertiblePricer.getName(); }
};