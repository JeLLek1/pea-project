#pragma once
#include <vector>
#include "Job.h"
#include "JobsOrder.h"
#include "DbSubset.h"
#include "JobNode.h"
/*
Klasa problemu szeregowania zada� dla 
*/
class WeightedTardiness
{
private:
	//lista zada�
	std::vector<Job*> jobs;

	//algorytm heapa generowania wszystkich permutacji
	void bruteforceGenerate(size_t size, std::vector<size_t>* order, JobsOrder* best);
	//subSets - przechowuje informacje o podzbiorach i indeksach zada� takie jak minimalna kara, ca�kowity czas przetwarzania i informacj� o poprzedniku
	//jobIndexes - dla u�atwienia odtwarzania zapisywane s� indeksy i podzbiory poprzednik�w
	//subsetSize - wielko�� podzbioru, start - startowy bit, end - ko�cowy bit, index - obecny poziom rekurencji, mask - obliczona maska
	void dpSubsets(
		std::vector<std::vector<DbSubset>>& subSets,
		size_t subsetSize, size_t end, size_t start = 0, size_t index = 0, size_t mask=0
	);
	//funkcja kosztu dla B&B (metod� zach�ann� wyszukiwanie tych zada� kt�re maj� najwi�szy obecny koszt)
	unsigned int BandBupper();
	//funkcja kosztu dla B&B (metod� zach�ann� wyszukiwanie tych zada� kt�re maj� najwi�szy obecny koszt)
	unsigned int BandBlower(JobNode* node, size_t current, unsigned int totalTime);
public:

	//dodanie zadania do listy zada�
	void pushJob(Job* job);
	//zwr�cenie ilo�ci zada� dla innych klas
	size_t countJobs();
	//wy�wietlanie struktury
	void display();
	//uruchamianie metody brute force dla struktury
	JobsOrder* bruteforce();
	//metoda g��wna metody dynamicznego programowania
	JobsOrder* dynamicProgramming();
	//B&B Wszerz
	JobsOrder* BandBBFS();
	//B&B Najpierw najlepszy
	JobsOrder* BandBBestFirst();
	//pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	//obliczanie ca�kowitej straty dla podanej kolejno�ci zada�
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	//destruktor
	~WeightedTardiness();
};

