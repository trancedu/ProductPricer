#include "models.h"

// ======== Stock Model ======== //
StockModel::StockModel(const StockData& data) : stock_data(data) {}
double StockModel::calculate() const { return stock_data.stock_value; }
std::string StockModel::getTicker() const { return stock_data.ticker; }

// ======== Bond Model ======== //
BondModel::BondModel(const BondData& data) : bond_data(data) {}
double BondModel::getBondValue() const {
    return bond_data.bond_value;
}
double BondModel::calculate() const {
    return getBondValue();
}
std::string BondModel::getTicker() const { return bond_data.ticker; }

// ======== Convertible Bond Model ======== //
ConvertibleBondModel::ConvertibleBondModel(const ConvertibleBondData& data) : cb_data(data) {}
double ConvertibleBondModel::getBondValue() const {
    return cb_data.bond_value;
}
double ConvertibleBondModel::getConversionRatio() const {
    return cb_data.conversion_ratio;
}
double ConvertibleBondModel::calculate() const {
    return getBondValue() * getConversionRatio();
}
std::string ConvertibleBondModel::getTicker() const { return cb_data.ticker; } 