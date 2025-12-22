#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "investment.h"
#include <string>

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

// Display a progress bar for simulation
void displayProgressBar(int current, int total, float currentValue);

// Display investment details before starting simulation
void displayInvestmentDetails(investment& inv);

// Display a simple ASCII chart during simulation
void updateLineChart(const std::vector<float>& values, int currentMonth);

// Clear screen (cross-platform)
void clearScreen();

// Display market news/events
void displayMarketEvent(int marketType, float fluctuation);

// Format currency for display
std::string formatCurrency(float amount);

// Display a separator line
void displaySeparator();

// Get market type name
std::string getMarketTypeName(int marketType);

// Display color-coded profit/loss
void displayProfitLoss(float amount);

#endif