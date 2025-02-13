#include "visitor.h"

void PricerVisitor::operator()(const StockData& data) const {
    StockModel model(data);
    std::cout << stock_pricer.getName() << " pricing " << data.ticker
              << ": " << stock_pricer.price(model) << "\n";
}

void PricerVisitor::operator()(const BondData& data) const {
    BondModel model(data);
    std::cout << bond_pricer.getName() << " pricing " << data.ticker
              << ": " << bond_pricer.price(model) << "\n";
}

void PricerVisitor::operator()(const ConvertibleBondData& data) const {
    ConvertibleBondModel model(data);
    std::cout << cb_pricer.getName() << " pricing " << data.ticker
              << ": " << cb_pricer.price(model) << "\n";
} 