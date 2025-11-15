#include "Option.h"
#include <vector>

using namespace std;


Option::Option(double _expiry) : _expiry{ _expiry } {}

double Option::getExpiry() { return _expiry; }

double Option::payoffPath(vector<double> v) 
{
	return payoff(v[v.size() - 1]);
}

bool Option::isAsianOption() 
{
	return false;
}

vector<double> Option::getTimeSteps()
{
	vector<double> timesteps{ 0, _expiry };
	return timesteps;
}

bool Option::isAmericanOption()
{
	return false;
}