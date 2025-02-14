#include "visitor.h"
#include "model_factory.h"
#include <vector>

int main() {
    // Create data
    StockData stock("AAPL", 1500.0, 100.0);
    BondData bond("US10Y", 5000.0, 200.0);
    ConvertibleBondData cbond("CB123", 3000.0, 150.0, 1.2);

    // Create different pricers and models
    StockPricer defaultStockPricer;
    BondPricer defaultBondPricer;
    ConvertibleBondPricer defaultCBPricer;
    
    DefaultModelFactory defaultModelFactory;
    AggressiveModelFactory aggressiveModels;

    // Create visitor with initial configuration
    PricerVisitor visitor;
    visitor.setStockPricer(&defaultStockPricer);
    visitor.setBondPricer(&defaultBondPricer);
    visitor.setConvertibleBondPricer(&defaultCBPricer);
    visitor.setModelFactory(&defaultModelFactory);

    std::vector<InstrumentVariant> instruments = {stock, bond, cbond};

    // First pass with default configuration
    std::cout << "=== Default Pricing ===" << std::endl;
    for (const auto& instrument : instruments) {
        std::visit(visitor, instrument);
    }

    // Create alternative implementations
    class DiscountedStockPricer : public StockPricer {
    public:
        std::string getName() const override { return "Discounted Stock Pricer"; }
        double price(const StockModel& model, const StockData& data) const override {
            return StockPricer::price(model, data) * 0.9;
        }
    };

    // Switch to new configuration
    DiscountedStockPricer discountedPricer;
    
    std::cout << "\n=== Modified Pricing ===" << std::endl;
    visitor.setStockPricer(&discountedPricer);
    visitor.setModelFactory(&aggressiveModels);
    
    for (const auto& instrument : instruments) {
        std::visit(visitor, instrument);
    }

    return 0;
}
