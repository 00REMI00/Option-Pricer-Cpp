#pragma once

#include "AsianOption.h"

class AsianPutOption : public AsianOption
{
private:
	double strike;
public:
	AsianPutOption(std::vector<double>, double);
	double payoff(double);
	double payoffPath(std::vector<double>);
	OptionType GetOptionType();
};