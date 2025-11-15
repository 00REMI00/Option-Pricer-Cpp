#include "MT.h"
#include <random>
#include <iostream>

MT::MT() {
	std::random_device rd;
	std::mt19937 gen(rd());
	MT_generator = gen;
}




MT& MT::getInstance() {
	static std::unique_ptr<MT> instance(new MT());
	return *instance;
}


double MT::rand_unif() {
	std::uniform_real_distribution<double> uniform_pdf(0.0, 1.0);
	return uniform_pdf(getInstance().MT_generator);
}

double MT::rand_norm() {
	std::normal_distribution<> gaussian_pdf(0.0, 1.0);
	return gaussian_pdf(getInstance().MT_generator);
}