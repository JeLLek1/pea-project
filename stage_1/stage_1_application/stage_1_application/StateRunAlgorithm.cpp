#include "StateRunAlgorithm.h"
#include <iostream>
#include "App.h"

//konstruktor z podanym typem algorytmu (stanem menu algorytmów)
StateRunAlgorithm::StateRunAlgorithm(StateMenuAlgorithms::MenuStatuses state) : AState()
{
	this->state = state;
}

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateRunAlgorithm::process()
{
	std::cout << "Uruchamianie algorytmu..." << std::endl;
	switch (this->state)
	{
	//algorytm przegl¹du zupe³nego
	case StateMenuAlgorithms::MenuStatuses::BRUTE_FORCE:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->bruteforce();
		order->display();
		delete order;
		break;
	}
		break;
	//algorytm programowania dynamicznego
	case StateMenuAlgorithms::MenuStatuses::DYNAMIC_PROGRAMMING:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->dynamicProgramming();
		order->display();
		delete order;
	}
		break;
	//algorytm B&B przeszukiwania wszerz
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_BFS:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->BandBBFS();
		order->display();
		delete order;
	}
		break;
	//algorytm B&B przeszukwiania typu najpierw najlepszy
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_BEST_FIRST:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->BandBBestFirst();
		order->display();
		delete order;
	}
		break;
	}

	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

//przetwarzanie wciœniêtych klawiszy
bool StateRunAlgorithm::handleInput(char key)
{
	//stan ma siê zakoñczyæ po wciœniêciu dowolnego klawisza
	return false;
}
