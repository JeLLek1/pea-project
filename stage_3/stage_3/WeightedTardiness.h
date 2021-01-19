#pragma once
#include <vector>
#include "Job.h"

class GeneticAlgorithm;

class ANeighborhood;
/*
	Klasa problemu szeregowania zada� dla 
*/
class WeightedTardiness
{
private:
	// lista zada�
	std::vector<Job*> jobs;
public:
	// Kryterium stopu w sekundach
	unsigned int stopSeconds = 10;
	// wielko�� populacji pocz�tkowej >=2
	unsigned int populationSize = 100;
	// wsp�czynnik mutacji <= 1
	float mutationRatio = 0.1f;
	// wsp�czynnik krzy�owania <= 1
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
	// dodanie zadania do listy zada�
	void pushJob(Job* job);
	// zwr�cenie ilo�ci zada� dla innych klas
	size_t countJobs();
	// wy�wietlanie struktury
	void display();
	// pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	// obliczanie ca�kowitej straty dla podanej kolejno�ci zada�
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	// generowanie losowej kolejno�ci
	std::vector<size_t>* randomOrder();
	// czyszczenie struktury
	void erease();
	// destruktor
	~WeightedTardiness();
};

