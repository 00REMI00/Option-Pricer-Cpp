#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesPricer.h"
#include "VanillaOption.h"
#include "DigitalOption.h"
#include "DigitalCallOption.h"
#include "DigitalPutOption.h"

using namespace std;


BlackScholesPricer::BlackScholesPricer(VanillaOption* option, double asset_price, double interest_rate, double volatility) : s{ asset_price }, r{ interest_rate }, sigma{ volatility }, o{ option }, od{nullptr} {}

BlackScholesPricer::BlackScholesPricer(DigitalOption* option, double asset_price, double interest_rate, double volatility) : s{ asset_price }, r{ interest_rate }, sigma{ volatility }, od{ option }, o{nullptr} {}


double BlackScholesPricer::norm_pdf(double x) 
{
	return exp(-0.5 * x * x) / pow(2 * M_PI, 0.5);
}

double BlackScholesPricer::norm_cdf(double x)
{
	return erfc(-x / sqrt(2))/2.;
}


double BlackScholesPricer::d1(double S, double K, double r, double sigma, double T)
{
	return (log(S / K) + (r + (sigma * sigma / 2)) * T) / (sigma * sqrt(T));
}

double BlackScholesPricer::d2(double S,double K,double r,double sigma,double T)
{
	return d1(S, K, r, sigma, T) - (sigma * sqrt(T));//pow(T, 0.5);
}


double BlackScholesPricer::operator()()
{
	double price = 0.0;
	if (o != nullptr) 
	{

		double dd1 = (log(s / o->_strike) + (r + (sigma * sigma / 2)) * o->getExpiry()) / (sigma * sqrt(o->getExpiry()));
		double dd2 = dd1 - (sigma * sqrt(o->getExpiry()));
		if (o->GetOptionType() == OptionType::call)
		{
			price = s * norm_cdf(d1(s, o->_strike, r, sigma, o->getExpiry())) - o->_strike * exp(-r * o->getExpiry()) * norm_cdf(d2(s, o->_strike, r, sigma, o->getExpiry()));
			
		}
		else if (o->GetOptionType() == OptionType::put)
		{
			price = o->_strike * exp(-r * o->getExpiry()) - s + (s * norm_cdf(d1(s, o->_strike, r, sigma, o->getExpiry())) - o->_strike * exp(-r * o->getExpiry()) * norm_cdf(d2(s, o->_strike, r, sigma, o->getExpiry())));
		}
		else
		{
			cout << "error" << endl;
		}
	}
	else if(od != nullptr)
	{
		if (od->GetOptionType() == OptionType::call)
		{
			price = exp(-r * od->getExpiry()) * norm_cdf(d2(s, od->_strike, r, sigma, od->getExpiry()));
		}
		else if (od->GetOptionType() == OptionType::put)
		{
			price = exp(-r * od->getExpiry()) * norm_cdf(-d2(s, od->_strike, r, sigma, od->getExpiry()));
		}
		else
		{
			cout << "error" << endl;
		}
	}
	else
	{
		cout << "error" << endl;
	}
	return price;
}

double BlackScholesPricer::delta()
{
	double d = 0.0;
	if (o != nullptr)
	{
		if (o->GetOptionType() == OptionType::call)
		{
			d = norm_cdf(d1(s, o->_strike, r, sigma, o->getExpiry()));

		}
		else if (o->GetOptionType() == OptionType::put)
		{
			d = norm_cdf(d1(s, o->_strike, r, sigma, o->getExpiry())) - 1;
		}
		else
		{
			cout << "error" << endl;
		}
	}
	else if (od != nullptr)
	{
		double x = (log(s / od->_strike) + (r + (sigma * sigma / 2)) * od->getExpiry()) / (sigma * sqrt(od->getExpiry())) - (sigma * sqrt(od->getExpiry()));
		if (od->GetOptionType() == OptionType::call)
		{
			d = (exp(-r * od->getExpiry()) / (od->_strike * sigma * sqrt(od->getExpiry())))* norm_pdf(x);
		}
		else if (od->GetOptionType() == OptionType::put)
		{
			d = -(exp(-r * od->getExpiry()) / (od->_strike * sigma * sqrt(od->getExpiry()))) * norm_pdf(x);
		}
		else
		{
			cout << "error" << endl;
		}
	}
	else
	{
		cout << "error" << endl;
	}
	return d;
}