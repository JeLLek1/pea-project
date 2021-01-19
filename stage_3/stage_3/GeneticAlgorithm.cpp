#include "GeneticAlgorithm.h"
#include "RandomGenerator.h"
#include "App.h"

GeneticAlgorithm::GeneticAlgorithm(WeightedTardiness* problem)
{
    this->best = new JobsOrder();
    this->timeStart = std::chrono::high_resolution_clock::now();
    this->problem = problem;
    this->population = std::vector<std::pair<std::vector<size_t>*, unsigned int>>(problem->populationSize);

    // generowanie losowej populacji poczatkowej
    for(size_t i = 0; i< this->problem->populationSize; i++){
        this->population[i].first = problem->randomOrder();
        this->population[i].second = problem->getTotalWeightedLoos(this->population[i].first);
        if (this->population[i].second < this->best->totalLoos) {
            this->best->setOrder(this->population[i].first, this->population[i].second);
        }
    }
}

std::pair<std::vector<size_t>*, unsigned int> GeneticAlgorithm::PMX(
    std::pair<std::vector<size_t>*, unsigned int>& parentFirst, 
    std::pair<std::vector<size_t>*, unsigned int>& parentSecond,
    WeightedTardiness* problem)
{
    std::vector<size_t>* children = new std::vector<size_t>(problem->countJobs());
    size_t firstPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, problem->countJobs() - 2);
    size_t secondPoint = RandomGenerator::getInstance()->getRandom<size_t>(firstPoint + 1, problem->countJobs() - 1);

    // kopia danych pierwszego rodzica do dziecka
    std::copy(parentFirst.first->begin(), parentFirst.first->end(), children->begin());

    // wektor informacji o tym na którym indeksie
    // w children znajduje siê elemnt o nr i
    std::vector<size_t> indexInfo(problem->countJobs());
    for (size_t i = 0; i < problem->countJobs(); i++) {
        indexInfo[(*children)[i]] = i;
    }

    for (size_t i = firstPoint; i <= secondPoint; i++) {
        size_t jobIndex = (*parentSecond.first)[i];
        // zamiana nr zadania na pozycji i numerem zadania o wartosci jobIndex
        App::swap(children, i, indexInfo[jobIndex]);
        // uzupe³nienie informacji o zamianie w wektorze map
        App::swap(&indexInfo, (*children)[i], (*children)[indexInfo[jobIndex]]);
    }

    return std::pair<std::vector<size_t>*, unsigned int>(children, problem->getTotalWeightedLoos(children));
}

std::pair<std::vector<size_t>*, unsigned int> GeneticAlgorithm::OX(
    std::pair<std::vector<size_t>*, unsigned int>& parentFirst, 
    std::pair<std::vector<size_t>*, unsigned int>& parentSecond,
    WeightedTardiness* problem)
{

    std::vector<size_t>* children = new std::vector<size_t>(problem->countJobs());
    size_t firstPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, problem->countJobs() - 2);
    size_t secondPoint = RandomGenerator::getInstance()->getRandom<size_t>(firstPoint + 1, problem->countJobs() - 1);

    size_t parentFirstPos = firstPoint;

    // u¿yte ju¿ indeksy zadañ
   std::vector<bool> notUsed(problem->countJobs(), true);

    
    for(; parentFirstPos <=secondPoint; parentFirstPos++){
        (*children)[parentFirstPos] = (*parentSecond.first)[parentFirstPos];
        notUsed[(*parentSecond.first)[parentFirstPos]] = false;
    }
    // zaczecie od kolejnego indeksu
    secondPoint++;
    // skopiowanie wszystkich nieuzytych elementow z rodzica 1 az indeks rodzica nie przekroczy zakresu
    for (; parentFirstPos < problem->countJobs(); parentFirstPos++) {
        if (notUsed[(*parentFirst.first)[parentFirstPos]]) {
            (*children)[secondPoint] = (*parentFirst.first)[parentFirstPos];
            secondPoint++;
        }
    }
    parentFirstPos = 0;
    // skopiowanie wszystkich nieuzytych elementow z rodzica 1 az indeks dziecka nie przekroczy zakresu
    for (; secondPoint < problem->countJobs(); parentFirstPos++) {
        if (notUsed[(*parentFirst.first)[parentFirstPos]]) {
            (*children)[secondPoint] = (*parentFirst.first)[parentFirstPos];
            secondPoint++;
        }
    }
    secondPoint = 0;
    // skopiowanie pozosta³ych elementów z rodzica 1
    for (; secondPoint < firstPoint; parentFirstPos++) {
        if (notUsed[(*parentFirst.first)[parentFirstPos]]) {
            (*children)[secondPoint] = (*parentFirst.first)[parentFirstPos];
            secondPoint++;
        }
    }

    return std::pair<std::vector<size_t>*, unsigned int>(children, problem->getTotalWeightedLoos(children));
}

