#pragma once
#include <iostream>
#include "DigitalOption.h"

class DigitalPutOption : public DigitalOption
{
public:
	DigitalPutOption(double _expiry ,double _strike);
	OptionType GetOptionType();
	double payoff(double);
};