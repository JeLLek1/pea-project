#include "StateRandom.h"
#include <iostream>
#include "App.h"
#include "RandomGenerator.h"
#include "WeightedTardiness.h"

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateRandom::process()
{
	//iloœæ zadañ do wygenerowania
	std::cout << "Podaj ilosc zadan do wygenerowania: ";
	unsigned int size = App::cinLine(1);
	std::cout << "Generowanie..." << std::endl << std::endl;
	//instancja generatora zadañ -> wygenerowanie zadañ
	WeightedTardiness* problem =  RandomGenerator::getInstance()->generateWeightedTardiness(size);
	//wyœwietlenie wygenerowanego problemu na ekranie
	problem->display();
	App::getInstance()->setWeightedTardiness(problem);
	std::cout << std::endl << "Nacisnij dowolny klawisz by powrocic...";
}

//przetwarzanie wciœniêtych klawiszy
bool StateRandom::handleInput(char key)
{
	//dowolny klawisz ma zakoñczyæ stan
	return false;
}
