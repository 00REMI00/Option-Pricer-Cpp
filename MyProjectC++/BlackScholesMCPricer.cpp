#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <iostream>
using namespace std;

BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : o(option), S0(initial_price), r(interest_rate), vol(volatility), NbPaths(0), estimates_price(-1) {};

int BlackScholesMCPricer::getNbPaths() const {
	if (NbPaths == 0)
	{
		throw invalid_argument("No Path generated yet.");
	}
	else
	{
		return NbPaths;
	}
}

void BlackScholesMCPricer::generate(int nb_paths) {

	double payoffs = 0;
	double spotT = 0;
	double rand = 0;
	vector<double> spotPaths;
	for (int i = 0; i < nb_paths; i++) {
		spotPaths.push_back(S0);
		if (o->isAsianOption() == false)
		{
			double expiry = o->getExpiry();
			spotT = S0 * exp(((r - ((vol * vol) / 2)) * expiry) + (vol * sqrt(expiry)) * MT::rand_norm());
			spotPaths.push_back(spotT);
		}
		else
		{
		
			double temp = o->getExpiry()/o->getTimeSteps().size();
			for (int j = 1; j < o->getTimeSteps().size() +1; j++) {
				rand = MT::rand_norm();
				spotT = spotPaths[j-1] * exp((r - (vol * vol) / 2) * (temp) + vol * sqrt(temp) * rand);
				spotPaths.push_back(spotT);
			}
		}
		payoffs = o->payoffPath(spotPaths) + payoffs;
		spotPaths.clear();
	}

	double result = exp(-r * o->getExpiry()) * (1 / double(nb_paths)) * payoffs;
	estimates_price = (estimates_price * NbPaths + result*nb_paths) / double(NbPaths + nb_paths);
	NbPaths += nb_paths;
}

// Renvoie la dernière estimation
double BlackScholesMCPricer::operator()() {
	try {
		if (NbPaths == 0) {
			throw string("The Monte Carlo function has never been called before.");
		}
		return estimates_price;
	}
	catch (const std::string& error) {
		cerr << error << endl;
		return 0.0;
	}
}

// renvoie l'intervalle de confiance du prix à un niveau de 95%
std::vector<double> BlackScholesMCPricer::confidenceInterval() {
	
	return { estimates_price - 1.96 * (vol/sqrt(double(NbPaths))), estimates_price+ 1.96*(vol/sqrt(double(NbPaths)))};
}