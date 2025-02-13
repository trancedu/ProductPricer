#pragma once
#include <string>
#include <variant>

class BaseData {
public:
    std::string ticker;
    double market_cap;

    explicit BaseData(std::string ticker, double market_cap);
    virtual ~BaseData() = default;
};

class StockData : public BaseData {
public:
    double stock_value;
    StockData(std::string ticker, double market_cap, double value);
};

class BondData : public BaseData {
public:
    double bond_value;
    BondData(std::string ticker, double market_cap, double value);
};

class ConvertibleBondData : public BondData {
public:
    double conversion_ratio;
    ConvertibleBondData(std::string ticker, double market_cap, 
                      double value, double ratio);
};

using InstrumentVariant = std::variant<StockData, BondData, ConvertibleBondData>; 