#include "StateRandom.h"
#include <iostream>
#include "App.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

void StateRandom::process()
{
	std::cout << "Podaj ilosc zadan do wygenerowania: ";
	unsigned int size = App::cinLine(1);
	std::cout << "Generowanie..." << std::endl << std::endl;
	WeightedTardiness* problem =  RandomGenerator::getInstance()->generateWeightedTardiness(size);
	problem->display();
	App::getInstance()->setWeightedTardiness(problem);
	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

bool StateRandom::handleInput(char key)
{
	return false;
}
