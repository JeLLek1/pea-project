#pragma once
#include "WeightedTardiness.h"
#include <random>

//singleton
//generowanie losowych warto�ci dla problemu szeregowania zada�
class RandomGenerator
{
	//przedzia� wag zada�
	static const std::uniform_int_distribution<unsigned int> distWeight;
	//przedzia� czas�w wykonywania zada�
	static const std::uniform_int_distribution<unsigned int> distTime;
	//generator liczb losowych
	std::random_device *rd;
	//generator liczb pseudolosowych 32-bit Mersenne'a Twister'a
	std::mt19937 *gen;

	//instancja singletonu
	static RandomGenerator* instance;

	//prywanty konstruktor singletonu
	RandomGenerator();
public:
	//usuni�cie metod kt�re niszcz� singleton
	RandomGenerator(RandomGenerator& other) = delete;
	void operator=(const RandomGenerator&) = delete;

	//pobranie instancji singletonu
	static RandomGenerator* getInstance();

	//generowanie problemu szeregowania zada�
	WeightedTardiness* generateWeightedTardiness(unsigned int size);
};

