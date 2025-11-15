#pragma once
#include "VanillaOption.h"
#include "BinaryTree.h"

class CRRPricer {
private:
	double up;
	double down;
	double interest_rate; //r
	double asset_price;
	int depth;
	Option* option;
	BinaryTree<bool> exercise;
	BinaryTree<double> tree;
public:
	BinaryTree<double> stock_tree = BinaryTree<double>(depth);
	CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
	CRRPricer(Option*, int, double, double, double);
	void compute();
	double get(int, int);
	double operator()(bool=false);
	bool getExercise(int, int);
private:
	double stock_price(int,int);
	double facto(int);
	double risk_neutral();
};