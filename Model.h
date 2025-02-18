#pragma once
#include <string>
#include <concepts>
#include "Data.h"
#include "Pricer.h"
#include "BondPricers.h"
#include "StockPricer.h"

class Model {
public:
    std::string getName() const {
        return name;
    }
    explicit Model(std::string name) : name(std::move(name)) {}
private:
    std::string name;
};

class StockModel : public Model {
public:
    StockModel() : Model("StockModel") {}
    double value(const StockData& data, const StockPricer& pricer) const {
        return pricer.calculatePrice(&data);
    }
};

class BondModel : public Model {
public:
    using Model::Model;
};

class CallableBondModel : public BondModel {
public:
    CallableBondModel() : BondModel("CallableBondModel") {}
    double value(const CallableBondData& data, const CallableBondPricer& pricer) const {
        return pricer.calculatePrice(&data);
    }
};

class ConvertibleBondModel : public BondModel {
public:
    ConvertibleBondModel() : BondModel("ConvertibleBondModel") {}
    double value(const ConvertibleBondData& data, const ConvertibleBondPricer& pricer) const {
        return pricer.calculatePrice(&data);
    }
};

