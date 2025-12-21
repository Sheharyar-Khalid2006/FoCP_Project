#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "investment.h"
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>
#include <string>

// Generate line chart for investment growth over time
bool generateInvestmentChart(investment& inv, std::string filename = "investment_chart.png");

// Generate bar chart comparing initial vs final amount
bool generateComparisonChart(investment& inv, std::string filename = "comparison_chart.png");

// Display chart generation success/failure message
void displayChartStatus(bool success, std::string filename);

#endif