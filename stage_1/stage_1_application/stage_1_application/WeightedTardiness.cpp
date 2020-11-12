#include "WeightedTardiness.h"
#include <iostream>
#include <iomanip>
#include "App.h"
//dodanie zadania do listy zada�
void WeightedTardiness::pushJob(Job* job)
{
	this->jobs.push_back(job);
}
//zwr�cenie ilo�ci zada� dla innych klas
size_t WeightedTardiness::countJobs()
{
	return this->jobs.size();
}
//wy�wietlanie struktury
void WeightedTardiness::display()
{
	//liczba zada�
	std::cout << std::endl << "Liczba zadan: " << this->countJobs() << std::endl;
	//opisy kolumn
	std::string nameNumber = "Numer zadania";
	std::string nameTime = "Czas przetwarzania";
	std::string namePriority = "Priorytet zadania";
	std::string nameEnd = "Oczekiwany termin zakonczenia";
	//wyliczanie ilo�ci znak�w maksymalnej
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
	//wy�wietlanie opis�w kolumn
	std::cout << std::setw(digitsNumber) << nameNumber << " | ";
	std::cout << std::setw(digitsTime) << nameTime << " | ";
	std::cout << std::setw(digitsPriority) << namePriority << " | ";
	std::cout << std::setw(digitsEnd) << nameEnd << std::endl;
	//wy�wietlanie informacji o zadaniach
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
	//permutacja zosta�� wygenerowana
	if (size == 1) {
		//strata obeznej permutacji
		unsigned int loos = this->getTotalWeightedLoos(order);
		//je�eli strata jest mniejsza od najlepszej znalezionej to zamiana rozwi�zania
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
	//najlepszy wynik zwracany przez metod�
	JobsOrder* best = new JobsOrder();
	//obecnie przetwarzana permutacja
	std::vector<size_t>* currentOrder = new std::vector<size_t>();
	for (size_t i = 0; i < this->countJobs(); i++) {
		currentOrder->push_back(i);
	}
	//odpalenie generowania poszczeg�lnych permutacji
	this->bruteforceGenerate(this->countJobs(), currentOrder, best);
	delete currentOrder;

	return best;
}
//subSets - przechowuje informacje o podzbiorach i indeksach zada� takie jak minimalna kara, ca�kowity czas przetwarzania i informacj� o poprzedniku
//jobIndexes - dla u�atwienia odtwarzania zapisywane s� indeksy i podzbiory poprzednik�w
//subsetSize - wielko�� podzbioru, start - startowy bit, end - ko�cowy bit, index - obecny poziom rekurencji, mask - obliczona maska
void WeightedTardiness::dpSubsets(
	std::vector<std::vector<DbSubset>>& subSets,
	size_t subsetSize, size_t end, size_t start, size_t index, size_t mask
)
{
	if (index == subsetSize) {
		//dla wszystkich element�w
		for (size_t i = 0; i < this->countJobs(); i++) {
			//je�eli element nie nale�y do obecnego podzbioru
			if (!(((size_t)1 << i) & mask)) {
				unsigned int min = UINT_MAX;
				unsigned int time = 0;
				size_t index = 0;
				//szukamy podzbiorow {mask}\j z obliczeniami dla j
				for (size_t j = 0; j < this->countJobs(); j++) {
					size_t jSet = size_t(1) << j;
					//je�eli j nale�y do obecnego podzbioru
					if (jSet & mask) {
						//usuwamy z podzbioru jSet
						size_t subMask = mask ^ jSet;
						//sprawdzanie czy znaleziono mniejsze minimum 
						if (min > subSets[j][subMask].totalPunishment) {
							min = subSets[j][subMask].totalPunishment;
							time = subSets[j][subMask].totalTime;
							//zapami�tanie �cie�ki (aby u�atwi� odtwarzanie)
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
	//generowane s� kolejne bity rekurencyjnie start-end - kolejne mo�liwe indeksy ustawienia bitu
	//zaczynaj�c od prawej wi�c musi pozosta� miejsce na zmiany pozosta�ych bit�w end - i + 1 >= subsetSize - index
	for (size_t i = start; i <= end && end - i + 1 >= subsetSize - index; i++)
	{
		//przekazywana jest maska z ustawionym nowym bitem
		this->dpSubsets(subSets, subsetSize, end, i+1, index+1, mask + (size_t(1) << i));
	}
}
//metoda g��wna metody dynamicznego programowania
JobsOrder* WeightedTardiness::dynamicProgramming()
{
	//struktura wyniku
	JobsOrder* best = new JobsOrder();
	//liczba podzbior�w potrzebnych do dzia�ania algorytmu pomini�ty zostaje zbi�r pusty
	size_t subsetsSize = (size_t(1) << this->countJobs()) - 1;
	//przechowanie kary dla poszczeg�lnych podzbior�w i czasu wykonywania oraz przej�� mi�dzy zadaniami aby u�atwi� odtwarzanie 
	std::vector<std::vector<DbSubset>> subSets(this->jobs.size(), std::vector<DbSubset>(subsetsSize));
	//wygenerowanie wynik�w dla k {/0} - pojedy�czych zada� (najmniejsze mo�liwe rozbicie problemu)
	for (size_t i = 0; i < this->countJobs(); i++) {
		size_t subset = size_t(1) << i;
		subSets[i][0].totalPunishment = this->jobs[i]->getWeightedDelay(0);
		subSets[i][0].totalTime = this->jobs[i]->processingTime;
	}
	//dla kolejnych wielko�ci pozbior�w generowanie najmniejszych mo�liwych warto�ci op�nienia
	for (unsigned int subsetSize = 1; subsetSize < this->countJobs(); subsetSize++) {
		this->dpSubsets(subSets, subsetSize, this->countJobs() - 1);
	}
	
	size_t set = (size_t(1) << this->countJobs()) - 1;
	unsigned int min = UINT_MAX;
	//submaska (podzbi�r) rozwi�zania optymalnego do wyszukania kolejno�ci
	size_t subMask = 0;
	//lista indeks�w zada� w kolejno�ci optymalnej
	std::vector<size_t> *indexes = new std::vector<size_t>(this->countJobs());
	//ostatnia iteracja dla zbioru pe�nego (wybieranie ostatniego optymalnego u�o�enia)
	for (size_t i = 0; i < this->countJobs(); i++) {
		//ustawienie maski podzbior�w o wielko�ci 1 mniejszej od wielko�ci zbioru pe�noego
		size_t subMaskTmp = set ^ (size_t(1) << i);
		//je�eli jest mniejsza od poprzeniej znalezionej
		if (min > subSets[i][subMaskTmp].totalPunishment) {
			//ustawienie nowego minimum
			min = subSets[i][subMaskTmp].totalPunishment;
			//zapisanie indeksu jaka ostatnia pozycja listy zada�
			(*indexes)[indexes->size() - 1] = i;
			//zapisanie submaski dla wyszukania reszty zada�
			subMask = subMaskTmp;
		}
	}
	//odtwarzanie pozosta�ych indeks�w
	for (size_t i = 2; i <= indexes->size(); i++) {
		//indeks w tablicy listy zada� zwracanych
		size_t index = indexes->size() - i;
		//pobranie indeksu kt�ry by� przed obecnym indeksem
		(*indexes)[index] = subSets[(*indexes)[index+1]][subMask].subIndex;
		//pobranie maski kt�ra by�a przed obenc� mask�
		subMask = subSets[(*indexes)[index+1]][subMask].subMask;
	}
	//uzupe�nienie struktury przechowu�cej wynik
	best->setOrder(indexes, min);

	delete indexes;

	return best;
}
//pobranie zadania o danym indeksie dla innych klas
Job* WeightedTardiness::getJob(size_t index)
{
	//je�eli indeks za du�y to zwraca nullptr
	if (index < this->jobs.size()) {
		return this->jobs[index];
	}
	return nullptr;
}
//obliczanie ca�kowitej straty dla podanej kolejno�ci zada�
unsigned int WeightedTardiness::getTotalWeightedLoos(std::vector<size_t>* order)
{
	//obecnie obliczona strata
	unsigned int loos = 0;
	//obecny czas wykonywania
	unsigned int currentTime = 0;
	//dla ka�dego elementu
	for (auto index : *order) {
		//dodaj czas wykonywania
		currentTime += this->jobs[index]->processingTime;
		//oblicz strat� na obecnej pozycji
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
