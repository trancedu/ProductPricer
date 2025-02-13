#pragma once
#include "data.h"

// ======== Base Model Interface ======== //
class BaseModel {
public:
    virtual ~BaseModel() = default;
    virtual double calculate() const = 0;
    virtual std::string getTicker() const = 0;
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
class BondModel : public BaseModel {
    const BondData& bond_data;
public:
    explicit BondModel(const BondData& data);
    double calculate() const override;
    std::string getTicker() const override;
};

// ======== Convertible Bond Model ======== //
class ConvertibleBondModel : public BaseModel {
    const ConvertibleBondData& cb_data;
public:
    explicit ConvertibleBondModel(const ConvertibleBondData& data);
    double calculate() const override;
    std::string getTicker() const override;
}; 