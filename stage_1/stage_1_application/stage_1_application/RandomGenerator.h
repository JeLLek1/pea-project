#pragma once
#include "WeightedTardiness.h"
#include <random>

//singleton
//generowanie losowych wartoœci dla problemu szeregowania zadañ
class RandomGenerator
{
	//przedzia³ wag zadañ
	static const std::uniform_int_distribution<unsigned int> distWeight;
	//przedzia³ czasów wykonywania zadañ
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
	//usuniêcie metod które niszcz¹ singleton
	RandomGenerator(RandomGenerator& other) = delete;
	void operator=(const RandomGenerator&) = delete;

	//pobranie instancji singletonu
	static RandomGenerator* getInstance();

	//generowanie problemu szeregowania zadañ
	WeightedTardiness* generateWeightedTardiness(unsigned int size);
};

