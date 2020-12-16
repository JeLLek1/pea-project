#include "StateRunAlgorithm.h"
#include <iostream>
#include "App.h"
#include "WeightedTardiness.h"
#include "ANeighborhood.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"

//reset czasu
void StateRunAlgorithm::resetTimer()
{
	this->start = std::chrono::high_resolution_clock::now();
}
//czas od ostatniego restartu
long long StateRunAlgorithm::returnTime()
{
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end - this->start).count();
}

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateRunAlgorithm::process()
{
	WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
	if (problem->countJobs() == 0) {
		std::cout << "Nalezy najpierw wczytac dane testowe\n";
		this->canBeRunned = false;
	}
	if (problem->countJobs() < 2) {
		std::cout << "Definicje sasiedztwa nie maja sensu dla problemow wielkosci mniejszej niz 2\n";
		this->canBeRunned = false;
	}
	if (problem->getNeighborhood() == nullptr) {
		std::cout << "Nalezy najpierw wybrac typ sasiedztwa\n";
		this->canBeRunned = false;
	}
	if (problem->getStopSeconds() < 1) {
		std::cout << "Nalezy najpierw wprowadzic kryterium stopu\n";
		this->canBeRunned = false;
	}

	if (this->canBeRunned) {
		std::cout << "Ilosc elementow problemu: " << problem->countJobs();
		std::cout << "\nTyp sasiedztwa: " << ANeighborhood::typeNames.at(problem->getNeighborhood()->getType());
		std::cout << "\nKryterium stopu: " << problem->getStopSeconds();
		std::cout << "\nDywersyfikacja: " << ( problem->getDiversification() ? "Tak" : "Nie" );
		std::cout << "\n\nWybierz algorytm [1 - SA, 2 - TS]: ";
		this->runAlgorithm(App::cinLine(1));
	}
	
	std::cout << "\nNacisnij dowolny klawisz by kontynuowac...";
}

//przetwarzanie wciœniêtych klawiszy
bool StateRunAlgorithm::handleInput(char key)
{
	//dowolny klawisz ma zakoñczyæ stan
	return false;
}

void StateRunAlgorithm::runAlgorithm(size_t choose)
{
	switch (choose) {
	case 1: {
		this->resetTimer();
		SimulatedAnnealing* algorithm = new SimulatedAnnealing(App::getInstance()->getWeightedTardiness());
		algorithm->run();
		long long time = this->returnTime();
		std::cout << "\nCzas wykonywania: " << 0.001 * time << " ms\n\n";
		algorithm->bestOrder->display();
		delete algorithm;
		break;
	}
	case 2: {
		TabuSearch* algorithm;
		if (App::getInstance()->getWeightedTardiness()->getDiversification()) {
			this->resetTimer();
			algorithm = new TabuSearch(App::getInstance()->getWeightedTardiness());
			algorithm->runDiversifi();
		}
		else {
			this->resetTimer();
			algorithm = new TabuSearch(App::getInstance()->getWeightedTardiness());
			algorithm->run();
		}
		long long time = this->returnTime();
		std::cout << "\nCzas wykonywania: " << 0.001 * time << " ms\n\n";
		algorithm->bestOrder->display();
		delete algorithm;
		break;
	}
	default:
		std::cout << "\nNieprawidlowy indeks algorytmu";
		break;
	}
}
