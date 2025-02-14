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

// ---------------------- VANILLA BOND PRICER ----------------------
class VanillaBondPricer : public BondPricer<VanillaBondPricer, BondData> {
public:
    double calculatePriceImpl(BondData* bond) {
        double base_price = bond->bond_specific_value * 1.03;  // Different base multiplier
        return base_price + commonBondFunction(bond);
    }
};

// ---------------------- VARIANT TYPE DEFINITION ----------------------
using ProductVariant = std::variant<
    StockData*,
    BondData*,  // Add base BondData to variant
    CallableBond*,
    ConvertibleBond*
>;

// ---------------------- PRICER VISITOR ----------------------
class PricerVisitor {
public:
    StockPricer stockPricer;
    VanillaBondPricer vanillaBondPricer;  // Add vanilla bond pricer
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;
    JunkStockPricer junkStockPricer;

    // Add handler for base BondData
    double operator()(StockData* data) { return stockPricer.calculatePrice(data); }
    double operator()(BondData* data) { return vanillaBondPricer.calculatePrice(data); }
    double operator()(CallableBond* data) { return callablePricer.calculatePrice(data); }
    double operator()(ConvertibleBond* data) { return convertiblePricer.calculatePrice(data); }
    
    double calculateJunkPrice(StockData* data) { return junkStockPricer.calculatePrice(data); }
};

// ---------------------- UPDATED USAGE ----------------------
int main() {
    StockData stock;
    BondData vanillaBond;  // Base bond instance
    CallableBond callableBond;
    ConvertibleBond convertibleBond;

    // Create product variants
    std::vector<ProductVariant> products = {
        &stock,
        &vanillaBond,  // Add base bond to products
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