#pragma once
#include "Option.h"


class VanillaOption : public Option
{
private:
	double _strike;
public:
	VanillaOption(double _expiry, double strike);	
	//enum class OptionType {call,put};
	virtual OptionType GetOptionType() = 0;
	friend class BlackScholesPricer;
	friend class CallOption;
	friend class PutOption;
};
