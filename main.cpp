#include "visitor.h"
#include <vector>

int main() {
    StockData stock("AAPL", 1500.0, 100.0);
    BondData bond("US10Y", 5000.0, 200.0);
    ConvertibleBondData cbond("CB123", 3000.0, 150.0, 1.2);

    StockPricer stockPricer;
    BondPricer bondPricer;
    ConvertibleBondPricer cbPricer;

    std::vector<InstrumentVariant> instruments = {stock, bond, cbond};

    const PricerVisitor visitor{stockPricer, bondPricer, cbPricer};
    for (const auto& instrument : instruments) {
        std::visit(visitor, instrument);
    }

    return 0;
}
