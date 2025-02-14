#include <iostream>

// Base Data class
class Data {
public:
    virtual ~Data() = default;
};

// Stock Data
class StockData : public Data {
public:
    double stock_specific_value = 100.0;
};

// Bond Data Hierarchy
class BondData : public Data {
public:
    double bond_specific_value = 200.0;
};

// Derived Bond Types
class CallableBond : public BondData {
public:
    double callable_premium = 5.0;
};

class ConvertibleBond : public BondData {
public:
    double conversion_ratio = 1.5;
};

// ---------------------- BASE PRICER CLASS ----------------------
// General template for all pricers
template <typename Derived, typename DataType>
class Pricer {
public:
    double calculatePrice(DataType* data) {
        return static_cast<Derived*>(this)->calculatePriceImpl(data);
    }
};

// ---------------------- STOCK PRICER ----------------------
// Specialization for stock pricing
class StockPricer : public Pricer<StockPricer, StockData> {
public:
    double calculatePriceImpl(StockData* data) {
        return data->stock_specific_value * 1.1;  // Example stock pricing logic
    }
};

// ---------------------- BOND PRICER (INTERMEDIATE CLASS) ----------------------
// Provides shared bond pricing logic
template <typename Derived, typename BondType>
class BondPricer : public Pricer<Derived, BondType> {
public:
    double commonBondFunction(BondType* bond) {
        return bond->bond_specific_value * 0.02; // Common bond adjustment logic
    }
};

// ---------------------- CALLABLE BOND PRICER ----------------------
class CallableBondPricer : public BondPricer<CallableBondPricer, CallableBond> {
public:
    double calculatePriceImpl(CallableBond* bond) {
        double base_price = bond->bond_specific_value * 1.05;  // Common bond pricing logic
        return base_price + bond->callable_premium + commonBondFunction(bond);
    }
};

// ---------------------- CONVERTIBLE BOND PRICER ----------------------
class ConvertibleBondPricer : public BondPricer<ConvertibleBondPricer, ConvertibleBond> {
public:
    double calculatePriceImpl(ConvertibleBond* bond) {
        double base_price = bond->bond_specific_value * 1.05;  // Common bond pricing logic
        return base_price + bond->conversion_ratio * 100 + commonBondFunction(bond);
    }
};

// ---------------------- USAGE ----------------------
int main() {
    StockData stock;
    CallableBond callableBond;
    ConvertibleBond convertibleBond;

    StockPricer stockPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;

    std::cout << "Stock Price: " << stockPricer.calculatePrice(&stock) << std::endl;
    std::cout << "Callable Bond Price: " << callablePricer.calculatePrice(&callableBond) << std::endl;
    std::cout << "Convertible Bond Price: " << convertiblePricer.calculatePrice(&convertibleBond) << std::endl;

    return 0;
}