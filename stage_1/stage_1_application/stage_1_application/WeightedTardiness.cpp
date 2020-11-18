#include "WeightedTardiness.h"
#include <iostream>
#include <iomanip>
#include <queue>
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
/**********************************
			BrutForce
**********************************/
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
	std::vector<size_t>* currentOrder = new std::vector<size_t>(this->countJobs());
	for (size_t i = 0; i < this->countJobs(); i++) {
		(*currentOrder)[i] = i;
	}
	//odpalenie generowania poszczeg�lnych permutacji
	this->bruteforceGenerate(this->countJobs(), currentOrder, best);
	delete currentOrder;

	return best;
}
/**********************************
		End BrutForce
**********************************/
/**********************************
		Dynamic Programming
**********************************/
//uzupe�nianie tablicy zbior�w dla db
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
						}
					}
				}
				//zapisanie czasu wykonywania dla znalezionego minimum
				subSets[i][mask].totalTime = time+ this->jobs[i]->processingTime;
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

//wyszukiwanie optymalnych wynik�w w tablicy zbior�w
//subSets - wygenerowana tablica podzbior�w
//best - lista najlepszej �cie�ki
void WeightedTardiness::dpSubsetsBack(std::vector<std::vector<DbSubset>>& subSets, std::vector<size_t>* best) {
	size_t subset = (size_t(1) << this->countJobs()) - 1;
	//dla ka�dego indeksu od najwi�kszego
	for (size_t index = this->countJobs(); index-- >0;) {
		unsigned int minPunishment = UINT_MAX;
		size_t submaskBest = 0;
		//przeszukiwanie podzbior�w
		for (size_t el = 0; el < this->countJobs(); el++) {
			size_t elementMask = size_t(1) << el;
			//najlepszy wynik dla podzbioru
			if (subset & elementMask) {
				size_t submask = subset ^ elementMask;
				if (subSets[el][submask].totalPunishment < minPunishment) {
					(*best)[index] = el;
					minPunishment = subSets[el][submask].totalPunishment;
					submaskBest = submask;
				}
			}
		}
		subset = submaskBest;
	}
}

//metoda g��wna metody dynamicznego programowania
JobsOrder* WeightedTardiness::dynamicProgramming()
{

	JobsOrder* best = new JobsOrder();
	size_t subsetsSize = (size_t(1) << this->countJobs()) - 1;
	std::vector<std::vector<DbSubset>> subSets(this->jobs.size(), std::vector<DbSubset>(subsetsSize));
	//wygenerowanie wynik�w dla k {/0} - pojedy�czych zada� (najmniejsze mo�liwe rozbicie problemu)
	for (size_t i = 0; i < this->countJobs(); i++) {
		size_t subset = size_t(1) << i;
		subSets[i][0].totalPunishment = this->jobs[i]->getWeightedDelay(this->jobs[i]->processingTime);
		subSets[i][0].totalTime = this->jobs[i]->processingTime;
	}

	//dla kolejnych wielko�ci pozbior�w generowanie najmniejszych mo�liwych warto�ci op�nienia
	for (unsigned int subsetSize = 1; subsetSize < this->countJobs(); subsetSize++) {
		this->dpSubsets(subSets, subsetSize, this->countJobs() - 1);
	}
	
	size_t set = (size_t(1) << this->countJobs()) - 1;
	unsigned int min = UINT_MAX;

	size_t subMask = 0;
	std::vector<size_t> *indexes = new std::vector<size_t>(this->countJobs());
	//szukanie optymalnego wyniku w tablicy wyniku
	this->dpSubsetsBack(subSets, indexes);

	//uzupe�nienie struktury przechowu�cej wynik
	size_t bestIndexLast = (*indexes)[this->countJobs() - 1];
	size_t bestSubset = ((size_t(1) << this->countJobs()) - 1) ^ (size_t(1) << bestIndexLast);
	best->setOrder(indexes, subSets[bestIndexLast][bestSubset].totalPunishment);

	delete indexes;

	return best;
}
/**********************************
	End Dynamic Programming
**********************************/
/**********************************
				B&B
**********************************/
//sortowanie zada� po czasie wykonywania
std::vector<size_t>* WeightedTardiness::orderJobs()
{
	std::vector<size_t>* tmp = new std::vector<size_t>(this->countJobs());
	for (size_t i = 0; i < this->countJobs(); i++) {
		(*tmp)[i] = i;
	}
	//sortowanie rosn�ce
	std::sort(tmp->begin(), tmp->end(), [this](size_t lhs, size_t rhs) -> bool {
		return this->jobs[lhs]->processingTime < this->jobs[rhs]->processingTime;
	});
	return tmp;
}

