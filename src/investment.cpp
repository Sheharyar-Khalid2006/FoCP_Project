/*#include <iostream>
#include "validation.h"
#include "investment.h"
#include<iomanip>
#include<thread>
#include<chrono>

void start_investment(investment& inv) {
	
	while (true) {
		std::cout << "\nEnter initial Investment amount in dollar: ";
		inv.initial_amount = getfloatinput();
		if (!amount_validation(inv.initial_amount)) {
			continue;
		}
		inv.monthly_values.push_back(inv.initial_amount);
		break;
	}
	while (true) {
		std::cout << "\nEnter monthly Investment (in dollars) : ";
		inv.monthly_amount = getfloatinput();
		if (!amount_validation(inv.monthly_amount)) {
			continue;
		}
		break;
	}
	while (true) {
		std::cout << "\nEnter investment duration (in months): ";
		inv.total_months= getintinput();
		if (!month_check(inv.total_months)) continue;
		break;
	}
	while (true) {
		std::cout << "\nEnter loss threshold: ";
		inv.safe_loss_percent = getfloatinput();
		if (!check_loss_threshold(inv.safe_loss_percent)) continue;
		break;
	}
}



float nextvalue(float previous, float percent_change) {
	return previous*(1.0f+(percent_change / 100));
}

void profit_loss(investment& inv) {
	inv.profit_loss = 100.0f*(inv.current_amount - inv.initial_amount) / inv.initial_amount;
}

bool check_loss(investment& inv) {
	if (inv.safe_loss_percent <= inv.profit_loss) {
		std::cout << "\nLoss threshold reached.\n It is recommended that you reclaim your invested amount.\n";
		return true;
	}
	return false;
}

void simulate_investment(investment& inv) {
	int choice;
	bool exit = false;

	std::cout << "\nStarting Simulation...\n";
	std::cout << "Month | Fluctuation | Contribution | Portfolio Value\n";
	std::cout << "------|-------------|--------------|----------------\n";

	// Loop through each month
	for (int month = 1; month <= inv.total_months; month++) {
		inv.current_months = month;

		//calculate market fluctuation
		//float fluctuation = generateMarketFluctuation(inv.market);
		//use the function for generating market fluctuations above.
	

		//Apply fluctuation to current value
		inv.current_amount = nextvalue(inv.current_amount, fluctuation);
		//Add monthly contribution
		applyMonthlyContribution(inv);

		//Record this month's value
		inv.monthly_values.push_back(inv.current_amount);

		//Display progress
		std::cout << std::setw(5) << month << " | "
			<< std::setw(10) << std:: fixed << std::setprecision(2) << fluctuation << "% | "
			<< std::setw(11) << inv.monthly_amount << " | "
			<< std::setw(15) << inv.current_amount << "\n";

		//Updateline chart
		//updateLineChart(inv.monthly_amount);

		// Check if loss threshold has reached
		if (check_loss(inv)) {
			while (true) {
				std::cout << "Would you like to exit as loss threshold is achieved.\n"
					<< "Your current loss is: " << inv.profit_loss << "%" 
					<< "(-" << inv.initial_amount - inv.current_amount << ")\n"
					<< "1.Exit\n2.Continue, risk it all.\n";
				choice = getintinput();
				if (choice == 1) {
					std::cout << "\nSigh, do not worry, loss is part of the journey.It is better to be safe than sorry.\n";
				}
				else if (choice == 2) {
					std::cout << "\nSo you will Risk it for the biscuit."
						<< "\nBe prepared to face cruelity of the business world.\n";
				}
				else {
					std::cout << "\nPlease enter correct choice.\n";
				}
				exit = true;
				break;  // Exit loop
			}
			if (exit) break;
		}

		// STEP 8: Small delay for visualization
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void total_investment(investment& inv) {
	inv.total_amount = inv.initial_amount;
	inv.total_amount += (inv.monthly_amount * inv.current_months);
}

void applyMonthlyContribution(investment& inv) {
	inv.current_amount += inv.monthly_amount;
	inv.total_amount += inv.monthly_amount;
}

float calc_percentage_return(investment& inv) {
	total_investment(inv);
	profit_loss(inv);

	float returnPercent = (inv.profit_loss/ inv.total_amount) * 100.0f;

	return returnPercent;
}

void resetInvestment(investment& inv) {
	inv.initial_amount = 0;
	inv.monthly_amount = 0;
	inv.total_months = 0;
	inv.current_amount= 0;
	inv.total_amount = 0;
	inv.current_months = 0;
	inv.profit_loss = 0;
	inv.return_percent = 0;
	inv.stoploss = false;
	inv.monthly_values.clear();

}

bool checkVirtualBalance(investment& inv, float available_balance, float min_invest) {
	//user invests more than he has
	if (inv.initial_amount > available_balance) {
		std::cout << "\nInsufficient balance.\n";
		std::cout << "Required: " << inv.initial_amount << "\n";
		std::cout << "Available: " << available_balance << "\n";
		return false;
	}


	//user has insufficient balance to buy the currency.
	else if (min_invest > available_balance) {
		std::cout << "\nInsufficient balance.\n";
		std::cout << "Required: " << min_invest << "\n";
		std::cout << "Available: " << available_balance << "\n";
		return false;
	}

	return true;
}*/

#include <iostream>
#include "validation.h"
#include "investment.h"
#include "interface.hpp"
#include <iomanip>
#include <thread>
#include <chrono>

