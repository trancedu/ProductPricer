#pragma once
#include "models.h"
#include "data.h"

// ======== Model Factory Interface ======== //
class ModelFactory {
public:
    virtual ~ModelFactory() = default;
    virtual StockModel createStockModel(const StockData& data) const = 0;
    virtual BondModel createBondModel(const BondData& data) const = 0;
    virtual ConvertibleBondModel createCBModel(const ConvertibleBondData& data) const = 0;
};

// ======== Default Model Factory ======== //
class DefaultModelFactory : public ModelFactory {
public:
    StockModel createStockModel(const StockData& data) const override;
    BondModel createBondModel(const BondData& data) const override;
    ConvertibleBondModel createCBModel(const ConvertibleBondData& data) const override;
};

// ======== Aggressive Model Factory ======== //
class AggressiveModelFactory : public ModelFactory {
public:
    StockModel createStockModel(const StockData& data) const override;
    BondModel createBondModel(const BondData& data) const override; 
    ConvertibleBondModel createCBModel(const ConvertibleBondData& data) const override;
}; 