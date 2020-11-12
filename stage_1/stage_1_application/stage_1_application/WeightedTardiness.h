#pragma once
#include <vector>
#include "Job.h"
#include "JobsOrder.h"
#include "DbSubset.h"
/*
Klasa problemu szeregowania zadañ dla 
*/
class WeightedTardiness
{
private:
	//lista zadañ
	std::vector<Job*> jobs;

	//algorytm heapa generowania wszystkich permutacji
	void bruteforceGenerate(size_t size, std::vector<size_t>* order, JobsOrder* best);
	//subSets - przechowuje informacje o podzbiorach i indeksach zadañ takie jak minimalna kara, ca³kowity czas przetwarzania i informacjê o poprzedniku
	//jobIndexes - dla u³atwienia odtwarzania zapisywane s¹ indeksy i podzbiory poprzedników
	//subsetSize - wielkoœæ podzbioru, start - startowy bit, end - koñcowy bit, index - obecny poziom rekurencji, mask - obliczona maska
	void dpSubsets(
		std::vector<std::vector<DbSubset>>& subSets,
		size_t subsetSize, size_t end, size_t start = 0, size_t index = 0, size_t mask=0
	);
public:

	//dodanie zadania do listy zadañ
	void pushJob(Job* job);
	//zwrócenie iloœci zadañ dla innych klas
	size_t countJobs();
	//wyœwietlanie struktury
	void display();
	//uruchamianie metody brute force dla struktury
	JobsOrder* bruteforce();
	//metoda g³ówna metody dynamicznego programowania
	JobsOrder* dynamicProgramming();
	//pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	//obliczanie ca³kowitej straty dla podanej kolejnoœci zadañ
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	//destruktor
	~WeightedTardiness();
};

