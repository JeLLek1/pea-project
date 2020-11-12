#include "RandomGenerator.h"
#include <vector>
#include <iostream>
//przedzia³ wag zadañ
const std::uniform_int_distribution<unsigned int> RandomGenerator::distWeight = std::uniform_int_distribution<unsigned int>(1,10);
//przedzia³ czasów wykonywania zadañ
const std::uniform_int_distribution<unsigned int> RandomGenerator::distTime = std::uniform_int_distribution<unsigned int>(1, 100);

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
//generowanie problemu szeregowania zadañ
WeightedTardiness* RandomGenerator::generateWeightedTardiness(unsigned int size)
{
    //lista wygenerowanych czasów przetwarzania
    std::vector<unsigned int> processingTimes;
    unsigned int ptSums = 0;
    unsigned int ptMax = 0;
    //generowanie i sumowanie kolejnych czasów przetwarzania
    for (size_t i = 0; i < size; i++) {
        unsigned int ptTmp = RandomGenerator::distTime(*this->gen);
        processingTimes.push_back(ptTmp);
        ptSums += ptTmp;
        if (ptTmp > ptMax) ptMax = ptTmp;
    }
    //instancja problemu szeregowania zadañ
    WeightedTardiness* problem = new WeightedTardiness();
    //generowanie kolejnych zadañ
    for (size_t i = 0; i < size; i++) {
        //przedzia³ maksymalnego czasu przetwarzania
        std::uniform_int_distribution<unsigned int> dist(ptMax, ptSums);
        //tworzenie zadania i dodawanie do listy
        problem->pushJob(new Job(i+1, processingTimes[i], dist(*this->gen), RandomGenerator::distWeight(*this->gen)));
    }

    return problem;
}
