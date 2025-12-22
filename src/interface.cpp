#include "interface.hpp"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

using namespace std;

void displayMarketTypes() {
    cout << "\n╔═════════════════════════════════════════════════════════╗\n";
    cout << "║               SELECT MARKET CONDITION                   ║\n";
    cout << "╠═════════════════════════════════════════════════════════╣\n";
    cout << "║  1. STABLE MARKET                                       ║\n";
    cout << "║     • Low volatility                                    ║\n";
    cout << "║     • Fluctuation: ±2%                                  ║\n";
    cout << "║     • Best for: Conservative investors                  ║\n";
    cout << "║                                                         ║\n";
    cout << "║  2. VOLATILE MARKET                                     ║\n";
    cout << "║     • High volatility                                   ║\n";
    cout << "║     • Fluctuation: ±5%                                  ║\n";
    cout << "║     • Best for: Risk-tolerant investors                 ║\n";
    cout << "║                                                         ║\n";
    cout << "║  3. BULLISH MARKET (Bull Run)                          ║\n";
    cout << "║     • Generally upward trend                            ║\n";
    cout << "║     • Fluctuation: -1% to +6%                          ║\n";
    cout << "║     • Best for: Growth seekers                          ║\n";
    cout << "║                                                         ║\n";
    cout << "║  4. BEARISH MARKET (Bear Market)                       ║\n";
    cout << "║     • Generally downward trend                          ║\n";
    cout << "║     • Fluctuation: -6% to +1%                          ║\n";
    cout << "║     • Best for: Testing loss tolerance                  ║\n";
    cout << "║                                                         ║\n";
    cout << "║  5. CRISIS MARKET                                       ║\n";
    cout << "║     • Extreme volatility                                ║\n";
    cout << "║     • Fluctuation: ±10%                                 ║\n";
    cout << "║     • Best for: Experienced investors only              ║\n";
    cout << "╚═════════════════════════════════════════════════════════╝\n";
}

int selectMarketType() {
    int choice;
    displayMarketTypes();
    
    while (true) {
        cout << "\nSelect market type (1-5): ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }
        
        if (choice >= 1 && choice <= 5) {
            return choice;
        }
        
        cout << "Invalid choice. Please select between 1 and 5.\n";
    }
}

float generateMarketFluctuation(int marketType) {
    random_device rd;
    mt19937 gen(rd());
    
    float fluctuation = 0.0f;
    
    switch (marketType) {
        case STABLE: {
            // Stable market: -2% to +2%
            uniform_real_distribution<float> dis(-2.0f, 2.0f);
            fluctuation = dis(gen);
            break;
        }
        
        case VOLATILE: {
            // Volatile market: -5% to +5%
            uniform_real_distribution<float> dis(-5.0f, 5.0f);
            fluctuation = dis(gen);
            break;
        }
        
        case BULLISH: {
            // Bullish market: -1% to +6% (bias towards positive)
            uniform_real_distribution<float> dis(-1.0f, 6.0f);
            fluctuation = dis(gen);
            break;
        }
        
        case BEARISH: {
            // Bearish market: -6% to +1% (bias towards negative)
            uniform_real_distribution<float> dis(-6.0f, 1.0f);
            fluctuation = dis(gen);
            break;
        }
        
        case CRISIS: {
            // Crisis market: -10% to +10% (extreme volatility)
            uniform_real_distribution<float> dis(-10.0f, 10.0f);
            fluctuation = dis(gen);
            break;
        }
        
        default: {
            uniform_real_distribution<float> dis(-2.0f, 2.0f);
            fluctuation = dis(gen);
            break;
        }
    }
    
    return fluctuation;
}

void displayProgressBar(int current, int total, float currentValue) {
    int barWidth = 40;
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);
    
    cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) cout << "█";
        else if (i == pos) cout << "▓";
        else cout << "░";
    }
    cout << "] " << int(progress * 100.0) << "% | Month " << current << "/" << total;
    cout << " | Value: $" << fixed << setprecision(2) << currentValue;
    cout << flush;
}

void displayInvestmentDetails(investment& inv) {
    cout << "\n╔═════════════════════════════════════════════════════╗\n";
    cout << "║           INVESTMENT CONFIGURATION                  ║\n";
    cout << "╠═════════════════════════════════════════════════════╣\n";
    cout << "║ Initial Investment:     $" << setw(23) << fixed << setprecision(2) 
         << inv.initial_amount << " ║\n";
    cout << "║ Monthly Contribution:   $" << setw(23) << fixed << setprecision(2) 
         << inv.monthly_amount << " ║\n";
    cout << "║ Duration:               " << setw(23) << inv.total_months << " months ║\n";
    cout << "║ Loss Threshold:         " << setw(23) << fixed << setprecision(1) 
         << inv.safe_loss_percent << "% ║\n";
    cout << "║ Market Type:            " << setw(23) << getMarketTypeName(inv.market) << " ║\n";
    cout << "╚═════════════════════════════════════════════════════╝\n";
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
            cout << "           │";
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

void displayMarketEvent(int marketType, float fluctuation) {
    if (abs(fluctuation) < 1.0f) return; // Don't show minor fluctuations
    
    cout << "  📊 ";
    
    if (fluctuation > 5.0f) {
        cout << "Major rally! Market surged " << fixed << setprecision(2) << fluctuation << "%";
    } else if (fluctuation > 3.0f) {
        cout << "Strong gains! Market up " << fixed << setprecision(2) << fluctuation << "%";
    } else if (fluctuation > 1.0f) {
        cout << "Modest growth, market up " << fixed << setprecision(2) << fluctuation << "%";
    } else if (fluctuation < -5.0f) {
        cout << "⚠️ Market crash! Down " << fixed << setprecision(2) << abs(fluctuation) << "%";
    } else if (fluctuation < -3.0f) {
        cout << "⚠️ Sharp decline! Down " << fixed << setprecision(2) << abs(fluctuation) << "%";
    } else if (fluctuation < -1.0f) {
        cout << "Market dip, down " << fixed << setprecision(2) << abs(fluctuation) << "%";
    }
    
    cout << "\n";
}

string formatCurrency(float amount) {
    ostringstream oss;
    oss << "$" << fixed << setprecision(2) << amount;
    return oss.str();
}

void displaySeparator() {
    cout << "─────────────────────────────────────────────────────────\n";
}

string getMarketTypeName(int marketType) {
    switch (marketType) {
        case STABLE: return "Stable";
        case VOLATILE: return "Volatile";
        case BULLISH: return "Bullish";
        case BEARISH: return "Bearish";
        case CRISIS: return "Crisis";
        default: return "Unknown";
    }
}

void displayProfitLoss(float amount) {
    if (amount >= 0) {
        cout << "💰 Profit: +" << formatCurrency(amount);
    } else {
        cout << "📉 Loss: " << formatCurrency(amount);
    }
}