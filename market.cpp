#include"market.h"
#include<cstdlib>
#include<ctime>

void initializeRandom() {
	srand(time(0));
}

float generateMarketFluctuation() {
	// Random integer from -1500 to +1500
	int randomValue = rand() % 3000 - 1500;

	// Convert to percentage with 2 decimals: -15.00 to +15.00
	return randomValue / 100.0;
}

float getStockFluctuation() {
	// Random integer from -1000 to +1000
	int randomNumber = rand() % 2000 - 1000;

	// Convert to percentage with 2 decimals: -10.00 to +10.00
	return randomNumber / 100.0;
}

float getCryptoFluctuation() {
	// Random integer from -1500 to +1500
	int randomInteger = rand() % 3000 - 1500;

	// Convert to percentage
	float fluctuation = randomInteger / 100.00;

	// Multiply by 1.5 for higher crypto volatility
	return fluctuation = fluctuation * 1.5;
}

float applyMarketTrend(float baseFluctuation, int monthNumber) {
	float trend = 0.0;

	// Early investment period (1-6 months): Add small positive bias to encourage investors
	if (monthNumber <= 6) {
		trend = 0.3;
	}
	// Mid-term period (7-12 months): Neutral market, no adjustment
	else if (monthNumber <= 12) {
		trend = 0.0;
	}
	// Long-term period (13+ months): Historical market growth trend
	else {
		trend = 0.5;
	}

	return baseFluctuation + trend;
}