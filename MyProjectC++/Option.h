#pragma once

#include <vector>

enum OptionType { call, put };
class Option 
{
private:
	double _expiry;
public:
	Option(double);
	double getExpiry();
	virtual double payoff(double _expiry) = 0;
	virtual double payoffPath(std::vector<double>);
	virtual bool isAsianOption();
	virtual std::vector<double> getTimeSteps();
	virtual bool isAmericanOption();
	virtual OptionType GetOptionType() = 0;
};