#pragma once
#include <iostream>
#include "VanillaOption.h"

class CallOption : public VanillaOption 
{
public:
	CallOption(double _expiry, double _strike);
	OptionType GetOptionType();
	double payoff(double);
};