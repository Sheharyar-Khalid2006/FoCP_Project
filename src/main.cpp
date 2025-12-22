#include <iostream>
#include <iomanip>
#include <limits>
#include "investment.h"
#include "validation.h"
#include "graph.hpp"

using namespace std;

void displayWelcome() {
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║     INVESTMENT SIMULATION GAME                 ║\n";
    cout << "║     Learn Investment Through Practice          ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
}

void displayMenu() {
    cout << "\n┌─────────────── MAIN MENU ───────────────┐\n";
    cout << "│  1. Start New Investment Simulation     │\n";
    cout << "│  2. View Investment Summary              │\n";
    cout << "│  3. Generate Growth Chart                │\n";
    cout << "│  4. Generate Comparison Chart            │\n";
    cout << "│  5. Reset Investment                     │\n";
    cout << "│  6. How to Play                          │\n";
    cout << "│  7. Exit                                 │\n";
    cout << "└──────────────────────────────────────────┘\n";
    cout << "Enter your choice: ";
}

void displayInstructions() {
    cout << "\n╔════════════════════════════════════════════════════════════╗\n";
    cout << "║                    HOW TO PLAY                             ║\n";
    cout << "╠════════════════════════════════════════════════════════════╣\n";
    cout << "║ 1. Start with an initial investment amount                 ║\n";
    cout << "║ 2. Choose monthly contribution amount                      ║\n";
    cout << "║ 3. Select investment duration (max 36 months)              ║\n";
    cout << "║ 4. Set a safe loss threshold (20-100%)                     ║\n";
    cout << "║ 5. Watch your investment grow (or shrink) with market     ║\n";
    cout << "║    fluctuations                                             ║\n";
    cout << "║ 6. If losses exceed your threshold, you'll be warned       ║\n";
    cout << "║ 7. Generate charts to visualize your investment journey    ║\n";
    cout << "╠════════════════════════════════════════════════════════════╣\n";
    cout << "║ TIPS:                                                       ║\n";
    cout << "║ • Diversification helps reduce risk                         ║\n";
    cout << "║ • Long-term investments often perform better                ║\n";
    cout << "║ • Don't panic during market downturns                       ║\n";
    cout << "║ • Regular monthly contributions help average costs          ║\n";
    cout << "╚════════════════════════════════════════════════════════════╝\n";
}

void displaySummary(investment& inv) {
    if (inv.monthly_values.empty()) {
        cout << "\nNo investment data available. Please run a simulation first.\n";
        return;
    }

    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║           INVESTMENT SUMMARY                   ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    cout << "║ Initial Investment:    $" << setw(18) << fixed << setprecision(2) 
         << inv.initial_amount << " ║\n";
    cout << "║ Monthly Contribution:  $" << setw(18) << fixed << setprecision(2) 
         << inv.monthly_amount << " ║\n";
    cout << "║ Total Invested:        $" << setw(18) << fixed << setprecision(2) 
         << inv.total_amount << " ║\n";
    cout << "║ Current Value:         $" << setw(18) << fixed << setprecision(2) 
         << inv.current_amount << " ║\n";
    cout << "║ Duration:              " << setw(19) << inv.current_months 
         << " months ║\n";
    cout << "╠════════════════════════════════════════════════╣\n";
    
    float profit_loss = inv.current_amount - inv.total_amount;
    float percentage = (profit_loss / inv.total_amount) * 100.0f;
    
    if (profit_loss >= 0) {
        cout << "║ 📈 PROFIT:             $" << setw(18) << fixed << setprecision(2) 
             << profit_loss << " ║\n";
        cout << "║ Return:                " << setw(18) << fixed << setprecision(2) 
             << percentage << "% ║\n";
    } else {
        cout << "║ 📉 LOSS:               $" << setw(18) << fixed << setprecision(2) 
             << abs(profit_loss) << " ║\n";
        cout << "║ Loss:                  " << setw(18) << fixed << setprecision(2) 
             << percentage << "% ║\n";
    }
    cout << "╚════════════════════════════════════════════════╝\n";
}

int main() {
    investment myInvestment;
    resetInvestment(myInvestment);
    
    int choice;
    bool running = true;
    
    displayWelcome();
    
    while (running) {
        displayMenu();
        choice = getintinput();
        
        switch (choice) {
            case 1: {
                cout << "\n--- Starting New Investment Simulation ---\n";
                resetInvestment(myInvestment);
                start_investment(myInvestment);
                myInvestment.current_amount = myInvestment.initial_amount;
                simulate_investment(myInvestment);
                
                cout << "\n✓ Simulation completed!\n";
                displaySummary(myInvestment);
                break;
            }
            
            case 2: {
                displaySummary(myInvestment);
                break;
            }
            
            case 3: {
                if (myInvestment.monthly_values.size() > 0) {
                    cout << "\nGenerating investment growth chart...\n";
                    bool success = generateInvestmentChart(myInvestment, "investment_growth.png");
                    displayChartStatus(success, "investment_growth.png");
                } else {
                    cout << "\nNo data available. Please run a simulation first.\n";
                }
                break;
            }
            
            case 4: {
                if (myInvestment.monthly_values.size() > 0) {
                    cout << "\nGenerating comparison chart...\n";
                    bool success = generateComparisonChart(myInvestment, "investment_comparison.png");
                    displayChartStatus(success, "investment_comparison.png");
                } else {
                    cout << "\nNo data available. Please run a simulation first.\n";
                }
                break;
            }
            
            case 5: {
                resetInvestment(myInvestment);
                cout << "\n✓ Investment data has been reset.\n";
                break;
            }
            
            case 6: {
                displayInstructions();
                break;
            }
            
            case 7: {
                cout << "\n╔════════════════════════════════════════╗\n";
                cout << "║  Thank you for using our simulator!    ║\n";
                cout << "║  Remember: Practice makes perfect!     ║\n";
                cout << "╚════════════════════════════════════════╝\n\n";
                running = false;
                break;
            }
            
            default: {
                cout << "\n✗ Invalid choice. Please enter a number between 1 and 7.\n";
                break;
            }
        }
        
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    
    return 0;
}