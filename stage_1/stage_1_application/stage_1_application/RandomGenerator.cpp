#include "RandomGenerator.h"
#include <vector>
#include <iostream>
const std::uniform_int_distribution<unsigned int> RandomGenerator::distWeight = std::uniform_int_distribution<unsigned int>(1,10);
const std::uniform_int_distribution<unsigned int> RandomGenerator::distTime = std::uniform_int_distribution<unsigned int>(1, 100);

RandomGenerator* RandomGenerator::instance = nullptr;

RandomGenerator::RandomGenerator() {
    this->rd = new std::random_device();
    this->gen = new std::mt19937((*this->rd)());
}

RandomGenerator* RandomGenerator::getInstance()
{
    if (RandomGenerator::instance == nullptr) {
        RandomGenerator::instance = new RandomGenerator();
    }
    return RandomGenerator::instance;
}

WeightedTardiness* RandomGenerator::generateWeightedTardiness(unsigned int size)
{
    std::vector<unsigned int> processingTimes;
    unsigned int ptSums = 0;
    unsigned int ptMax = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned int ptTmp = RandomGenerator::distTime(*this->gen);
        processingTimes.push_back(ptTmp);
        ptSums += ptTmp;
        if (ptTmp > ptMax) ptMax = ptTmp;
    }

    WeightedTardiness* problem = new WeightedTardiness();

    for (size_t i = 0; i < size; i++) {
        std::uniform_int_distribution<unsigned int> dist(ptMax, ptSums);
        problem->pushJob(new Job(i+1, processingTimes[i], dist(*this->gen), RandomGenerator::distWeight(*this->gen)));
    }

    return problem;
}

float RandomGenerator::generateFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(*this->gen);
}
