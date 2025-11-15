#include "DigitalCallOption.h"
#include "DigitalOption.h"


DigitalCallOption::DigitalCallOption(double _expiry, double _strike) : DigitalOption(_expiry, _strike) {}

double DigitalCallOption::payoff(double z)
{
	if (z >= _strike)
	{
		return 1.;
	}
	else {
		return 0.0;
	}
}


OptionType DigitalCallOption::GetOptionType()
{
	return OptionType::call;
}
