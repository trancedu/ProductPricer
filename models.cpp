#include "models.h"

// ======== Stock Model ======== //
StockModel::StockModel(const StockData& data) : stock_data(data) {}
double StockModel::calculate() const { return stock_data.stock_value; }
std::string StockModel::getTicker() const { return stock_data.ticker; }

// ======== Bond Model ======== //
BondModel::BondModel(const BondData& data) : bond_data(data) {}
double BondModel::calculate() const { return bond_data.bond_value; }
std::string BondModel::getTicker() const { return bond_data.ticker; }

// ======== Convertible Bond Model ======== //
ConvertibleBondModel::ConvertibleBondModel(const ConvertibleBondData& data) : cb_data(data) {}
double ConvertibleBondModel::calculate() const {
    return cb_data.bond_value * cb_data.conversion_ratio;
}
std::string ConvertibleBondModel::getTicker() const { return cb_data.ticker; } 