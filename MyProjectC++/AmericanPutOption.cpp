#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption(double strike, double expiry) : AmericanOption(strike, expiry) {}

double AmericanPutOption::payoff(double s) {
	if (s <= strike) {
		return strike - s;
	}
	else {
		return 0;
	}
}

OptionType AmericanPutOption::GetOptionType() {
	return OptionType::put;
}