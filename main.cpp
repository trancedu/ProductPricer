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

    // Process all products using visitor pattern
    std::cout << "Stock Price: " << std::visit(visitor, products[0]) << std::endl;
    std::cout << "Callable Bond Price: " << std::visit(visitor, products[1]) << std::endl;
    std::cout << "Convertible Bond Price: " << std::visit(visitor, products[2]) << std::endl;
    
    // Handle junk stock pricing separately
    std::cout << "Junk Stock Price: " << visitor.calculateJunkPrice(&stock) << std::endl;

    return 0;
}