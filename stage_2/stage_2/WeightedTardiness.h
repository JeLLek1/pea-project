#pragma once
#include <vector>
#include "Job.h"

class ANeighborhood;
/*
	Klasa problemu szeregowania zadañ dla 
*/
class WeightedTardiness
{
private:
	// lista zadañ
	std::vector<Job*> jobs;
	// typ s¹siedztwa
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

