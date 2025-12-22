#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "investment.h"
#include <string>


// Display a simple ASCII chart during simulation
void updateLineChart(const std::vector<float>& values, int currentMonth);

// Clear screen (cross-platform)
void clearScreen();

// Display market news/events
void displayMarketEvent(int marketType, float fluctuation);


void simulate_investment(investment& inv);

// Format currency for display
std::string formatCurrency(float amount);

// Display a separator line
void displaySeparator();

// Display color-coded profit/loss
void displayProfitLoss(float amount);

#endif