#include "AmericanCallOption.h"
#include "AmericanOption.h"

AmericanCallOption::AmericanCallOption(double strike, double expiry) : AmericanOption(strike, expiry) {}

double AmericanCallOption::payoff(double s) {
	if (s >= strike) {
		return s - strike;
	}
	else {
		return 0;
	}
}

OptionType AmericanCallOption::GetOptionType() {
	return OptionType::call;
}