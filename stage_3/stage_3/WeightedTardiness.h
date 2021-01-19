#pragma once
#include <vector>
#include "Job.h"

class GeneticAlgorithm;

class ANeighborhood;
/*
	Klasa problemu szeregowania zadañ dla 
*/
class WeightedTardiness
{
private:
	// lista zadañ
	std::vector<Job*> jobs;
public:
	// Kryterium stopu w sekundach
	unsigned int stopSeconds = 10;
	// wielkoœæ populacji pocz¹tkowej >=2
	unsigned int populationSize = 100;
	// wspó³czynnik mutacji <= 1
	float mutationRatio = 0.1f;
	// wspó³czynnik krzy¿owania <= 1
	float crossoverRatio = 0.7f;
	// funkcja mutacji
	void (*mutationFunction)(
		std::pair<std::vector<size_t>*, unsigned int>& specimen,
		WeightedTardiness* problem);
	// funkcja krzyzowania
	std::pair<std::vector<size_t>*, unsigned int>(*crossFunction)(
		std::pair<std::vector<size_t>*, unsigned int>& parentFirst,
		std::pair<std::vector<size_t>*, unsigned int>& parentSecond,
		WeightedTardiness* problem);

	WeightedTardiness();
	// dodanie zadania do listy zadañ
	void pushJob(Job* job);
	// zwrócenie iloœci zadañ dla innych klas
	size_t countJobs();
	// wyœwietlanie struktury
	void display();
	// pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	// obliczanie ca³kowitej straty dla podanej kolejnoœci zadañ
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	// generowanie losowej kolejnoœci
	std::vector<size_t>* randomOrder();
	// czyszczenie struktury
	void erease();
	// destruktor
	~WeightedTardiness();
};

