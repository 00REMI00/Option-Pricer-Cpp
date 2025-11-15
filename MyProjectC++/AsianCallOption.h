#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption
{
private:
	double strike;
public:
	AsianCallOption(std::vector<double>,double);
	double payoff(double);
	double payoffPath(std::vector<double>);
	OptionType GetOptionType();
};