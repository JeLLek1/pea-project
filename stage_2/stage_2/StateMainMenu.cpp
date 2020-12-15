#include "StateMainMenu.h"
#include <iostream>
#include "App.h"
#include "StateLoadFile.h"
#include "StateShowProblem.h"
#include "StateRunAlgorithm.h"
#include "StateStopCrit.h"
#include "StateDiversifi.h"
#include "StateChooseNeighborhood.h"

//mapowanie typ�w akcji i nazw wy�wietlanych na ekranie
const std::map<StateMainMenu::MenuStatuses, std::string> StateMainMenu::menuStatusesNames = {
	{MenuStatuses::LOAD_FILE, "Wczytaj plik"},
	{MenuStatuses::SHOW_PROBLEM, "Wyswietl problem"},
	{MenuStatuses::STOP_CRIT, "Wprowadz kryterium stopu"},
	{MenuStatuses::DIVERSIFI, "Wlacz / wylacz dywersyfikacje"},
	{MenuStatuses::NEIGHORHOOD, "Wybierz typ sasiedztwa"},
	{MenuStatuses::RUN_ALGORITHM, "Uruchom algorytm"},
	{MenuStatuses::EXIT, "Zakoncz program"}
};

//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateMainMenu::process()
{
	//dla wszystkich opcji
	for (size_t i = 0; i < StateMainMenu::menuStatusesNames.size(); i++) {
		//zmiana size_t na enum
		MenuStatuses state = static_cast<MenuStatuses>(i);
		//wy�wietlanie wyr�nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wy�wietlanie tre�ci elementu
		std::cout << StateMainMenu::menuStatusesNames.at(state) << std::endl;
	}
}
//przetwarzanie wci�ni�tych klawiszy
bool StateMainMenu::handleInput(char key)
{
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
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = StateMainMenu::menuStatusesNames.size() - 1;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	case 's':
		{
			//przej�cie w g� menu
			size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = 0;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	}
	return true;
}
//akcja po wybraniu opcji
bool StateMainMenu::selectOtption()
{
	switch (this->currentStatus)
	{
	case MenuStatuses::LOAD_FILE:
		App::getInstance()->pushState(new StateLoadFile());
		break;
	case MenuStatuses::SHOW_PROBLEM:
		App::getInstance()->pushState(new StateShowProblem());
		break;
	case MenuStatuses::STOP_CRIT:
		App::getInstance()->pushState(new StateStopCrit());
		break;
	case MenuStatuses::DIVERSIFI:
		App::getInstance()->pushState(new StateDiversifi());
		break;
	case MenuStatuses::NEIGHORHOOD:
		App::getInstance()->pushState(new StateChooseNeighborhood());
		break;
	case MenuStatuses::RUN_ALGORITHM:
		App::getInstance()->pushState(new StateRunAlgorithm());
		break;
	case MenuStatuses::EXIT:
		return false;
	}
	//stan nie jest zaka�czany
	return true;
}
