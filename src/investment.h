#ifndef INVESTMENT.HPP
#define INVESTMENT.HPP
#include<vector>
struct investment {
	float initial_amount,current_amount,final_amount,safe_loss_percent,profit_loss,monthly_amount,total_amount,return_percent;
	int total_months, current_months,market;
	bool stoploss = false;

	std::vector<float> monthly_values;

};

void start_investment(investment&);
float nextvalue(float, float);
bool check_loss(investment&);
void profit_loss(investment&);
void simulate_investment(investment&);
void total_investment(investment&);
void applyMonthlyContribution(investment& inv);
float calc_percentage_return(investment& inv);
void resetInvestment(investment& inv);
bool checkVirtualBalance(investment& inv, float available_balance, float min_invest);


#endif