#include <iostream>
#include <vector>
#include "Visitor.h"
#include "ProductVariant.h"
#include "Model.h"

// ---------------------- UPDATED USAGE ----------------------
int main() {
    StockData stock;
    CallableBondData callableBond;
    ConvertibleBondData convertibleBond;

    // Create product variants
    std::vector<ProductVariant> products = {
        stock,
        callableBond,
        convertibleBond
    };

    PricerVisitor visitor;
    TypeNameVisitor typeVisitor;
    PricerNameVisitor nameVisitor(visitor);

    // Process all products using visitor pattern
    for (const auto& product : products) {
        std::cout << " Data: " << std::visit(typeVisitor, product)
                  << " Pricer: " << std::visit(nameVisitor, product)
                  << " Price: " << std::visit(visitor, product) << std::endl;
    }
    
    // Handle junk stock pricing separately
    std::cout << " Data: " << stock.typeName
              << " Pricer: " << visitor.junkStockPricer.getName() 
              << " Junk Stock Price: " << visitor.calculateJunkPrice(stock) << std::endl;

    // ---------------------- UPDATED USAGE ----------------------
    PricerModelVisitor modelVisitor;
    for (const auto& product : products) {
        std::cout << " Data: " << std::visit(typeVisitor, product)
                  << " Model: " << std::visit(modelVisitor, product)
                  << " Value: " << std::visit(modelVisitor, product) << std::endl;
    }
    return 0;
}