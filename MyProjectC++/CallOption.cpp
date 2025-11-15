#include "CallOption.h"
#include "VanillaOption.h"


CallOption::CallOption(double _expiry, double _strike) : VanillaOption(_expiry,_strike) {}

double CallOption::payoff(double z) 
{
	if (z >= _strike)
	{
		return z - _strike;
	}
	else {
		return 0.0;
	}
}


OptionType CallOption::GetOptionType() 
{
	return OptionType::call;
}

