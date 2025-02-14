#pragma once
#include "Pricer.h"
#include "Data.h"

class StockPricer : public Pricer<StockPricer, StockData> {
public:
    double calculatePriceImpl(StockData* data) {
        return data->stock_specific_value * 1.1;
    }
    std::string getName() const {
        return "StockPricer";
    }
};

class JunkStockPricer : public Pricer<JunkStockPricer, StockData> {
public:
    double calculatePriceImpl(StockData* data) {
        return data->stock_specific_value * 0.5;
    }
    std::string getName() const {
        return "JunkStockPricer";
    }
}; 