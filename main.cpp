#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

// ======== Base Data Class (Common Attributes) ======== //
class BaseData {
public:
    std::string ticker;
    double market_cap;

    explicit BaseData(std::string ticker, double market_cap)
        : ticker(std::move(ticker)), market_cap(market_cap) {}

    virtual ~BaseData() = default;
};

// ======== StockData & BondData (Specialized Data) ======== //
class StockData : public BaseData {
public:
    double stock_value;

    StockData(std::string ticker, double market_cap, double value)
        : BaseData(std::move(ticker), market_cap), stock_value(value) {}
};

class BondData : public BaseData {
public:
    double bond_value;

    BondData(std::string ticker, double market_cap, double value)
        : BaseData(std::move(ticker), market_cap), bond_value(value) {}
};

// ======== Base Pricer Class ======== //
class BasePricer {
public:
    virtual ~BasePricer() = default;
    virtual std::string getName() const = 0;
};

// ======== StockPricer ======== //
class StockPricer : public BasePricer {
public:
    std::string getName() const override {
        return "Stock Pricer";
    }

    double price(const StockData* stockData) const {
        return stockData->stock_value * 1.1;  // Example pricing formula
    }
};

// ======== BondPricer ======== //
class BondPricer : public BasePricer {
public:
    std::string getName() const override {
        return "Bond Pricer";
    }

    double price(const BondData* bondData) const {
        return bondData->bond_value * 0.9;  // Example pricing formula
    }
};

// ======== Variant-Based Pricing Mechanism ======== //
// Use std::variant to hold StockData or BondData
using InstrumentVariant = std::variant<StockData, BondData>;

// ======== Pricer Visitor ======== //
struct PricerVisitor {
    // Store pricers by reference (ensure they outlive this visitor)
    const StockPricer& stock_pricer;
    const BondPricer& bond_pricer;

    void operator()(const StockData& data) const {
        std::cout << stock_pricer.getName() << " pricing " << data.ticker
                  << ": " << stock_pricer.price(&data) << "\n";
    }

    void operator()(const BondData& data) const {
        std::cout << bond_pricer.getName() << " pricing " << data.ticker
                  << ": " << bond_pricer.price(&data) << "\n";
    }
};

int main() {
    // Create stock and bond data
    StockData stock("AAPL", 1500.0, 100.0);
    BondData bond("US10Y", 5000.0, 200.0);

    // Create pricers
    StockPricer stockPricer;
    BondPricer bondPricer;

    // Store financial instruments in a vector
    std::vector<InstrumentVariant> instruments = {stock, bond};

    // Process pricing using visitor pattern
    const PricerVisitor visitor{stockPricer, bondPricer};
    for (const auto& instrument : instruments) {
        std::visit(visitor, instrument);
    }

    return 0;
}
