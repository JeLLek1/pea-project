#pragma once
#include "WeightedTardiness.h"
#include <random>

//singleton
//generowanie losowych wartoœci dla problemu szeregowania zadañ
class RandomGenerator
{
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

	double getRandomDouble(double min, double max);

	template< class IntType = int >
	IntType getRandom(IntType min, IntType max);
};

template<class IntType>
inline IntType RandomGenerator::getRandom(IntType min, IntType max)
{
	std::uniform_int_distribution<IntType> distrib(min, max);

	return distrib(*this->gen);
}
