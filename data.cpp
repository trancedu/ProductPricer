#include "data.h"

BaseData::BaseData(std::string ticker, double market_cap)
    : ticker(std::move(ticker)), market_cap(market_cap) {}

StockData::StockData(std::string ticker, double market_cap, double value)
    : BaseData(std::move(ticker), market_cap), stock_value(value) {}

BondData::BondData(std::string ticker, double market_cap, double value)
    : BaseData(std::move(ticker), market_cap), bond_value(value) {}

ConvertibleBondData::ConvertibleBondData(std::string ticker, double market_cap,
                                       double value, double ratio)
    : BondData(std::move(ticker), market_cap, value), conversion_ratio(ratio) {} 