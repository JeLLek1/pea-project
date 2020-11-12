#pragma once
#include "WeightedTardiness.h"
#include <random>

//singleton
class RandomGenerator
{
	static const std::uniform_int_distribution<unsigned int> distWeight;
	static const std::uniform_int_distribution<unsigned int> distTime;
	std::random_device *rd;
	std::mt19937 *gen;

	static RandomGenerator* instance;

	RandomGenerator();
public:
	//usuniêcie metod które niszcz¹ singleton
	RandomGenerator(RandomGenerator& other) = delete;
	void operator=(const RandomGenerator&) = delete;

	static RandomGenerator* getInstance();

	WeightedTardiness* generateWeightedTardiness(unsigned int size);
	float generateFloat(float min, float max);
};

