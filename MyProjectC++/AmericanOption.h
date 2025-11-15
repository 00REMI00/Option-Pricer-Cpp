#pragma once
#include "Option.h"

class AmericanOption : public Option
{
private:
	double strike;
public:
	AmericanOption(double, double);
	bool isAmericanOption();
	//enum class OptionType { call, put };
	virtual OptionType GetOptionType() = 0;
	friend class AmericanCallOption;
	friend class AmericanPutOption;
};