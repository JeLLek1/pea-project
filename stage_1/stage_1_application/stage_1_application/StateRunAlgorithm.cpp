#include "StateRunAlgorithm.h"
#include <chrono>
#include <iostream>
#include "App.h"

//konstruktor z podanym typem algorytmu (stanem menu algorytm�w)
StateRunAlgorithm::StateRunAlgorithm(StateMenuAlgorithms::MenuStatuses state) : AState()
{
	this->state = state;
}

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateRunAlgorithm::process()
{
	std::cout << "Uruchamianie algorytmu..." << std::endl;
	switch (this->state)
	{
	//algorytm przegl�du zupe�nego
	case StateMenuAlgorithms::MenuStatuses::BRUTE_FORCE:
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->bruteforce();
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		order->display();
		std::cout << std::endl << "Czas wykonywania: " << 0.001 * std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms";
		delete order;
		break;
	}
		break;
	//algorytm programowania dynamicznego
	case StateMenuAlgorithms::MenuStatuses::DYNAMIC_PROGRAMMING:
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->dynamicProgramming();
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		order->display();
		std::cout << std::endl << "Czas wykonywania: " << 0.001 * std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms";
		delete order;
	}
		break;
	//algorytm B&B przeszukiwania wszerz
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_DFS_1:
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->BandBDFS(WeightedTardiness::BandBlower1);
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		order->display();
		std::cout << std::endl << "Czas wykonywania: " << 0.001 * std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms";
		delete order;
	}
		break;
	//algorytm B&B przeszukwiania typu najpierw najlepszy
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_DFS_2:
	{
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->BandBDFS(WeightedTardiness::BandBlower2);
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		order->display();
		std::cout << std::endl << "Czas wykonywania: " << 0.001 * std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " ms";
		delete order;
	}
		break;
	}

	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

//przetwarzanie wci�ni�tych klawiszy
bool StateRunAlgorithm::handleInput(char key)
{
	//stan ma si� zako�czy� po wci�ni�ciu dowolnego klawisza
	return false;
}
