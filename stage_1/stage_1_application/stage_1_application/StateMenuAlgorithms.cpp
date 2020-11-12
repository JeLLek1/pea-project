#include "StateMenuAlgorithms.h"
#include <iostream>
#include "App.h"
#include "StateRunAlgorithm.h"
#include "JobsOrder.h"

const std::map<StateMenuAlgorithms::MenuStatuses, std::string> StateMenuAlgorithms::menuStatusesNames = {
	{MenuStatuses::BRUTE_FORCE, "Przeglad zupelny"},
	{MenuStatuses::DYNAMIC_PROGRAMMING, "Programowanie dynamiczne"},
	{MenuStatuses::B_AND_B_1, "B & B pierwsza strategia"},
	{MenuStatuses::B_AND_B_2, "B & B druga strategia"},
	{MenuStatuses::BACK, "Powrot"},
};

void StateMenuAlgorithms::process()
{
	if (App::getInstance()->getWeightedTardiness() == nullptr) {
		std::cout << "Nalezy najpierw wczytac lub wygenerowac instancje" << std::endl << std::endl;
		std::cout << "Nacisnij dowolny klawisz by zakonczyc..";
		return;
	}
	for (size_t i = 0; i < StateMenuAlgorithms::menuStatusesNames.size(); i++) {
		MenuStatuses state = static_cast<MenuStatuses>(i);
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		std::cout << StateMenuAlgorithms::menuStatusesNames.at(state) << std::endl;
	}
}

bool StateMenuAlgorithms::handleInput(char key)
{
	if (App::getInstance()->getWeightedTardiness() == nullptr) {
		return false;
	}

	switch (key)
	{
	case 13:
		return this->selectOtption();
		break;
	case 'w':
	{
		size_t currentState = static_cast<size_t>(this->currentStatus) - 1;
		if (currentState >= StateMenuAlgorithms::menuStatusesNames.size()) currentState = StateMenuAlgorithms::menuStatusesNames.size() - 1;
		this->currentStatus = static_cast<MenuStatuses>(currentState);
	}
	break;
	case 's':
	{
		size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
		if (currentState >= StateMenuAlgorithms::menuStatusesNames.size()) currentState = 0;
		this->currentStatus = static_cast<MenuStatuses>(currentState);
	}
	break;
	}
	return true;
}

bool StateMenuAlgorithms::selectOtption()
{
	switch (this->currentStatus)
	{
	case MenuStatuses::BRUTE_FORCE:
	case MenuStatuses::DYNAMIC_PROGRAMMING:
	case MenuStatuses::B_AND_B_1:
	case MenuStatuses::B_AND_B_2:
		App::getInstance()->pushState(new StateRunAlgorithm(this->currentStatus));
		break;
	case MenuStatuses::BACK:
		return false;
	}
	return true;
}
