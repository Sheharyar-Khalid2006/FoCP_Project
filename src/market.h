#ifndef MARKET_HPP
#define MARKET_HPP

// Initialize random number generator
void initializeRandom();

// General market fluctuation (±15%)
float generateMarketFluctuation();

// Stock market fluctuation (±10%)
float getStockFluctuation();

// Crypto market fluctuation (±22.5%)
float getCryptoFluctuation();

// Applies a simple trend based on duration
float applyMarketTrend(float baseFluctuation, int monthNumber);

#endif