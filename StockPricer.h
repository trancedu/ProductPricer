#pragma once
#include "Pricer.h"
#include "Data.h"

class StockPricer : public Pricer {
public:
    StockPricer() : Pricer("StockPricer") {}
    double calculatePrice(const StockData* data) {
        return data->stock_specific_value * 1.1;
    }
};

class JunkStockPricer : public Pricer {
public:
    JunkStockPricer() : Pricer("JunkStockPricer") {}
    double calculatePrice(const StockData* data) {
        return data->stock_specific_value * 0.5;
    }
}; 