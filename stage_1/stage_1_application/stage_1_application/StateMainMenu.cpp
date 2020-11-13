#include "StateMainMenu.h"
#include <iostream>
#include "App.h"
#include "StateLoadFile.h"
#include "StateRandom.h"
#include "StateDisplay.h"
#include "StateMenuAlgorithms.h"
#include "StateTimeTests.h"

//mapowanie typów akcji i nazw wyœwietlanych na ekranie
const std::map<StateMainMenu::MenuStatuses, std::string> StateMainMenu::menuStatusesNames = {
	{MenuStatuses::LOAD_FILE, "Wczytaj plik"},
	{MenuStatuses::RANDOM_GENERATE, "Wygeneruj losowe dane"},
	{MenuStatuses::DISPLAY_DATA, "Wyswietl dane na ekranie"},
	{MenuStatuses::RUN_ALGORITHM, "Wybierz i wykonaj algorytm"},
	{MenuStatuses::TIME_TESTS, "Uruchom testy czasu dzialania"},
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
		//stan wczytywania pliku
		App::getInstance()->pushState(new StateLoadFile());
		break;
	case MenuStatuses::RANDOM_GENERATE:
		//stan generowania struktury
		App::getInstance()->pushState(new StateRandom());
		break;
	case MenuStatuses::DISPLAY_DATA:
		//stan wyœwietlania struktury
		App::getInstance()->pushState(new StateDisplay());
		break;
	case MenuStatuses::RUN_ALGORITHM:
		//stan menu algorytmu
		App::getInstance()->pushState(new StateMenuAlgorithms());
		break;
	case MenuStatuses::TIME_TESTS:
		//stan testów czasowych
		App::getInstance()->pushState(new StateTimeTests());
		break;
	case MenuStatuses::EXIT:
		//zakoñczenie obecnego stanu
		return false;
	}
	//stan nie jest zakañczany
	return true;
}
