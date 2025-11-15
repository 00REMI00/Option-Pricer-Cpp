#pragma once
#include "Option.h"
#include <vector>


class AsianOption : public Option
{
private:
	std::vector<double> t;
protected:
	double strike;
public:
	AsianOption(std::vector<double>);
	std::vector<double> getTimeSteps();
	double payoffPath(std::vector<double>);
	bool isAsianOption() override;
	virtual OptionType GetOptionType() = 0;
};