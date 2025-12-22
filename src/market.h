#ifndef MARKET_HPP
#define MARKET_HPP

#include<string>


// Market types
enum MarketType {
    STABLE = 1,
    VOLATILE = 2,
    BULLISH = 3,
    BEARISH = 4,
    CRISIS = 5
};

// Display market type selection menu
void displayMarketTypes();

// Select market type for simulation
int selectMarketType();

// Generate market fluctuation based on market type
float generateMarketFluctuation(int marketType);

// Stock market fluctuation (±10%)
float getStockFluctuation();

// Crypto market fluctuation (±22.5%)
float getCryptoFluctuation();

// Applies a simple trend based on duration
float applyMarketTrend(float baseFluctuation, int monthNumber);


std::string getMarketTypeName(int marketType);

#endif