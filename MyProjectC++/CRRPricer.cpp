#include "CRRPricer.h"
#include <iostream>
#include "VanillaOption.h"
#include "BinaryTree.h"
#include <math.h>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) 
{
	if (option->isAsianOption()) { 
		throw std::invalid_argument("Error : The option is an Asian Option");
	}
	this->option = option;
	this->depth = depth;
	this->asset_price = asset_price;
	this->up = up;
	this->down = down;
	this->interest_rate = interest_rate;
	stock_tree.setDepth(depth);

	if (this->down < this->interest_rate && this->interest_rate < this->up) 
	{
		cout << "The model admits no arbitrage\n" << endl;
	}
	else {
		cout << "The model admits arbitrage\n" << endl;
	}
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
	:option(option), depth(depth), asset_price(asset_price)
{
	double h = option->getExpiry() / depth;
	if (option->isAsianOption() == false)
	{
		up = exp((r + (pow(volatility, 2) / 2)) * h + volatility * sqrt(h)) - 1;
		down = exp((r + (pow(volatility, 2) / 2)) * h - volatility * sqrt(h)) - 1;
		interest_rate = exp(r * h) - 1;
		if (down < interest_rate && interest_rate < up) {
			tree = BinaryTree<double>(depth);
			exercise = BinaryTree<bool>(depth);
		}
		else
			throw invalid_argument("Error : There is an arbitrage");
	}
	else
	{
		throw invalid_argument("It is an Asian Option");
	}
}

void CRRPricer::compute() 
{
	double m = 0;
	double mInter = 0;
	double q = (interest_rate - down) / (up - down);
	double res = 0;
	for (int n = depth;n >=0;n--) 
	{
		for (int i = 0;i <= n;i++)
		{
			if (n == depth)
			{
				stock_tree.setNode(n, i, option->payoff(stock_price(n, i)));
			}
			else 
			{
				if (option->isAmericanOption()) {
					m = option->payoff(stock_price(n, i));
					mInter = (q * stock_tree.getNode(n + 1, i + 1) + (1 - q) * stock_tree.getNode(n + 1, i) / (1 + interest_rate));
					res = std::max(m, mInter);
					exercise.setNode(n, i, ((m >= mInter) ? true : false));
				}
				else {
					res = (q * stock_tree.getNode(n + 1, i + 1) + (1 - q) * stock_tree.getNode(n + 1, i)) / (1 + interest_rate);
				}
				stock_tree.setNode(n, i, res);
			}
		}
	}
}

double CRRPricer::get(int n, int i)
{
	if (n == depth)
	{
		return option->payoff(stock_price(n,i));
	}
	else {
		return (risk_neutral() *get(n+1,i+1) + (1 - risk_neutral()) * get(n+1,i)) / (1 + interest_rate);
	}
}

double CRRPricer::stock_price(int n, int i) 
{
	return asset_price * pow(1 + up,i) * pow(1 + down,n - i);

}

double CRRPricer::operator()(bool istrue) 
{
	double res = 0.0;
	if (istrue == false)
	{
		compute();
		return stock_tree.getNode(0,0);
	}
	else 
	{
		for (int i = 0;i <= depth;i++)
		{
			res += (facto(depth) / (facto(i) * facto(depth - i)))*pow(risk_neutral(),i)*pow(1-risk_neutral(),depth-i)*get(depth,i);
		}
		return res / pow(1 + interest_rate, depth);
	}
}

double CRRPricer::facto(int n)//depth 
{
	double res = 1.;
	if (n == 0) 
	{
		return res;
	}
	else 
	{
		for (int i = 1;i <= n;i++)
		{
			res *= i;
		}
		return res;
	}
}

double CRRPricer::risk_neutral() 
{
	return (interest_rate - down) / (up - down);
}

bool CRRPricer::getExercise(int n, int i) {
	double _risk_neutral_probability = (interest_rate - down) / (up - down);
	double continuation_value = 0;
	double intrinsic_value = 0;
	std::vector<std::vector<double>> tableauFinalH;
	bool res = false;
#pragma region arbre de tous les payoffs
	for (int k = n; k >= 0; k--) {
		std::vector<double> tableauInterH;

		if (k == n) {
			for (int i = 0; i <= k; i++) {
				double h = get(k, i);
				tableauInterH.push_back(h);
			}
		}
		else {
			for (int i = 0; i <= k; i++) {
				double h = (_risk_neutral_probability * tableauFinalH[n - (k + 1)][i + 1] + (1 - _risk_neutral_probability) * tableauFinalH[n - (k + 1)][i]) / (1 + interest_rate);
				tableauInterH.push_back(h);
			}

		}
		tableauFinalH.push_back(tableauInterH);
	}
	std::reverse(tableauFinalH.begin(), tableauFinalH.end());
#pragma endregion
	continuation_value = tableauFinalH[-1][-1];
	for (int k = 0; k < depth; k++) {
		for (int j = 0; j < k + 1; j++) {
			intrinsic_value = get(n, i);
			if (intrinsic_value <= continuation_value) {
				tree.setNode(k, j, false);
			}
			else {
				tree.setNode(k, j, true);
			}
		}
	}
	res = exercise.getNode(n, i);
	return res;

}