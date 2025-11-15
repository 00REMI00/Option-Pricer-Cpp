#pragma once
#include "VanillaOption.h"
#include "DigitalOption.h"

class BlackScholesPricer //: public VanillaOption
{
private:
	double s;
	double r;
	double sigma;
	VanillaOption* o;
	DigitalOption* od;
public:
	BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility);
	BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility);
	double operator()();
	double delta();
private:
	double norm_pdf(double x);
	double norm_cdf(double x);
	double d1(double S,double K, double r, double sigma, double T);
	double d2(double S,double K, double r, double sigma, double T);
};