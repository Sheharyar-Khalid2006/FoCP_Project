#include "interface.hpp"
#include "validation.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <sstream>
#include <algorithm>
#include "market.h"
#include<thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

void simulate_investment(investment& inv) {
    int choice;
    bool exit = false;
    float fluctuation;
    bool loss = false;

    std::cout << "\t\tSTARTING SIMULATION\n";
    std::cout << "\n";

    std::cout << "Month | Fluctuation | Contribution | Portfolio Value\n";
    std::cout << "------|-------------|--------------|----------------\n";

    // Loop through each month
    for (int month = 1; month <= inv.total_months; month++) {
        inv.current_months = month;

        // Generate market fluctuation based on selected market type
        fluctuation = generateMarketFluctuation(inv.market);

        // Apply fluctuation to current value
        inv.current_amount = nextvalue(inv.current_amount, fluctuation);

        profit_loss(inv);
        // Add monthly contribution
        applyMonthlyContribution(inv);

        // Record this month's value
        inv.monthly_values.push_back(inv.current_amount);

        // Display progress
        std::cout << std::setw(5) << month << " | "
            << std::setw(10) << std::fixed << std::setprecision(2) << fluctuation << "% | "
            << std::setw(11) << inv.monthly_amount << " | "
            << std::setw(15) << inv.current_amount << "\n";

        // Display market events for significant fluctuations
        displayMarketEvent(inv.market, fluctuation);

        // Update progress bar every few months
        if (month % 3 == 0 || month == inv.total_months) {
            std::cout << "\n";
            displayProgressBar(month, inv.total_months, inv.current_amount);
            std::cout << "\n\n";
        }
        total_investment(inv);
        // Check if loss threshold has been reached
        if(!loss){
        if (check_loss(inv)) {
            loss = true;
            while (true) {
                std::cout << "\nWhat would you like to do?\n";
                std::cout << "1. Exit simulation (cut losses)\n";
                std::cout << "2. Continue investing (risk it all)\n";
                std::cout << "Enter choice: ";
                choice = getintinput();

                if (choice == 1) {
                    std::cout << "\nWise decision! Sometimes it's better to be safe than sorry.\n";
                    std::cout << "Final portfolio value: $" << std::fixed << std::setprecision(2)
                        << inv.current_amount << "\n";
                    exit = true;
                    break;
                }
                else if (choice == 2) {
                    std::cout << "\nBold choice! Risk it for the biscuit.\n";
                    std::cout << "Be prepared to face the cruelty of the business world.\n";
                    inv.stoploss = 100;
                    break;
                }
                else {
                    std::cout << "\nPlease enter 1 or 2.\n";
                }
            }
            if (exit) break;
        }}

        // Small delay for visualization
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\n";
    std::cout << "------------------------------------------------\n";

    // Final statistics
    total_investment(inv);
    profit_loss(inv);

    std::cout << "\t\tSIMULATION COMPLETED\n";
    std::cout << "\n";
}

int selectMarketType() {
    int choice;
    displayMarketTypes();
    
    while (true) {
        cout << "\nSelect market type (1-5): ";
        choice = getintinput();
        
        if (choice >= 1 && choice <= 5) {
            return choice;
        }
        
        cout << "Invalid choice. Please select between 1 and 5.\n";
    }
}






void updateLineChart(const vector<float>& values, int currentMonth) {
    if (values.empty() || currentMonth < 1) return;
    
    const int chartHeight = 10;
    const int chartWidth = min(50, static_cast<int>(values.size()));
    
    // Find min and max for scaling
    float minVal = *min_element(values.begin(), values.end());
    float maxVal = *max_element(values.begin(), values.end());
    float range = maxVal - minVal;
    
    if (range < 0.01f) range = 1.0f; // Avoid division by zero
    
    cout << "\n";
    
    // Draw chart
    for (int h = chartHeight; h >= 0; h--) {
        float threshold = minVal + (range * h / chartHeight);
        
        if (h == chartHeight) {
            cout << "  $" << fixed << setprecision(0) << setw(8) << maxVal << " │";
        } else if (h == 0) {
            cout << "  $" << fixed << setprecision(0) << setw(8) << minVal << " │";
        } else {
            cout << "\t│";
        }
        
        for (int w = 0; w < chartWidth && w < values.size(); w++) {
            if (abs(values[w] - threshold) < (range / chartHeight)) {
                cout << "●";
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    cout << "           └";
    for (int i = 0; i < chartWidth; i++) cout << "─";
    cout << "\n            0";
    for (int i = 0; i < chartWidth - 10; i++) cout << " ";
    cout << "Month " << currentMonth << "\n";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string formatCurrency(float amount) {
    ostringstream oss;
    oss << "$" << fixed << setprecision(2) << amount;
    return oss.str();
}

void displaySeparator() {
    cout << "--------------------------------------------\n";
}



void displayProfitLoss(float amount) {
    if (amount >= 0) {
        cout << "Profit: +" << formatCurrency(amount);
    } else {
        cout << "Loss: " << formatCurrency(amount);
    }
}


void displayMarketTypes() {
    cout << "\n\n";
    cout << "\t\tSELECT MARKET CONDITION\n";
    cout << "1. STABLE MARKET\n";
    cout << "\t Low volatility\n";
    cout << "\t Fluctuation: +2% to -2%\n";
    cout << "\t Best for: Conservative investors\n";
    cout << "\n";
    cout << "2. VOLATILE MARKET\n";
    cout << "\t High volatility\n";
    cout << "\t Fluctuation: +5% to -5%\n";
    cout << "\t Best for: Risk-tolerant investors\n";
    cout << "\n";
    cout << "3. BULLISH MARKET (Bull Run)\n";
    cout << "\t Generally upward trend\n";
    cout << "\t Fluctuation: -1% to +6%\n";
    cout << "\t Best for: Growth seekers\n";
    cout << "\n";
    cout << "4. BEARISH MARKET (Bear Market)\n";
    cout << "\t Generally downward trend\n";
    cout << "\t Fluctuation: -6% to +1%\n";
    cout << "\t Best for: Testing loss tolerance\n";
    cout << "\n";
    cout << "5. CRISIS MARKET\n";
    cout << "\t Extreme volatility\n";
    cout << "\t Fluctuation: +10% to -10%\n";
    cout << "\t Best for: Experienced investors only\n";
    cout << "\n";
}