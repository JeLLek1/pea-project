#include "StateMainMenu.h"
#include <iostream>
#include "App.h"
#include "StateLoadFile.h"
#include "StateShowProblem.h"
#include "StateRunAlgorithm.h"
#include "StateStopCrit.h"
#include "StatePopSize.h"
#include "StateMutRate.h"
#include "StateCrossRate.h"
#include "StateMutType.h"
#include "StateCrossType.h"
#include "StateTests.h"

//mapowanie typów akcji i nazw wyœwietlanych na ekranie
const std::map<StateMainMenu::MenuStatuses, std::string> StateMainMenu::menuStatusesNames = {
	{MenuStatuses::LOAD_FILE, "Wczytaj plik"},
	{MenuStatuses::SHOW_PROBLEM, "Wyswietl problem"},
	{MenuStatuses::STOP_CRIT, "Wprowadz kryterium stopu"},
	{MenuStatuses::POP_SIZE, "Wprowadz wielkosc populacji poczatkowej"},
	{MenuStatuses::MUT_RATE, "Wprowadz wspolczynnik mutacji"},
	{MenuStatuses::CROSS_RATE, "Wprowadz wspolczynnik krzyzowania"},
	{MenuStatuses::MUT_TYPE, "Wybierz typ mutacji"},
	{MenuStatuses::CROS_TYPE, "Wybierz typ krzyzowania"},
	{MenuStatuses::RUN_ALGORITHM, "Uruchom algorytm"},
	{MenuStatuses::RUN_TESTS, "Uruchom testy algorytmu"},
	{MenuStatuses::EXIT, "Zakoncz program"}
};

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateMainMenu::process()
{
	//dla wszystkich opcji
	for (size_t i = 0; i < StateMainMenu::menuStatusesNames.size(); i++) {
		//zmiana size_t na enum
		MenuStatuses state = static_cast<MenuStatuses>(i);
		//wyœwietlanie wyró¿nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wyœwietlanie treœci elementu
		std::cout << StateMainMenu::menuStatusesNames.at(state) << std::endl;
	}
}
//przetwarzanie wciœniêtych klawiszy
bool StateMainMenu::handleInput(char key)
{
	switch (key)
	{
	//enter -> wykonanie wyró¿nionej akcji
	case 13:
		return this->selectOtption();
		break;
	case 'w':
		{
			//przejœcie w górê menu
			size_t currentState = static_cast<size_t>(this->currentStatus) - 1;
			if (currentState >= StateMainMenu::menuStatusesNames.size()) currentState = StateMainMenu::menuStatusesNames.size() - 1;
			this->currentStatus = static_cast<MenuStatuses>(currentState);
		}
		break;
	case 's':
		{
			//przejœcie w gó³ menu
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
	case MenuStatuses::POP_SIZE:
		App::getInstance()->pushState(new StatePopSize());
		break;
	case MenuStatuses::MUT_RATE:
		App::getInstance()->pushState(new StateMutRate());
		break;
	case MenuStatuses::CROSS_RATE:
		App::getInstance()->pushState(new StateCrossRate());
		break;
	case MenuStatuses::MUT_TYPE:
		App::getInstance()->pushState(new StateMutType());
		break;
	case MenuStatuses::CROS_TYPE:
		App::getInstance()->pushState(new StateCrossType());
		break;
	case MenuStatuses::RUN_ALGORITHM:
		App::getInstance()->pushState(new StateRunAlgorithm());
		break;
	case MenuStatuses::RUN_TESTS:
		App::getInstance()->pushState(new StateTests());
		break;
	case MenuStatuses::EXIT:
		return false;
	}
	//stan nie jest zakañczany
	return true;
}
