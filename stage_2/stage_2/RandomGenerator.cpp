#include "RandomGenerator.h"
#include <vector>
#include <iostream>

////instancja singletonu
RandomGenerator* RandomGenerator::instance = nullptr;

RandomGenerator::RandomGenerator() {
    //tworzenie instancji generatorów losowych
    this->rd = new std::random_device();
    this->gen = new std::mt19937((*this->rd)());
}
//pobranie instancji singletonu
RandomGenerator* RandomGenerator::getInstance()
{
    if (RandomGenerator::instance == nullptr) {
        RandomGenerator::instance = new RandomGenerator();
    }
    return RandomGenerator::instance;
}

double RandomGenerator::getRandomDouble(double min, double max)
{
    std::uniform_real_distribution<double> distrib(min, max);
    return distrib(*this->gen);
}


