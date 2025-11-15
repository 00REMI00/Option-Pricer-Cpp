#include "AsianOption.h"
#include <vector>

using namespace std;


AsianOption::AsianOption(vector<double> time) : Option(time[time.size() - 1]) ,t{time} {}

vector<double> AsianOption::getTimeSteps() 
{
	return t;
}


bool AsianOption::isAsianOption() {

	return true;
}

double AsianOption::payoffPath(vector<double> times)
{
	double res = 0.0;
	for (int i = 0;i < times.size();i++)
	{
		res += times[i];
	}

	return res / times.size();
}