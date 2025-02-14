#include <iostream>
#include <vector>
#include "Visitor.h"
#include "ProductVariant.h"

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
    TypeNameVisitor typeVisitor;

    // Process all products using visitor pattern
    std::cout << " Data: " << std::visit(typeVisitor, products[0])
              << " Pricer: " << visitor.stockPricer.getName() 
              << " Stock Price: " << std::visit(visitor, products[0]) << std::endl;

    std::cout << " Data: " << std::visit(typeVisitor, products[1])
              << " Pricer: " << visitor.callablePricer.getName() 
              << " Callable Bond Price: " << std::visit(visitor, products[1]) << std::endl;

    std::cout << " Data: " << std::visit(typeVisitor, products[2])
              << " Pricer: " << visitor.convertiblePricer.getName() 
              << " Convertible Bond Price: " << std::visit(visitor, products[2]) << std::endl;
    
    // Handle junk stock pricing separately
    std::cout << " Data: " << stock.typeName
              << " Pricer: " << visitor.junkStockPricer.getName() 
              << " Junk Stock Price: " << visitor.calculateJunkPrice(&stock) << std::endl;

    return 0;
}