void GeneticAlgorithm::insertMutation(
    std::pair<std::vector<size_t>*, unsigned int>& specimen,
    WeightedTardiness* problem)
{
    size_t firstPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, problem->countJobs() - 1);
    size_t secondPoint = firstPoint;
    while (secondPoint == firstPoint){
        secondPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, problem->countJobs() - 1);
    }
    std::vector<size_t>* tmp = new std::vector<size_t>(problem->countJobs());

    // kopiowanie odpowiednio pocz¹tku z tymi samymi indeksami, przesuniêtego œrodka oraz koñca z tymi samymi indeksami
    if (firstPoint < secondPoint) {
        std::copy(specimen.first->begin(), specimen.first->begin() + firstPoint, tmp->begin());
        std::copy(specimen.first->begin() + firstPoint + 1, specimen.first->begin() + secondPoint + 1, tmp->begin() + firstPoint);
        std::copy(specimen.first->begin() + secondPoint + 1, specimen.first->begin() + specimen.first->size(), tmp->begin() + secondPoint + 1);
    }
    else {
        std::copy(specimen.first->begin(), specimen.first->begin() + secondPoint, tmp->begin());
        std::copy(specimen.first->begin() + secondPoint, specimen.first->begin() + firstPoint, tmp->begin() + secondPoint + 1);
        std::copy(specimen.first->begin() + firstPoint + 1, specimen.first->begin() + specimen.first->size(), tmp->begin() + firstPoint + 1);
    }
    // skopiowanie elementu przenoszonego
    (*tmp)[secondPoint] = (*specimen.first)[firstPoint];

    delete specimen.first;
    specimen.first = tmp;
    specimen.second = problem->getTotalWeightedLoos(specimen.first);
}

void GeneticAlgorithm::transpositionMutation(
    std::pair<std::vector<size_t>*, unsigned int>& specimen,
    WeightedTardiness* problem)
{
    size_t firstPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, problem->countJobs() - 2);
    size_t secondPoint = RandomGenerator::getInstance()->getRandom<size_t>(firstPoint, problem->countJobs() - 1);

    // prosta zamiana wartoœci
    App::swap(specimen.first, firstPoint, secondPoint);

    specimen.second = problem->getTotalWeightedLoos(specimen.first);
}

void GeneticAlgorithm::generatePopulation()
{
    std::vector<std::pair<std::vector<size_t>*, unsigned int>> newPopulation(this->problem->populationSize);
    // indeksy rodziców
    std::vector<size_t> parents(this->problem->populationSize);
    // selekcja turniejowa rodziców
    for (size_t i = 0; i < this->problem->populationSize; i++) {
        // losowanie indeksów do turnieju
        size_t firstPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, this->problem->populationSize - 1);
        size_t secondPoint = firstPoint;
        while (secondPoint == firstPoint) {
            secondPoint = RandomGenerator::getInstance()->getRandom<size_t>(0, this->problem->populationSize - 1);
        }
        parents[i] = (this->population[firstPoint].second < this->population[secondPoint].second) ?
            firstPoint : secondPoint;
    }
    // tworzenie nowej populacji
    for (size_t i = 0; i < this->problem->populationSize / 2; i++) {
        // prawdopodobienstwo krzyzowania
        float croosRand = RandomGenerator::getInstance()->getRandomFloat(0.f, 1.f);
        if (croosRand <= this->problem->crossoverRatio) {
            newPopulation[2 * i] = this->problem->crossFunction(this->population[parents[2 * i]], this->population[parents[2 * i + 1]], this->problem);
            newPopulation[2 * i + 1] = this->problem->crossFunction(this->population[parents[2 * i + 1]], this->population[parents[2 * i]], this->problem);
        } else {
            newPopulation[2 * i].first = new std::vector<size_t>(*this->population[parents[2 * i]].first);
            newPopulation[2 * i].second = this->population[parents[2 * i]].second;

            newPopulation[2 * i + 1].first = new std::vector<size_t>(*this->population[parents[2 * i + 1]].first);
            newPopulation[2 * i + 1].second = this->population[parents[2 * i + 1]].second;
        }
    }
    // mutacje nowych elementów
    for (size_t i = 0; i < this->problem->populationSize; i++) {
        // prawdopodobienstwo mutacji
        float mutRand = RandomGenerator::getInstance()->getRandomFloat(0.f, 1.f);
        if (mutRand <= this->problem->mutationRatio) {
            // sprawdzenie przed mutacj¹ czy nie by³o lepszym rozwi¹zaniem
            if (this->best->totalLoos > newPopulation[i].second) {
                this->best->setOrder(newPopulation[i].first, newPopulation[i].second);
            }
            // mutacja
            this->problem->mutationFunction(newPopulation[i], this->problem);
        }
    }

    this->clearPopulation();
    this->population = newPopulation;
}

void GeneticAlgorithm::clearPopulation()
{
    for (auto element : this->population) {
        delete element.first;
    }
}

void GeneticAlgorithm::runAlgorithm()
{
    std::chrono::high_resolution_clock::time_point timeNow;
    do {
        // generowanie nowej populacji
        this->generatePopulation();
        // sprawdzenie czy poprawa
        for (size_t i = 0; i < this->problem->populationSize; i++) {
            if (this->population[i].second < this->best->totalLoos) {
                this->best->setOrder(this->population[i].first, this->population[i].second);
            }
        }

        timeNow = std::chrono::high_resolution_clock::now();
    } while (std::chrono::duration_cast<std::chrono::seconds>(timeNow - this->timeStart).count() < this->problem->stopSeconds);
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    delete this->best;
    this->clearPopulation();
}
