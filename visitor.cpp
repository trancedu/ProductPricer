#include "visitor.h"

void PricerVisitor::operator()(const StockData& data) const {
    auto model = model_factory->createStockModel(data);
    std::cout << stock_pricer->getName() << " pricing " << data.ticker
              << ": " << stock_pricer->price(model, data) << "\n";
}

void PricerVisitor::operator()(const BondData& data) const {
    auto model = model_factory->createBondModel(data);
    std::cout << bond_pricer->getName() << " pricing " << data.ticker
              << ": " << bond_pricer->price(model, data) << "\n";
}

void PricerVisitor::operator()(const ConvertibleBondData& data) const {
    auto model = model_factory->createCBModel(data);
    std::cout << cb_pricer->getName() << " pricing " << data.ticker
              << ": " << cb_pricer->price(model, data) << "\n";
} 