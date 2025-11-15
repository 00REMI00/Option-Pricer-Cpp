#pragma once
#include "Option.h"

class DigitalOption : public Option
{
private:
	double _strike;
public:
	DigitalOption(double _expiry, double strike);
	//enum class OptionType { call, put };
	virtual OptionType GetOptionType() = 0;
	friend class BlackScholesPricer;
	friend class DigitalCallOption;
	friend class DigitalPutOption;
};
