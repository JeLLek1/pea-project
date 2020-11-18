#pragma once
#include <vector>
#include "Job.h"
#include "JobsOrder.h"
#include "DbSubset.h"
#include "JobNode.h"
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
	//uzupe³nianie tablicy zbiorów dla db
	//subSets - przechowuje informacje o podzbiorach i indeksach zadañ takie jak minimalna kara, ca³kowity czas przetwarzania i informacjê o poprzedniku
	//jobIndexes - dla u³atwienia odtwarzania zapisywane s¹ indeksy i podzbiory poprzedników
	//subsetSize - wielkoœæ podzbioru, start - startowy bit, end - koñcowy bit, index - obecny poziom rekurencji, mask - obliczona maska
	void dpSubsets(
		std::vector<std::vector<DbSubset>>& subSets,
		size_t subsetSize, size_t end, size_t start = 0, size_t index = 0, size_t mask=0
	);
	//wyszukiwanie optymalnych wyników w tablicy zbiorów
	//subSets tablica podzbiorów
	//best - tablica najlepszej œcie¿ki
	void dpSubsetsBack(
		std::vector<std::vector<DbSubset>>& subSets,
		std::vector<size_t>* best
	);
	//kolejne permutacje dla B&B z lowerBound
	//best - najlepsza œcie¿ka
	//currentPermutation - obecna permutacja
	//orderedJobs - posortowane niemalej¹co zadania wed³ug czasu trwania zadania
	//l obecny indeks zmiany
	//nodeUsed - tablica przechowuj¹ca informacje których elementów u³o¿enie ju¿ znamy
	//currentTime - obecny czas wykonywania u³o¿onych zadañ
	//lowerBoundFunction - wybrana funckja dolnego ograniczenia
	void permutate(JobsOrder* best, std::vector<size_t>* currentPermutation, std::vector<size_t>* orderedJobs, size_t l, bool *nodesUsed, unsigned int currentTime, unsigned int totalLoos,
		unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*)
	);
	//sortowanie zadañ po czasie wykonywania
	std::vector<size_t>* orderJobs();
	//generowanie pierwszej górnej granicy
	unsigned int upperBound();
public:
	//funkcja dolnego ograniczenia 1 (sortowanie od najmniejszego i maksymalny termin jako termin wszystkich)
	static unsigned int BandBlower1(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem);
	//funkcja dolnego ograniczenia 2 (jakby wszystkie zadania mia³y zakoñczyæ siê w tej chwili)
	static unsigned int BandBlower2(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem);

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
	//B&B Wg³¹b
	JobsOrder* BandBDFS(unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*));
	//pobranie zadania o danym indeksie dla innych klas
	Job* getJob(size_t index);
	//obliczanie ca³kowitej straty dla podanej kolejnoœci zadañ
	unsigned int getTotalWeightedLoos(std::vector<size_t>* order);
	//destruktor
	~WeightedTardiness();
};

