#include "PutOption.h"
#include "VanillaOption.h"
//#include <vector>

PutOption::PutOption(double _expiry, double _strike) : VanillaOption(_expiry, _strike) {}

double PutOption::payoff(double z)
{
	if (z <= _strike)
	{
		return _strike-z;
	}
	else {
		return 0.0;
	}
}


OptionType PutOption::GetOptionType()
{
	return OptionType::put;
}


/*
double PutOption::payoffPath(std::vector<double> v)
{
	double h = 0.0;
	double temp = 0.0;
	for (int k = 0;k < v.size();k++)
	{
		temp += v[k];
	}
	return ((temp / v.size()) - getExpiry());
}*/