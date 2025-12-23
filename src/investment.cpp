#include <iostream>
#include "validation.h"
#include "investment.h"
#include <iomanip>
#include <thread>
#include <chrono>
#include "market.h"
#include "graph.hpp"

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
	return (previous  + previous*(percent_change / 100));
}

void profit_loss(investment& inv) {
	inv.profit_loss = 100.0 * (inv.current_amount - inv.initial_amount) / inv.initial_amount;
}

bool check_loss(investment& inv) {
	profit_loss(inv);
	
	float checkloss = 100*(inv.current_amount - inv.total_amount)/inv.total_amount;
	if (checkloss <= -inv.safe_loss_percent) {
		std::cout << "\n\n";
		std::cout << "\tLOSS THRESHOLD REACHED!\n";
		std::cout << "\tCurrent Loss: " << std::fixed << std::setprecision(2) 
		          << inv.profit_loss << "%\n";
		std::cout << "\tAmount Lost: $" << std::fixed << std::setprecision(2) 
		          << (inv.initial_amount - inv.current_amount) << "\n";
		std::cout << "\tIt is recommended that you reclaim your invested amount.\n";
		std::cout << "\n";
		return true;
	}
	return false;
}


void total_investment(investment& inv) {
	inv.total_amount = inv.initial_amount;
	inv.total_amount += (inv.monthly_amount * inv.current_months);
}

void applyMonthlyContribution(investment& inv) {
	inv.current_amount += inv.monthly_amount;
	inv.total_amount += inv.monthly_amount;
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
		std::cout << "\nInsufficient balance.\n";
		std::cout << "Required: $" << std::fixed << std::setprecision(2) 
		          << inv.initial_amount << "\n";
		std::cout << "Available: $" << std::fixed << std::setprecision(2) 
		          << available_balance << "\n";
		return false;
	}

	// User has insufficient balance to buy the currency
	else if (min_invest > available_balance) {
		std::cout << "\nInsufficient balance.\n";
		std::cout << "Minimum required: $" << std::fixed << std::setprecision(2) 
		          << min_invest << "\n";
		std::cout << "Available: $" << std::fixed << std::setprecision(2) 
		          << available_balance << "\n";
		return false;
	}

	return true;
}


void displayProgressBar(int current, int total, float currentValue) {
	int barWidth = 40;
	float progress = static_cast<float>(current) / total;
	int pos = static_cast<int>(barWidth * progress);

	std::cout << "\r[";
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "[]";
		else if (i == pos) std::cout << "[]";
		else std::cout << "  ";
	}
	std::cout << "] " << int(progress * 100.0) << "% | Month " << current << "/" << total;
	std::cout << " | Value: $" << std::fixed << std::setprecision(2) << currentValue;
	std::cout << std::flush;
}


void displayInvestmentDetails(investment& inv) {
	std::cout << "\n-------------------------------------------------\n";
	std::cout << "\tINVESTMENT CONFIGURATION";
	std::cout << "\n-------------------------------------------------\n";
	std::cout << "Initial Investment: $" << std::setw(23) << std::fixed << std::setprecision(2)
		<< inv.initial_amount << "\n";
	std::cout << "\tMonthly Contribution: $" << std::setw(23) << std::fixed << std::setprecision(2)
		<< inv.monthly_amount << "\n";
	std::cout << "Duration: " << std::setw(23) << inv.total_months << " months \n";
	std::cout << "Loss Threshold:" << std::setw(23) << std::fixed << std::setprecision(1)
		<< inv.safe_loss_percent << "%\n";
	std::cout << "Market Type: " << std::setw(23) << getMarketTypeName(inv.market) << "\n";
	std::cout << "---------------------------\n";
}