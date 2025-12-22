#ifndef INVESTMENT_HPP
#define INVESTMENT_HPP
#include<vector>
struct investment {
	float initial_amount,current_amount,final_amount,safe_loss_percent,profit_loss,monthly_amount,total_amount,return_percent;
	int total_months, current_months,market;
	bool stoploss = false;

	std::vector<float> monthly_values;

};


// Display investment details before starting simulation
void displayInvestmentDetails(investment& inv);
// Display a progress bar for simulation
void displayProgressBar(int current, int total, float currentValue);

void start_investment(investment&);
float nextvalue(float, float);
bool check_loss(investment&);
void profit_loss(investment&);
void total_investment(investment&);
void applyMonthlyContribution(investment& inv);
void resetInvestment(investment& inv);
bool checkVirtualBalance(investment& inv, float available_balance, float min_invest);


#endif