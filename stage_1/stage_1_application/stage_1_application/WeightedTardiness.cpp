#include "WeightedTardiness.h"
#include <iostream>
#include <iomanip>
#include "App.h"
//dodanie zadania do listy zadañ
void WeightedTardiness::pushJob(Job* job)
{
	this->jobs.push_back(job);
}
//zwrócenie iloœci zadañ dla innych klas
size_t WeightedTardiness::countJobs()
{
	return this->jobs.size();
}
//wyœwietlanie struktury
void WeightedTardiness::display()
{
	//liczba zadañ
	std::cout << std::endl << "Liczba zadan: " << this->countJobs() << std::endl;
	//opisy kolumn
	std::string nameNumber = "Numer zadania";
	std::string nameTime = "Czas przetwarzania";
	std::string namePriority = "Priorytet zadania";
	std::string nameEnd = "Oczekiwany termin zakonczenia";
	//wyliczanie iloœci znaków maksymalnej
	size_t digitsNumber = nameNumber.size(), digitsTime = nameTime.size(), digitsPriority = namePriority.size(), digitsEnd = nameEnd.size();
	for (auto const& job : this->jobs) {
		unsigned int test = App::countDigits(job->number);
		if (test > digitsNumber) digitsNumber = test;
		test = App::countDigits(job->processingTime);
		if (test > digitsTime) digitsTime = test;
		test = App::countDigits(job->priority);
		if (test > digitsPriority) digitsPriority = test;
		test = App::countDigits(job->expectedEnd);
		if (test > digitsEnd) digitsEnd = test;
	}
	//wyœwietlanie opisów kolumn
	std::cout << std::setw(digitsNumber) << nameNumber << " | ";
	std::cout << std::setw(digitsTime) << nameTime << " | ";
	std::cout << std::setw(digitsPriority) << namePriority << " | ";
	std::cout << std::setw(digitsEnd) << nameEnd << std::endl;
	//wyœwietlanie informacji o zadaniach
	for (auto const& job : this->jobs) {
		std::cout << std::setw(digitsNumber) << job->number << " | ";
		std::cout << std::setw(digitsTime) << job->processingTime << " | ";
		std::cout << std::setw(digitsPriority) << job->priority << " | ";
		std::cout << std::setw(digitsEnd) << job->expectedEnd << std::endl;
	}
}
//algorytm heapa generowania wszystkich permutacji
void WeightedTardiness::bruteforceGenerate(size_t size, std::vector<size_t>* order, JobsOrder* best)
{
	//permutacja zosta³¹ wygenerowana
	if (size == 1) {
		//strata obeznej permutacji
		unsigned int loos = this->getTotalWeightedLoos(order);
		//je¿eli strata jest mniejsza od najlepszej znalezionej to zamiana rozwi¹zania
		if (loos < best->totalLoos) {
			best->setOrder(order, loos);
		}
	}
	//generowanie kolejnych zamian dla permutacji
	else {
		this->bruteforceGenerate(size - 1, order, best);
		for (size_t i = 0; i < size - 1; i++) {
			if (size % 2 == 0) {
				//swap i oraz size-1
				size_t tmp = order->at(i);
				(*order)[i] = order->at(size - 1);
				(*order)[size - 1] = tmp;
			}
			else {
				//swap 0 oraz size-1
				size_t tmp = order->at(0);
				(*order)[0] = order->at(size - 1);
				(*order)[size - 1] = tmp;
			}
			this->bruteforceGenerate(size - 1, order, best);
		}
	}
}
//uruchamianie metody brute force dla struktury
JobsOrder* WeightedTardiness::bruteforce()
{
	//najlepszy wynik zwracany przez metodê
	JobsOrder* best = new JobsOrder();
	//obecnie przetwarzana permutacja
	std::vector<size_t>* currentOrder = new std::vector<size_t>();
	for (size_t i = 0; i < this->countJobs(); i++) {
		currentOrder->push_back(i);
	}
	//odpalenie generowania poszczególnych permutacji
	this->bruteforceGenerate(this->countJobs(), currentOrder, best);
	delete currentOrder;

	return best;
}
//subSets - przechowuje informacje o podzbiorach i indeksach zadañ takie jak minimalna kara, ca³kowity czas przetwarzania i informacjê o poprzedniku
//jobIndexes - dla u³atwienia odtwarzania zapisywane s¹ indeksy i podzbiory poprzedników
//subsetSize - wielkoœæ podzbioru, start - startowy bit, end - koñcowy bit, index - obecny poziom rekurencji, mask - obliczona maska
void WeightedTardiness::dpSubsets(
	std::vector<std::vector<DbSubset>>& subSets,
	size_t subsetSize, size_t end, size_t start, size_t index, size_t mask
)
{
	if (index == subsetSize) {
		//dla wszystkich elementów
		for (size_t i = 0; i < this->countJobs(); i++) {
			//je¿eli element nie nale¿y do obecnego podzbioru
			if (!(((size_t)1 << i) & mask)) {
				unsigned int min = UINT_MAX;
				unsigned int time = 0;
				size_t index = 0;
				//szukamy podzbiorow {mask}\j z obliczeniami dla j
				for (size_t j = 0; j < this->countJobs(); j++) {
					size_t jSet = size_t(1) << j;
					//je¿eli j nale¿y do obecnego podzbioru
					if (jSet & mask) {
						//usuwamy z podzbioru jSet
						size_t subMask = mask ^ jSet;
						//sprawdzanie czy znaleziono mniejsze minimum 
						if (min > subSets[j][subMask].totalPunishment) {
							min = subSets[j][subMask].totalPunishment;
							time = subSets[j][subMask].totalTime;
							//zapamiêtanie œcie¿ki (aby u³atwiæ odtwarzanie)
							subSets[i][mask].subIndex = j;
							subSets[i][mask].subMask = subMask;
						}
					}
				}
				//zapisanie czasu wykonywania dla znalezionego minimum
				subSets[i][mask].totalTime = time+ this->jobs[i]->processingTime;
				//przypisanie znalezionego minimum
				subSets[i][mask].totalPunishment = min + this->jobs[i]->getWeightedDelay(subSets[i][mask].totalTime);
				
			}
		}
		return;
	}
	//generowane s¹ kolejne bity rekurencyjnie start-end - kolejne mo¿liwe indeksy ustawienia bitu
	//zaczynaj¹c od prawej wiêc musi pozostaæ miejsce na zmiany pozosta³ych bitów end - i + 1 >= subsetSize - index
	for (size_t i = start; i <= end && end - i + 1 >= subsetSize - index; i++)
	{
		//przekazywana jest maska z ustawionym nowym bitem
		this->dpSubsets(subSets, subsetSize, end, i+1, index+1, mask + (size_t(1) << i));
	}
}
//metoda g³ówna metody dynamicznego programowania
JobsOrder* WeightedTardiness::dynamicProgramming()
{
	//struktura wyniku
	JobsOrder* best = new JobsOrder();
	//liczba podzbiorów potrzebnych do dzia³ania algorytmu pominiêty zostaje zbiór pusty
	size_t subsetsSize = (size_t(1) << this->countJobs()) - 1;
	//przechowanie kary dla poszczególnych podzbiorów i czasu wykonywania oraz przejœæ miêdzy zadaniami aby u³atwiæ odtwarzanie 
	std::vector<std::vector<DbSubset>> subSets(this->jobs.size(), std::vector<DbSubset>(subsetsSize));
	//wygenerowanie wyników dla k {/0} - pojedyñczych zadañ (najmniejsze mo¿liwe rozbicie problemu)
	for (size_t i = 0; i < this->countJobs(); i++) {
		size_t subset = size_t(1) << i;
		subSets[i][0].totalPunishment = this->jobs[i]->getWeightedDelay(0);
		subSets[i][0].totalTime = this->jobs[i]->processingTime;
	}
	//dla kolejnych wielkoœci pozbiorów generowanie najmniejszych mo¿liwych wartoœci opóŸnienia
	for (unsigned int subsetSize = 1; subsetSize < this->countJobs(); subsetSize++) {
		this->dpSubsets(subSets, subsetSize, this->countJobs() - 1);
	}
	
	size_t set = (size_t(1) << this->countJobs()) - 1;
	unsigned int min = UINT_MAX;
	//submaska (podzbiór) rozwi¹zania optymalnego do wyszukania kolejnoœci
	size_t subMask = 0;
	//lista indeksów zadañ w kolejnoœci optymalnej
	std::vector<size_t> *indexes = new std::vector<size_t>(this->countJobs());
	//ostatnia iteracja dla zbioru pe³nego (wybieranie ostatniego optymalnego u³o¿enia)
	for (size_t i = 0; i < this->countJobs(); i++) {
		//ustawienie maski podzbiorów o wielkoœci 1 mniejszej od wielkoœci zbioru pe³noego
		size_t subMaskTmp = set ^ (size_t(1) << i);
		//je¿eli jest mniejsza od poprzeniej znalezionej
		if (min > subSets[i][subMaskTmp].totalPunishment) {
			//ustawienie nowego minimum
			min = subSets[i][subMaskTmp].totalPunishment;
			//zapisanie indeksu jaka ostatnia pozycja listy zadañ
			(*indexes)[indexes->size() - 1] = i;
			//zapisanie submaski dla wyszukania reszty zadañ
			subMask = subMaskTmp;
		}
	}
	//odtwarzanie pozosta³ych indeksów
	for (size_t i = 2; i <= indexes->size(); i++) {
		//indeks w tablicy listy zadañ zwracanych
		size_t index = indexes->size() - i;
		//pobranie indeksu który by³ przed obecnym indeksem
		(*indexes)[index] = subSets[(*indexes)[index+1]][subMask].subIndex;
		//pobranie maski która by³a przed obenc¹ mask¹
		subMask = subSets[(*indexes)[index+1]][subMask].subMask;
	}
	//uzupe³nienie struktury przechowu¹cej wynik
	best->setOrder(indexes, min);

	delete indexes;

	return best;
}
//pobranie zadania o danym indeksie dla innych klas
Job* WeightedTardiness::getJob(size_t index)
{
	//je¿eli indeks za du¿y to zwraca nullptr
	if (index < this->jobs.size()) {
		return this->jobs[index];
	}
	return nullptr;
}
//obliczanie ca³kowitej straty dla podanej kolejnoœci zadañ
unsigned int WeightedTardiness::getTotalWeightedLoos(std::vector<size_t>* order)
{
	//obecnie obliczona strata
	unsigned int loos = 0;
	//obecny czas wykonywania
	unsigned int currentTime = 0;
	//dla ka¿dego elementu
	for (auto index : *order) {
		//dodaj czas wykonywania
		currentTime += this->jobs[index]->processingTime;
		//oblicz stratê na obecnej pozycji
		loos += this->jobs[index]->getWeightedDelay(currentTime);
	}
	return loos;
}
//destruktor
WeightedTardiness::~WeightedTardiness()
{
	while (!this->jobs.empty()) {
		delete this->jobs.back();
		this->jobs.pop_back();
	}
}
