#include "StateMenuAlgorithms.h"
#include <iostream>
#include "App.h"
#include "StateRunAlgorithm.h"
#include "JobsOrder.h"

//mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
const std::map<StateMenuAlgorithms::MenuStatuses, std::string> StateMenuAlgorithms::menuStatusesNames = {
	{MenuStatuses::BRUTE_FORCE, "Przeglad zupelny"},
	{MenuStatuses::DYNAMIC_PROGRAMMING, "Programowanie dynamiczne"},
	{MenuStatuses::B_AND_B_DFS_1, "B & B w glab - pierwsza funkcja ograniczajaca"},
	{MenuStatuses::B_AND_B_DFS_2, "B & B w glab - druga funkcja ograniczajaca"},
	{MenuStatuses::BACK, "Powrot"},
};

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateMenuAlgorithms::process()
{
	//je�eli brak instancji nie mo�na wykona� algorytmu
	if (App::getInstance()->getWeightedTardiness() == nullptr) {
		std::cout << "Nalezy najpierw wczytac lub wygenerowac instancje" << std::endl << std::endl;
		std::cout << "Nacisnij dowolny klawisz by zakonczyc..";
		return;
	}
	//dla wszystkich element�w menu
	for (size_t i = 0; i < StateMenuAlgorithms::menuStatusesNames.size(); i++) {
		//zmiana sie_t na enum
		MenuStatuses state = static_cast<MenuStatuses>(i);
		//wy�wietlanie wyr�nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wy�wietlanie tre�ci elementu
		std::cout << StateMenuAlgorithms::menuStatusesNames.at(state) << std::endl;
	}
}

//przetwarzanie wci�ni�tych klawiszy
bool StateMenuAlgorithms::handleInput(char key)
{
	//je�eli brak instancji problemu to dowolny klawisz ma zako�czy� ten stan
	if (App::getInstance()->getWeightedTardiness() == nullptr) {
		return false;
	}

	switch (key)
	{
	//enter -> wykonanie wyr�nionej akcji
	case 13:
		return this->selectOtption();
		break;
	case 'w':
	{
		//przej�cie w g�r� menu
		size_t currentState = static_cast<size_t>(this->currentStatus) - 1;
		if (currentState >= StateMenuAlgorithms::menuStatusesNames.size()) currentState = StateMenuAlgorithms::menuStatusesNames.size() - 1;
		this->currentStatus = static_cast<MenuStatuses>(currentState);
	}
	break;
	case 's':
	{
		//przej�cie w g� menu
		size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
		if (currentState >= StateMenuAlgorithms::menuStatusesNames.size()) currentState = 0;
		this->currentStatus = static_cast<MenuStatuses>(currentState);
	}
	break;
	}
	return true;
}
//akcja po wybraniu opcji
bool StateMenuAlgorithms::selectOtption()
{
	switch (this->currentStatus)
	{
	//odpalanie wybranego algorytmu
	case MenuStatuses::BRUTE_FORCE:
	case MenuStatuses::DYNAMIC_PROGRAMMING:
	case MenuStatuses::B_AND_B_DFS_1:
	case MenuStatuses::B_AND_B_DFS_2:
		App::getInstance()->pushState(new StateRunAlgorithm(this->currentStatus));
		break;
	//powr�t do stanu poprzedniego
	case MenuStatuses::BACK:
		return false;
	}
	//stan nie jest zaka�czany
	return true;
}
