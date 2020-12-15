#include "WeightedTardiness.h"
#include <iostream>
#include <iomanip>
#include "App.h"
#include "RandomGenerator.h"
#include "ANeighborhood.h"

WeightedTardiness::WeightedTardiness()
{
	this->neighborhood = nullptr;
	this->diversification = true;
	this->stopSeconds = 0;
}

ANeighborhood* WeightedTardiness::getNeighborhood()
{
	return this->neighborhood;
}

void WeightedTardiness::setNeighborhood(ANeighborhood* neighborhood)
{
	if(this->neighborhood != nullptr) delete this->neighborhood;
	
	this->neighborhood = neighborhood;
}

bool WeightedTardiness::getDiversification()
{
	return this->diversification;
}

void WeightedTardiness::setDiversification(bool diversification)
{
	this->diversification = diversification;
}

unsigned int WeightedTardiness::getStopSeconds()
{
	return this->stopSeconds;
}

void WeightedTardiness::setStopSeconds(unsigned int seconds)
{
	this->stopSeconds = seconds;
}

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

// generowanie losowej kolejnoœci
std::vector<size_t>* WeightedTardiness::randomOrder() {
	std::vector<size_t>* order = new std::vector<size_t>(this->countJobs());
	for (size_t i = 0; i < this->countJobs(); i++) {
		(*order)[i] = i;
	}
	RandomGenerator* gen = RandomGenerator::getInstance();
	for (size_t i = 0; i < this->countJobs() - 1; i++) {
		size_t randomIndex = gen->getRandom<size_t>(i+1, this->countJobs()-1);
		
		size_t tmp = (*order)[i];
		(*order)[i] = (*order)[randomIndex];
		(*order)[randomIndex] = tmp;
	}
	return order;
}

void WeightedTardiness::erease()
{
	// czyszczenie struktury
	while (!this->jobs.empty()) {
		delete this->jobs.back();
		this->jobs.pop_back();
	}
}

// destruktor
WeightedTardiness::~WeightedTardiness()
{
	delete this->neighborhood;
	this->erease();
}
