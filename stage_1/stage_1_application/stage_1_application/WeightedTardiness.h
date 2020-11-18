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
	//uzupe�nianie tablicy zbior�w dla db
	//subSets - przechowuje informacje o podzbiorach i indeksach zada� takie jak minimalna kara, ca�kowity czas przetwarzania i informacj� o poprzedniku
	//jobIndexes - dla u�atwienia odtwarzania zapisywane s� indeksy i podzbiory poprzednik�w
	//subsetSize - wielko�� podzbioru, start - startowy bit, end - ko�cowy bit, index - obecny poziom rekurencji, mask - obliczona maska
	void dpSubsets(
		std::vector<std::vector<DbSubset>>& subSets,
		size_t subsetSize, size_t end, size_t start = 0, size_t index = 0, size_t mask=0
	);
	//wyszukiwanie optymalnych wynik�w w tablicy zbior�w
	//subSets tablica podzbior�w
	//best - tablica najlepszej �cie�ki
	void dpSubsetsBack(
		std::vector<std::vector<DbSubset>>& subSets,
		std::vector<size_t>* best
	);
	//kolejne permutacje dla B&B z lowerBound
	//best - najlepsza �cie�ka
	//currentPermutation - obecna permutacja
	//orderedJobs - posortowane niemalej�co zadania wed�ug czasu trwania zadania
	//l obecny indeks zmiany
	//nodeUsed - tablica przechowuj�ca informacje kt�rych element�w u�o�enie ju� znamy
	//currentTime - obecny czas wykonywania u�o�onych zada�
	//lowerBoundFunction - wybrana funckja dolnego ograniczenia
	void permutate(JobsOrder* best, std::vector<size_t>* currentPermutation, std::vector<size_t>* orderedJobs, size_t l, bool *nodesUsed, unsigned int currentTime, unsigned int totalLoos,
		unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*)
	);
	//sortowanie zada� po czasie wykonywania
	std::vector<size_t>* orderJobs();
	//generowanie pierwszej g�rnej granicy
	unsigned int upperBound();
public:
	//funkcja dolnego ograniczenia 1 (sortowanie od najmniejszego i maksymalny termin jako termin wszystkich)
	static unsigned int BandBlower1(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem);
	//funkcja dolnego ograniczenia 2 (jakby wszystkie zadania mia�y zako�czy� si� w tej chwili)
	static unsigned int BandBlower2(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem);

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
	//B&B Wg��b
	JobsOrder* BandBDFS(unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*));
	//pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	//obliczanie ca�kowitej straty dla podanej kolejno�ci zada�
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	//destruktor
	~WeightedTardiness();
};

