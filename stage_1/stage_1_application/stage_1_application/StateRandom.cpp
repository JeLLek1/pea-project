#include "StateRandom.h"
#include <iostream>
#include "App.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateRandom::process()
{
	//ilo�� zada� do wygenerowania
	std::cout << "Podaj ilosc zadan do wygenerowania: ";
	unsigned int size = App::cinLine(1);
	std::cout << "Generowanie..." << std::endl << std::endl;
	//instancja generatora zada� -> wygenerowanie zada�
	WeightedTardiness* problem =  RandomGenerator::getInstance()->generateWeightedTardiness(size);
	//wy�wietlenie wygenerowanego problemu na ekranie
	problem->display();
	App::getInstance()->setWeightedTardiness(problem);
	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

//przetwarzanie wci�ni�tych klawiszy
bool StateRandom::handleInput(char key)
{
	//dowolny klawisz ma zako�czy� stan
	return false;
}
