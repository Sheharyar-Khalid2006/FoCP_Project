#include"market.h"
#include<cstdlib>
#include<ctime>
#include<random>
#include<string>
#include <iostream>
#include<iomanip>


float generateMarketFluctuation(int marketType) {
    std::random_device rd;
    std::mt19937 gen(rd());

    float fluctuation = 0.0;

    switch (marketType) {
    case STABLE: {
        // Stable market: -2% to +2%
        std::uniform_real_distribution<float> dis(-2.0, 2.0);
        fluctuation = dis(gen);
        break;
    }

    case VOLATILE: {
        // Volatile market: -5% to +5%
        std::uniform_real_distribution<float> dis(-5.0, 5.0);
        fluctuation = dis(gen);
        break;
    }

    case BULLISH: {
        // Bullish market: -1% to +6% (bias towards positive)
        std::uniform_real_distribution<float> dis(-1.0, 6.0);
        fluctuation = dis(gen);
        break;
    }

    case BEARISH: {
        // Bearish market: -6% to +1% (bias towards negative)
        std::uniform_real_distribution<float> dis(-6.0, 1.0);
        fluctuation = dis(gen);
        break;
    }

    case CRISIS: {
        // Crisis market: -10% to +10% (extreme volatility)
        std::uniform_real_distribution<float> dis(-10.0, 10.0);
        fluctuation = dis(gen);
        break;
    }

    default: {
        std::uniform_real_distribution<float> dis(-2.0, 2.0);
        fluctuation = dis(gen);
        break;
    }
    }

    return fluctuation;
}

/*float getStockFluctuation() {
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
}*/

void displayMarketEvent(int marketType, float fluctuation) {
    if (abs(fluctuation) < 1.0f) return; // Don't show minor fluctuations

    std::cout << "Fluctuation";

    if (fluctuation > 5.0f) {
        std::cout << "Major rally! Market surged " << std::fixed << std::setprecision(2) << fluctuation << "%";
    }
    else if (fluctuation > 3.0f) {
        std::cout << "Strong gains! Market up " << std::fixed << std::setprecision(2) << fluctuation << "%";
    }
    else if (fluctuation > 1.0f) {
        std::cout << "Modest growth, market up " << std::fixed <<std:: setprecision(2) << fluctuation << "%";
    }
    else if (fluctuation < -5.0f) {
        std::cout << "Market crash! Down " << std::fixed << std::setprecision(2) << abs(fluctuation) << "%";
    }
    else if (fluctuation < -3.0f) {
        std::cout << "Sharp decline! Down " << std::fixed << std::setprecision(2) << abs(fluctuation) << "%";
    }
    else if (fluctuation < -1.0f) {
        std::cout << "Market dip, down " << std::fixed << std::setprecision(2) << abs(fluctuation) << "%";
    }

    std::cout << "\n";
}


std::string getMarketTypeName(int marketType) {
    switch (marketType) {
    case STABLE: return "Stable";
    case VOLATILE: return "Volatile";
    case BULLISH: return "Bullish";
    case BEARISH: return "Bearish";
    case CRISIS: return "Crisis";
    default: return "Unknown";
    }
}