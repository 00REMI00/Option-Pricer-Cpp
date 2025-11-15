#pragma once
#include <iostream>
//#include <vector>
#include "VanillaOption.h"

class PutOption : public VanillaOption
{
public:
	PutOption(double _expiry, double _strike);
	OptionType GetOptionType();
	double payoff(double);
};