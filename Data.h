#pragma once

class Data {
public:
    virtual ~Data() = default;
};

class StockData : public Data {
public:
    double stock_specific_value = 100.0;
};

class BondData : public Data {
public:
    double bond_specific_value = 200.0;
};

class CallableBondData : public BondData {
public:
    double callable_premium = 5.0;
};

class ConvertibleBondData : public BondData {
public:
    double conversion_ratio = 1.5;
}; 