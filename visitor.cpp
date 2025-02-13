#include "visitor.h"

void PricerVisitor::operator()(const StockData& data) const {
    std::cout << stock_pricer.getName() << " pricing " << data.ticker
              << ": " << stock_pricer.price(&data) << "\n";
}

void PricerVisitor::operator()(const BondData& data) const {
    std::cout << bond_pricer.getName() << " pricing " << data.ticker
              << ": " << bond_pricer.price(&data) << "\n";
}

void PricerVisitor::operator()(const ConvertibleBondData& data) const {
    std::cout << cb_pricer.getName() << " pricing " << data.ticker
              << ": " << cb_pricer.price(&data) << "\n";
} 