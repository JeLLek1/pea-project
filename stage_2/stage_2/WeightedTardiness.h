#pragma once
#include <vector>
#include "Job.h"

class ANeighborhood;
/*
	Klasa problemu szeregowania zada� dla 
*/
class WeightedTardiness
{
private:
	// lista zada�
	std::vector<Job*> jobs;
	// typ s�siedztwa
	ANeighborhood* neighborhood;
	// dywersyfikacja
	bool diversification;
	// Kryterium stopu w sekundach
	unsigned int stopSeconds;
public:
	WeightedTardiness();
	// get/set
	ANeighborhood* getNeighborhood();
	void setNeighborhood(ANeighborhood* newigborhood);
	bool getDiversification();
	void setDiversification(bool diversyfication);
	unsigned int getStopSeconds();
	void setStopSeconds(unsigned int seconds);
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

