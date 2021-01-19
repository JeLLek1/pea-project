#include "StateRunAlgorithm.h"
#include <iostream>
#include "App.h"
#include "WeightedTardiness.h"
#include "GeneticAlgorithm.h"

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
		std::cout << "\nNacisnij dowolny klawisz by kontynuowac...";
		return;
	}
	if (problem->countJobs() < 2) {
		std::cout << "Problem jest zbyt ma³y aby uruchomiæ na nim zaimplementowany algorytm genetyczny\n";
		std::cout << "\nNacisnij dowolny klawisz by kontynuowac...";
		return;
	}

	std::cout << "Ilosc elementow problemu: " << problem->countJobs();
	std::cout << "\nKryterium stopu: " << problem->stopSeconds;
	std::cout << "\nWspolczynnik krzyzowania: " << problem->crossoverRatio;
	std::cout << "\nWspolczynnik mutacji: " << problem->mutationRatio;
	std::cout << "\nMetoda krzyzowania: " << ((problem->crossFunction == GeneticAlgorithm::PMX) ? "PMX" : "OX");
	std::cout << "\nMetoda mutacji: " << ((problem->mutationFunction == GeneticAlgorithm::insertMutation) ? "insert" : "transposition");
	
	this->resetTimer();
	GeneticAlgorithm algorithm(App::getInstance()->getWeightedTardiness());
	algorithm.runAlgorithm();
	long long time = this->returnTime();
	std::cout << "\nCzas wykonywania: " << 0.001 * time << " ms\n\n";
	algorithm.best->display();

	std::cout << "\nNacisnij dowolny klawisz by kontynuowac...";
}

//przetwarzanie wciœniêtych klawiszy
bool StateRunAlgorithm::handleInput(char key)
{
	//dowolny klawisz ma zakoñczyæ stan
	return false;
}
