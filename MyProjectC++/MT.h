#pragma once
#include <random>

class MT
{

private:
	MT();
	std::mt19937 MT_generator;
	//static MT *instance;
public:
	static MT& getInstance();
	//std::mt19937 get_MT();
	MT(const MT&) = delete;
	MT& operator=(const MT&) = delete;
	static double rand_unif();
	static double rand_norm();
};

