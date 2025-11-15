#pragma once
#include "Option.h"
#include "MT.h"


class BlackScholesMCPricer 
{
private:
	int NbPaths = 0; //count the nb of path
	double S0; //initial price
	double r; //interest rateNbPaths
	double vol; //volatility
	Option* o;
	double estimates_price;
	//std::vector<double> estimated_prices;
public:
	BlackScholesMCPricer(Option*, double, double, double);
	int getNbPaths() const;
	void generate(int nb_paths);
	double operator()();
	std::vector<double> confidenceInterval();
};