#pragma once
#include "data.h"

// ======== Base Model Interface ======== //
class BaseModel {
public:
    virtual ~BaseModel() = default;
    virtual double calculate() const = 0;
    virtual std::string getTicker() const = 0;
};

// ======== Bond Model Base ======== //
class BondModelBase : public BaseModel {
public:
    virtual double getBondValue() const = 0;
    virtual double getConversionRatio() const { return 1.0; } // Default for vanilla bonds
};

// ======== Stock Model ======== //
class StockModel : public BaseModel {
    const StockData& stock_data;
public:
    explicit StockModel(const StockData& data);
    double calculate() const override;
    std::string getTicker() const override;
};

// ======== Bond Model ======== //
class BondModel : public BondModelBase {
    const BondData& bond_data;
public:
    explicit BondModel(const BondData& data);
    double calculate() const override;
    std::string getTicker() const override;
    double getBondValue() const override;
};

// ======== Convertible Bond Model ======== //
class ConvertibleBondModel : public BondModelBase {
    const ConvertibleBondData& cb_data;
public:
    explicit ConvertibleBondModel(const ConvertibleBondData& data);
    double calculate() const override;
    std::string getTicker() const override;
    double getBondValue() const override;
    double getConversionRatio() const override;
}; 