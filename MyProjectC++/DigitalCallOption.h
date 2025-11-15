#pragma once
#include <iostream>
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption
{
public:
	DigitalCallOption(double _expiry, double _strike);
	OptionType GetOptionType();
	double payoff(double);
};