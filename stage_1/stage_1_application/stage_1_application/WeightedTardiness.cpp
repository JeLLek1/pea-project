#include "WeightedTardiness.h"
#include <iostream>
#include <iomanip>
#include "App.h"

void WeightedTardiness::pushJob(Job* job)
{
	this->jobs.push_back(job);
}

size_t WeightedTardiness::countJobs()
{
	return this->jobs.size();
}

void WeightedTardiness::display()
{
	std::cout << std::endl << "Liczba zadan: " << this->countJobs() << std::endl;
	std::string nameNumber = "Numer zadania";
	std::string nameTime = "Czas przetwarzania";
	std::string namePriority = "Priorytet zadania";
	std::string nameEnd = "Oczekiwany termin zakonczenia";
	unsigned int digitsNumber = nameNumber.size(), digitsTime = nameTime.size(), digitsPriority = namePriority.size(), digitsEnd = nameEnd.size();
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
	std::cout << std::setw(digitsNumber) << nameNumber << " | ";
	std::cout << std::setw(digitsTime) << nameTime << " | ";
	std::cout << std::setw(digitsPriority) << namePriority << " | ";
	std::cout << std::setw(digitsEnd) << nameEnd << std::endl;
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
	if (size == 1) {
		unsigned int loos = this->getTotalWeightedLoos(order);
		if (loos < best->totalLoos) {
			best->setOrder(order, loos);
		}
	}
	else {
		this->bruteforceGenerate(size - 1, order, best);
		for (size_t i = 0; i < size - 1; i++) {
			if (size % 2 == 0) {
				size_t tmp = order->at(i);
				(*order)[i] = order->at(size - 1);
				(*order)[size - 1] = tmp;
			}
			else {
				size_t tmp = order->at(0);
				(*order)[0] = order->at(size - 1);
				(*order)[size - 1] = tmp;
			}
			this->bruteforceGenerate(size - 1, order, best);
		}
	}
}

JobsOrder* WeightedTardiness::bruteforce()
{
	JobsOrder* best = new JobsOrder();
	std::vector<size_t>* currentOrder = new std::vector<size_t>();
	for (size_t i = 0; i < this->countJobs(); i++) {
		currentOrder->push_back(i);
	}
	this->bruteforceGenerate(this->countJobs(), currentOrder, best);
	delete currentOrder;

	return best;
}
//generowanie podzbior�w i sprawdzanie najmniejszych wag (algorytm Held�Karp)
//punishment - tablica kar dla pozbior�w
//totalTime - czas wykonywania zadania w danym podzbiorze
//jobIndexes - dla u�atwienia odtwarzania zapisywane s� indeksy i podzbiory poprzednik�w
//subsetSize - wielko�� podzbioru, start - startowy bit, end - ko�cowy bit, index - obecny poziom rekurencji, mask - obliczona maska
void WeightedTardiness::dpSubsets(
	std::vector<std::vector<unsigned int>>& punishment,
	std::vector<std::vector<unsigned int>>& totalTime,
	std::vector<std::vector<IndexMask>>& jobIndexes,
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
						if (min > punishment[j][subMask]) {
							min = punishment[j][subMask];
							time = totalTime[j][subMask];
							//zapami�tanie �cie�ki (aby u�atwi� odtwarzanie)
							jobIndexes[i][mask].index = j;
							jobIndexes[i][mask].mask = subMask;
						}
					}
				}
				//zapisanie czasu wykonywania dla znalezionego minimum
				totalTime[i][mask] = time+ this->jobs[i]->processingTime;
				//przypisanie znalezionego minimum
				punishment[i][mask] = min + this->jobs[i]->getWeightedDelay(totalTime[i][mask]);
				
			}
		}
		return;
	}
	//generowane s� kolejne bity rekurencyjnie start-end - kolejne mo�liwe indeksy ustawienia bitu
	//zaczynaj�c od prawej wi�c musi pozosta� miejsce na zmiany pozosta�ych bit�w end - i + 1 >= subsetSize - index
	for (size_t i = start; i <= end && end - i + 1 >= subsetSize - index; i++)
	{
		//przekazywana jest maska z ustawionym nowym bitem
		this->dpSubsets(punishment, totalTime, jobIndexes, subsetSize, end, i+1, index+1, mask + (size_t(1) << i));
	}
}
//metoda g��wna metody dynamicznego programowania
JobsOrder* WeightedTardiness::dynamicProgramming()
{
	//struktura wyniku
	JobsOrder* best = new JobsOrder();
	//liczba podzbior�w potrzebnych do dzia�ania algorytmu pomini�ty zostaje zbi�r pusty
	size_t subsets = (size_t(1) << this->countJobs()) - 1;
	//kara wyliczona dla danego podzbioru w po��czeniu z danym zadaniem
	std::vector<std::vector<unsigned int>> punishment(this->jobs.size(), std::vector<unsigned int>(subsets, UINT_MAX));
	//przechowywany aktualny czas wykonania dla danego podzbioru i danego zadania
	std::vector<std::vector<unsigned int>> totalTime(this->jobs.size(), std::vector<unsigned int>(subsets));
	//przechowanie przej�� mi�dzy zadaniami aby u�atwi� odtwarzanie 
	std::vector<std::vector<IndexMask>> jobIndexes(this->jobs.size(), std::vector<IndexMask>(subsets));
	//wygenerowanie wynik�w dla k {/0} - pojedy�czych zada� (najmniejsze mo�liwe rozbicie problemu)
	for (size_t i = 0; i < this->countJobs(); i++) {
		size_t subset = size_t(1) << i;
		punishment[i][0] = this->jobs[i]->getWeightedDelay(0);
		totalTime[i][0] = this->jobs[i]->processingTime;
	}
	//dla kolejnych wielko�ci pozbior�w generowanie najmniejszych mo�liwych warto�ci op�nienia
	for (unsigned int subsetSize = 1; subsetSize < this->countJobs(); subsetSize++) {
		this->dpSubsets(punishment, totalTime, jobIndexes, subsetSize, this->countJobs() - 1);
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
		if (min > punishment[i][subMaskTmp]) {
			//ustawienie nowego minimum
			min = punishment[i][subMaskTmp];
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
		(*indexes)[index] = jobIndexes[(*indexes)[index+1]][subMask].index;
		//pobranie maski kt�ra by�a przed obenc� mask�
		subMask = jobIndexes[(*indexes)[index+1]][subMask].mask;
	}
	//uzupe�nienie struktury przechowu�cej wynik
	best->setOrder(indexes, min);

	delete indexes;

	return best;
}

Job* WeightedTardiness::getJob(size_t index)
{
	if (index < this->jobs.size()) {
		return this->jobs[index];
	}
	return nullptr;
}

unsigned int WeightedTardiness::getTotalWeightedLoos(std::vector<size_t>* order)
{
	unsigned int loos = 0;
	unsigned int currentTime = 0;
	for (auto index : *order) {
		currentTime += this->jobs[index]->processingTime;
		loos += this->jobs[index]->getWeightedDelay(currentTime);
	}
	return loos;
}

WeightedTardiness::~WeightedTardiness()
{
	while (!this->jobs.empty()) {
		delete this->jobs.back();
		this->jobs.pop_back();
	}
}
