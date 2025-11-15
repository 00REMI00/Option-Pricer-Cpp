#include "AsianPutOption.h"

using namespace std;

AsianPutOption::AsianPutOption(vector<double> time, double strike) : AsianOption(time), strike{strike}{
	if (strike > 0)
	{
		strike = strike;
	}
	else {
		strike = 0;
	}
}


double AsianPutOption::payoff(double s) {
	if (s <= strike) {
		return strike - s;
	}
	else {
		return 0;
	}
}

double AsianPutOption::payoffPath(vector<double> times)
{
	return payoff(AsianOption::payoffPath(times));
}

OptionType AsianPutOption::GetOptionType()
{
	return OptionType::put;
}
