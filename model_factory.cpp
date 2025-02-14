#include "model_factory.h"

// Default implementations
StockModel DefaultModelFactory::createStockModel(const StockData& data) const {
    return StockModel(data);
}

BondModel DefaultModelFactory::createBondModel(const BondData& data) const {
    return BondModel(data);
}

ConvertibleBondModel DefaultModelFactory::createCBModel(const ConvertibleBondData& data) const {
    return ConvertibleBondModel(data);
}

// Aggressive implementations 
StockModel AggressiveModelFactory::createStockModel(const StockData& data) const {
    return StockModel(data); // Could use different model
}

BondModel AggressiveModelFactory::createBondModel(const BondData& data) const {
    return BondModel(data); // Could use different model
}

ConvertibleBondModel AggressiveModelFactory::createCBModel(const ConvertibleBondData& data) const {
    return ConvertibleBondModel(data); // Could use different model
} 