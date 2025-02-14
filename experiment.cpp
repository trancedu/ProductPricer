#include <iostream>
#include <variant>
#include <vector>

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
class CallableBondData : public BondData {
public:
    double callable_premium = 5.0;
};

class ConvertibleBondData : public BondData {
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

class JunkStockPricer : public Pricer<JunkStockPricer, StockData> {
public:
    double calculatePriceImpl(StockData* data) {
        return data->stock_specific_value * 0.5;  // Junk stock pricing logic
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
class CallableBondPricer : public BondPricer<CallableBondPricer, CallableBondData> {
public:
    double calculatePriceImpl(CallableBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;  // Common bond pricing logic
        return base_price + bond->callable_premium + commonBondFunction(bond);
    }
};

// ---------------------- CONVERTIBLE BOND PRICER ----------------------
class ConvertibleBondPricer : public BondPricer<ConvertibleBondPricer, ConvertibleBondData> {
public:
    double calculatePriceImpl(ConvertibleBondData* bond) {
        double base_price = bond->bond_specific_value * 1.05;  // Common bond pricing logic
        return base_price + bond->conversion_ratio * 100 + commonBondFunction(bond);
    }
};

// ---------------------- VARIANT TYPE DEFINITION ----------------------
using ProductVariant = std::variant<
    StockData*,
    CallableBondData*,
    ConvertibleBondData*
>;

// ---------------------- PRICER VISITOR ----------------------
class PricerVisitor {
public:
    StockPricer stockPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;
    JunkStockPricer junkStockPricer;

    // Handle StockData with different pricer options
    double operator()(StockData* data) { return stockPricer.calculatePrice(data); }
    double operator()(CallableBondData* data) { return callablePricer.calculatePrice(data); }
    double operator()(ConvertibleBondData* data) { return convertiblePricer.calculatePrice(data); }
    
    // Additional method for junk stock pricing
    double calculateJunkPrice(StockData* data) { return junkStockPricer.calculatePrice(data); }
};

// ---------------------- UPDATED USAGE ----------------------
int main() {
    StockData stock;
    CallableBondData callableBond;
    ConvertibleBondData convertibleBond;

    // Create product variants
    std::vector<ProductVariant> products = {
        &stock,
        &callableBond,
        &convertibleBond
    };

    PricerVisitor visitor;

    // Process all products using visitor pattern
    std::cout << "Stock Price: " << std::visit(visitor, products[0]) << std::endl;
    std::cout << "Callable Bond Price: " << std::visit(visitor, products[1]) << std::endl;
    std::cout << "Convertible Bond Price: " << std::visit(visitor, products[2]) << std::endl;
    
    // Handle junk stock pricing separately
    std::cout << "Junk Stock Price: " << visitor.calculateJunkPrice(&stock) << std::endl;

    return 0;
}