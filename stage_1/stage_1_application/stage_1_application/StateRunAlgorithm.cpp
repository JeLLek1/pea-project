#include "StateRunAlgorithm.h"
#include <iostream>
#include "App.h"

StateRunAlgorithm::StateRunAlgorithm(StateMenuAlgorithms::MenuStatuses state) : AState()
{
	this->state = state;
}

void StateRunAlgorithm::process()
{
	std::cout << "Uruchamianie algorytmu..." << std::endl;
	switch (this->state)
	{
	case StateMenuAlgorithms::MenuStatuses::BRUTE_FORCE:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->bruteforce();
		order->display();
		delete order;
		break;
	}
		break;
	case StateMenuAlgorithms::MenuStatuses::DYNAMIC_PROGRAMMING:
	{
		JobsOrder* order = App::getInstance()->getWeightedTardiness()->dynamicProgramming();
		order->display();
		delete order;
		break;
	}
		break;
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_1:
		break;
	case StateMenuAlgorithms::MenuStatuses::B_AND_B_2:
		break;
	}

	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

bool StateRunAlgorithm::handleInput(char key)
{
	return false;
}
