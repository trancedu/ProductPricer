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

// ====================== PRICER INTERFACES ======================
class StockPricerInterface {
public:
    virtual double calculatePrice(const StockData* data) const = 0;
    virtual ~StockPricerInterface() = default;
};

class CallableBondPricerInterface {
public:
    virtual double calculatePrice(const CallableBond* data) const = 0;
    virtual ~CallableBondPricerInterface() = default;
};

class ConvertibleBondPricerInterface {
public:
    virtual double calculatePrice(const ConvertibleBond* data) const = 0;
    virtual ~ConvertibleBondPricerInterface() = default;
};

// ====================== UPDATED PRICERS ======================
template <typename Derived, typename DataType>
class Pricer {
public:
    double calculatePrice(const DataType* data) const {
        return static_cast<const Derived*>(this)->calculatePriceImpl(data);
    }
};

class StockPricer : public Pricer<StockPricer, StockData>, public StockPricerInterface {
public:
    double calculatePriceImpl(const StockData* data) const {
        return data->stock_specific_value * 1.1;
    }
    
    double calculatePrice(const StockData* data) const override {
        return Pricer<StockPricer, StockData>::calculatePrice(data);
    }
};

class JunkStockPricer : public Pricer<JunkStockPricer, StockData>, public StockPricerInterface {
public:
    double calculatePriceImpl(const StockData* data) const {
        return data->stock_specific_value * 0.5;
    }
    
    double calculatePrice(const StockData* data) const override {
        return Pricer<JunkStockPricer, StockData>::calculatePrice(data);
    }
};

// ---------------------- BOND PRICER (INTERMEDIATE CLASS) ----------------------
template <typename Derived, typename BondType>
class BondPricer : public Pricer<Derived, BondType> {
public:
    double commonBondFunction(BondType* bond) const {
        return bond->bond_specific_value * 0.02;
    }
};

// ---------------------- CALLABLE BOND PRICER ----------------------
class CallableBondPricer : public BondPricer<CallableBondPricer, CallableBond>, 
                          public CallableBondPricerInterface {
public:
    double calculatePriceImpl(const CallableBond* bond) const {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->callable_premium + commonBondFunction(const_cast<CallableBond*>(bond));
    }
    
    double calculatePrice(const CallableBond* data) const override {
        return Pricer<CallableBondPricer, CallableBond>::calculatePrice(data);
    }
};

// ---------------------- CONVERTIBLE BOND PRICER ----------------------
class ConvertibleBondPricer : public BondPricer<ConvertibleBondPricer, ConvertibleBond>, 
                             public ConvertibleBondPricerInterface {
public:
    double calculatePriceImpl(const ConvertibleBond* bond) const {
        double base_price = bond->bond_specific_value * 1.05;
        return base_price + bond->conversion_ratio * 100 + commonBondFunction(const_cast<ConvertibleBond*>(bond));
    }
    
    double calculatePrice(const ConvertibleBond* data) const override {
        return Pricer<ConvertibleBondPricer, ConvertibleBond>::calculatePrice(data);
    }
};

// ====================== VISITOR ======================
using InstrumentVariant = std::variant<StockData, CallableBond, ConvertibleBond>;

struct PricingVisitor {
    const StockPricerInterface* stock_pricer;
    const CallableBondPricerInterface* callable_pricer;
    const ConvertibleBondPricerInterface* convertible_pricer;
    
    void operator()(const StockData& data) const {
        std::cout << "Stock Price: " << stock_pricer->calculatePrice(&data) << std::endl;
    }
    
    void operator()(const CallableBond& data) const {
        std::cout << "Callable Bond Price: " << callable_pricer->calculatePrice(&data) << std::endl;
    }
    
    void operator()(const ConvertibleBond& data) const {
        std::cout << "Convertible Bond Price: " << convertible_pricer->calculatePrice(&data) << std::endl;
    }
};

// ====================== UPDATED USAGE ======================
int main() {
    StockData stock;
    CallableBond callableBond;
    ConvertibleBond convertibleBond;

    // Create pricers
    StockPricer stockPricer;
    JunkStockPricer junkPricer;
    CallableBondPricer callablePricer;
    ConvertibleBondPricer convertiblePricer;

    // Create instrument collection
    std::vector<InstrumentVariant> instruments = {stock, callableBond, convertibleBond};

    // Create visitor with different pricing strategies
    PricingVisitor defaultVisitor{&stockPricer, &callablePricer, &convertiblePricer};
    PricingVisitor junkStockVisitor{&junkPricer, &callablePricer, &convertiblePricer};

    std::cout << "=== Default Pricing ===" << std::endl;
    for (const auto& instrument : instruments) {
        std::visit(defaultVisitor, instrument);
    }

    std::cout << "\n=== Junk Stock Pricing ===" << std::endl;
    for (const auto& instrument : instruments) {
        std::visit(junkStockVisitor, instrument);
    }

    return 0;
}