//Kolejne permutacje (dla B&B wg��b)
void WeightedTardiness::permutate(JobsOrder* best, std::vector<size_t>* currentPermutation, std::vector<size_t>* orderedJobs, size_t l, bool* nodesUsed, unsigned int currentTime, unsigned int totalLoos,
	unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*))
{
	if (l == this->countJobs()-1) {
		unsigned int tmpProcessingTime = currentTime + this->jobs[(*currentPermutation)[l]]->processingTime;
		unsigned int tmpTotalLoos = totalLoos + this->jobs[(*currentPermutation)[l]]->getWeightedDelay(tmpProcessingTime);
		if (tmpTotalLoos < best->totalLoos) {
			best->setOrder(currentPermutation, tmpTotalLoos);
		}
	}
	else {
		for (size_t i = l; i < this->countJobs(); i++) {
			unsigned int tmpProcessingTime = currentTime + this->jobs[(*currentPermutation)[i]]->processingTime;
			unsigned int tmpTotalLoos = totalLoos + this->jobs[(*currentPermutation)[i]]->getWeightedDelay(tmpProcessingTime);
			nodesUsed[(*currentPermutation)[i]] = true;
			if (tmpTotalLoos+(*lowerBoundFunction)(nodesUsed, currentTime, orderedJobs, this)< best->totalLoos) {
				size_t tmp = (*currentPermutation)[l];
				(*currentPermutation)[l] = (*currentPermutation)[i];
				(*currentPermutation)[i] = tmp;
				this->permutate(best, currentPermutation, orderedJobs, l + 1, nodesUsed, tmpProcessingTime, tmpTotalLoos, lowerBoundFunction);
				tmp = (*currentPermutation)[l];
				(*currentPermutation)[l] = (*currentPermutation)[i];
				(*currentPermutation)[i] = tmp;
			}
			nodesUsed[(*currentPermutation)[i]] = false;
		}
	}
}

//dolna granica (wszyskie elementy wykonane w czasie aktualnym)
unsigned int WeightedTardiness::BandBlower1(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem)
{
	unsigned int maxDueDate = 0;
	for (size_t i = 0; i < currentProblem->countJobs(); i++) {
		if (!nodesUsed[(*orderedJobs)[i]] && currentProblem->jobs[(*orderedJobs)[i]]->expectedEnd > maxDueDate) {
			maxDueDate = currentProblem->jobs[(*orderedJobs)[i]]->expectedEnd;
		}
	}
	unsigned int lowerBound = 0;
	for (size_t i = 0; i < currentProblem->countJobs(); i++) {
		if (!nodesUsed[(*orderedJobs)[i]]) {
			currentTime += currentProblem->jobs[(*orderedJobs)[i]]->processingTime;
			lowerBound += (currentTime < maxDueDate) ? 0 : (currentTime - maxDueDate) * currentProblem->jobs[(*orderedJobs)[i]]->priority;
		}
	}
	return lowerBound;
}
//funkcja dolnego ograniczenia 2 (jakby wszystkie zadania mia�y zako�czy� si� w tej chwili)
unsigned int WeightedTardiness::BandBlower2(bool* nodesUsed, unsigned int currentTime, std::vector<size_t>* orderedJobs, WeightedTardiness* currentProblem)
{
	unsigned int lowerBound = 0;
	for (size_t i = 0; i < currentProblem->countJobs(); i++) {
		if (!nodesUsed[i]) {
			lowerBound += currentProblem->jobs[i]->getWeightedDelay(currentTime + currentProblem->jobs[i]->processingTime);
		}
	}
	return lowerBound;
}

//pierwsza granica g�rna
unsigned int WeightedTardiness::upperBound() {
	std::vector<size_t>* tmp = new std::vector<size_t>(this->countJobs());
	for (size_t i = 0; i < this->countJobs(); i++) {
		(*tmp)[i] = i;
	}
	//sortowanie rosn�ce
	std::sort(tmp->begin(), tmp->end(), [this](size_t lhs, size_t rhs) -> bool {
		return this->jobs[lhs]->processingTime < this->jobs[rhs]->processingTime;
	});
	unsigned int upperBound = this->getTotalWeightedLoos(tmp);
	delete tmp;
	return upperBound;
}
//B&B przeszukiwanie wg��b
JobsOrder* WeightedTardiness::BandBDFS(unsigned int (*lowerBoundFunction)(bool*, unsigned int, std::vector<size_t>*, WeightedTardiness*))
{
	//struktura przechowuj�ca najlepszy wynik
	JobsOrder* best = new JobsOrder();
	best->totalLoos = this->upperBound();
	//zadania posortowanie o najkr�cej wykonuj�cego si�
	std::vector<size_t>* orderedJobs = this->orderJobs();
	//obecna permutacja
	std::vector<size_t>* currentPermutation = new std::vector<size_t>(this->countJobs());
	for (size_t i = 0; i < this->countJobs(); i++) {
		(*currentPermutation)[i] = i;
	}
	//wykorzystane wierzcho�ki
	bool* nodeUsed = new bool[this->countJobs()];
	std::fill(nodeUsed, nodeUsed + this->countJobs(), false);
	this->permutate(best, currentPermutation, orderedJobs, 0, nodeUsed, 0, 0, lowerBoundFunction);
	delete[] nodeUsed;
	delete currentPermutation;
	delete orderedJobs;
	return best;
}

/**********************************
			End B&B
**********************************/

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
