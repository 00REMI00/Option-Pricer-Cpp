#include "AsianCallOption.h"

using namespace std;

AsianCallOption::AsianCallOption(vector<double> t, double strike) : AsianOption(t), strike{strike}{
	if (strike > 0) 
	{
		strike = strike;
	}
	else {
		strike = 0;
	}
}


double AsianCallOption::payoff(double s) {
	if (s >= strike) {
		return s - strike;
	}
	else {
		return 0;
	}
}

double AsianCallOption::payoffPath(vector<double> times)
{
	return payoff(AsianOption::payoffPath(times));
}
OptionType AsianCallOption::GetOptionType()
{
	return OptionType::put;
}
