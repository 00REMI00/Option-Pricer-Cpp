#include "AmericanOption.h"



AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), strike(strike) {}


bool AmericanOption::isAmericanOption()
{
	return true;
}


