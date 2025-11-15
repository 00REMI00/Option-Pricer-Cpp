#include "DigitalPutOption.h"
#include "DigitalOption.h"


DigitalPutOption::DigitalPutOption(double _expiry, double _strike) : DigitalOption(_expiry, _strike) {}

double DigitalPutOption::payoff(double z)
{
	if (z <= _strike)
	{
		return 1.;
	}
	else {
		return 0.0;
	}
}


OptionType DigitalPutOption::GetOptionType()
{
	return OptionType::put;
}
