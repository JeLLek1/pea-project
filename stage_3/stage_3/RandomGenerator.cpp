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

float RandomGenerator::getRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(*this->gen);
}


