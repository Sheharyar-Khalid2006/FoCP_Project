#include "validation.h"
#include <limits>
#include <iostream>


int getintinput() {
	int i;
	while (true) {
		std::cin >> i;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			continue;
		}
		return i;
	 }
}

float getfloatinput() {
	float f;
	while (true) {
		std::cin >> f;
		
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		return f;
	}
}

bool amount_validation(float amount) {
	if (amount < 0) {
		std::cout << "Amount cannot be negative.(At least not in this game)\n";
		return false;

	}
	else if (amount == 0) {
		std::cout << "0 dollars!! come on, you have to invest something, otherwise how will you learn.\n";
		return false;
	}
	else if (amount > 1000000) {
		std::cout << "You don't have that much money.";
		return false;
	}
	return true;
}


bool month_check(int months) {
	if (months > 36) {
		std::cout << "\nWe can only handle 3 years of your monthly investments.\n";
		return false;
	}
	else if (months < 0) {
		std::cout << "\nWe cant go back in time to invest.Now, Can we?\n";
		return false;
	}

	return true;
}

bool check_loss_threshold(float threshold) {
	if (threshold > 100) {
		std::cout << "\nSafe loss threshold cannot be greater than 100%.\n";
		return false;
	}
	else if (threshold < 20) {
		std::cout << "\nRemember there is no business without loss.\n Least loss threshold is 20%.\n";
		return false;
	}
	return true;
}

