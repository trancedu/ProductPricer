#pragma once
#include "StockPricer.h"
#include "BondPricers.h"
#include "ProductVariant.h"
#include "Model.h"
class PricerVisitor {
public:
    StockPricer stockPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;
    JunkStockPricer junkStockPricer;

    double operator()(const StockData& data) { return stockPricer.calculatePrice(&data); }
    double operator()(const CallableBondData& data) { return callablePricer.calculatePrice(&data); }
    double operator()(const ConvertibleBondData& data) { return convertiblePricer.calculatePrice(&data); }
    
    double calculateJunkPrice(const StockData& data) { return junkStockPricer.calculatePrice(&data); }
};

class PricerModelVisitor {
public:
    StockPricer stockPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;

    StockModel stockModel;
    CallableBondModel callableBondModel;
    ConvertibleBondModel convertibleBondModel;

    double operator()(const StockData& data) { return stockModel.value(data, stockPricer); }
    double operator()(const CallableBondData& data) { return callableBondModel.value(data, callablePricer); }
    double operator()(const ConvertibleBondData& data) { return convertibleBondModel.value(data, convertiblePricer); }
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
    
    std::string operator()(const StockData& data) { return visitor.stockPricer.getName(); }
    std::string operator()(const CallableBondData& data) { return visitor.callablePricer.getName(); }
    std::string operator()(const ConvertibleBondData& data) { return visitor.convertiblePricer.getName(); }
};