void start_investment(investment& inv) {
	
	while (true) {
		std::cout << "\nEnter initial Investment amount in dollar: ";
		inv.initial_amount = getfloatinput();
		if (!amount_validation(inv.initial_amount)) {
			continue;
		}
		inv.monthly_values.push_back(inv.initial_amount);
		break;
	}
	while (true) {
		std::cout << "\nEnter monthly Investment (in dollars) : ";
		inv.monthly_amount = getfloatinput();
		if (!amount_validation(inv.monthly_amount)) {
			continue;
		}
		break;
	}
	while (true) {
		std::cout << "\nEnter investment duration (in months): ";
		inv.total_months = getintinput();
		if (!month_check(inv.total_months)) continue;
		break;
	}
	while (true) {
		std::cout << "\nEnter loss threshold (20-100%): ";
		inv.safe_loss_percent = getfloatinput();
		if (!check_loss_threshold(inv.safe_loss_percent)) continue;
		break;
	}
	
	// Select market type
	inv.market = selectMarketType();
	
	// Display configured investment details
	displayInvestmentDetails(inv);
	
	std::cout << "\nPress Enter to start simulation...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

float nextvalue(float previous, float percent_change) {
	return previous * (1.0f + (percent_change / 100.0f));
}

void profit_loss(investment& inv) {
	inv.profit_loss = 100.0f * (inv.current_amount - inv.initial_amount) / inv.initial_amount;
}

bool check_loss(investment& inv) {
	profit_loss(inv);
	
	if (inv.profit_loss <= -inv.safe_loss_percent) {
		std::cout << "\n\n  ═══════════════════════════════════════════════════ \n";
		std::cout << "     LOSS THRESHOLD REACHED!\n";
		std::cout << "     Current Loss: " << std::fixed << std::setprecision(2) 
		          << inv.profit_loss << "%\n";
		std::cout << "     Amount Lost: $" << std::fixed << std::setprecision(2) 
		          << (inv.initial_amount - inv.current_amount) << "\n";
		std::cout << "     It is recommended that you reclaim your invested amount.\n";
		std::cout << "  ═══════════════════════════════════════════════════ \n";
		return true;
	}
	return false;
}

void simulate_investment(investment& inv) {
	int choice;
	bool exit = false;

	std::cout << "\n\n╔════════════════════════════════════════════════════════╗\n";
	std::cout << "║              STARTING SIMULATION                       ║\n";
	std::cout << "╚════════════════════════════════════════════════════════╝\n\n";

	std::cout << "Month | Fluctuation | Contribution | Portfolio Value\n";
	std::cout << "------|-------------|--------------|----------------\n";

	// Loop through each month
	for (int month = 1; month <= inv.total_months; month++) {
		inv.current_months = month;

		// Generate market fluctuation based on selected market type
		float fluctuation = generateMarketFluctuation(inv.market);

		// Apply fluctuation to current value
		inv.current_amount = nextvalue(inv.current_amount, fluctuation);
		
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

		// Check if loss threshold has been reached
		if (check_loss(inv)) {
			while (true) {
				std::cout << "\nWhat would you like to do?\n";
				std::cout << "1. Exit simulation (cut losses)\n";
				std::cout << "2. Continue investing (risk it all)\n";
				std::cout << "Enter choice: ";
				choice = getintinput();
				
				if (choice == 1) {
					std::cout << "\n Wise decision! Sometimes it's better to be safe than sorry.\n";
					std::cout << "   Final portfolio value: $" << std::fixed << std::setprecision(2) 
					          << inv.current_amount << "\n";
					exit = true;
					break;
				}
				else if (choice == 2) {
					std::cout << "\n Bold choice! Risk it for the biscuit.\n";
					std::cout << "   Be prepared to face the cruelty of the business world.\n";
					break;
				}
				else {
					std::cout << "\n✗ Please enter 1 or 2.\n";
				}
			}
			if (exit) break;
		}

		// Small delay for visualization
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	std::cout << "\n";
	displaySeparator();
	
	// Final statistics
	total_investment(inv);
	profit_loss(inv);
	
	std::cout << "\n╔════════════════════════════════════════════════════════╗\n";
	std::cout << "║           SIMULATION COMPLETED                         ║\n";
	std::cout << "╚════════════════════════════════════════════════════════╝\n";
}

void total_investment(investment& inv) {
	inv.total_amount = inv.initial_amount;
	inv.total_amount += (inv.monthly_amount * inv.current_months);
}

void applyMonthlyContribution(investment& inv) {
	inv.current_amount += inv.monthly_amount;
	inv.total_amount += inv.monthly_amount;
}

float calc_percentage_return(investment& inv) {
	total_investment(inv);
	profit_loss(inv);

	float returnPercent = (inv.profit_loss / inv.total_amount) * 100.0f;

	return returnPercent;
}

void resetInvestment(investment& inv) {
	inv.initial_amount = 0;
	inv.monthly_amount = 0;
	inv.total_months = 0;
	inv.current_amount = 0;
	inv.total_amount = 0;
	inv.current_months = 0;
	inv.profit_loss = 0;
	inv.return_percent = 0;
	inv.stoploss = false;
	inv.market = 0;
	inv.monthly_values.clear();
}

bool checkVirtualBalance(investment& inv, float available_balance, float min_invest) {
	// User invests more than they have
	if (inv.initial_amount > available_balance) {
		std::cout << "\n✗ Insufficient balance.\n";
		std::cout << "  Required: $" << std::fixed << std::setprecision(2) 
		          << inv.initial_amount << "\n";
		std::cout << "  Available: $" << std::fixed << std::setprecision(2) 
		          << available_balance << "\n";
		return false;
	}

	// User has insufficient balance to buy the currency
	else if (min_invest > available_balance) {
		std::cout << "\n✗ Insufficient balance.\n";
		std::cout << "  Minimum required: $" << std::fixed << std::setprecision(2) 
		          << min_invest << "\n";
		std::cout << "  Available: $" << std::fixed << std::setprecision(2) 
		          << available_balance << "\n";
		return false;
	}

	return true;
}