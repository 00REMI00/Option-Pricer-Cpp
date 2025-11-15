#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption
{
public:
	AmericanCallOption(double , double );
	OptionType GetOptionType() ;
	double payoff(double prix);
};