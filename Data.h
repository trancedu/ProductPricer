#pragma once

class Data {
public:
    std::string typeName;
};

class StockData : public Data {
public:
    double stock_specific_value = 100.0;
    StockData() { typeName = "StockData"; }
};

class BondData : public Data {
public:
    double bond_specific_value = 200.0;
    BondData() { typeName = "BondData"; }
};

class CallableBondData : public BondData {
public:
    double callable_premium = 5.0;
    CallableBondData() { typeName = "CallableBondData"; }
};

class ConvertibleBondData : public BondData {
public:
    double conversion_ratio = 1.5;
    ConvertibleBondData() { typeName = "ConvertibleBondData"; }
}; 