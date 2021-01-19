#include "StateMutType.h"
#include <iostream>
#include <map>
#include "App.h"
#include "GeneticAlgorithm.h"

#include "App.h"
//mapowanie typów akcji i nazw wyœwietlanych na ekranie
const std::map<StateMutType::MutationTypes, std::string> StateMutType::crossTypesNames = {
	{StateMutType::MutationTypes::INSERT, "insert"},
	{StateMutType::MutationTypes::TRANSPOSITION, "transposition"},
};


StateMutType::StateMutType()
{
	this->currentStatus = (App::getInstance()->getWeightedTardiness()->mutationFunction == GeneticAlgorithm::insertMutation) ?
		MutationTypes::INSERT : MutationTypes::TRANSPOSITION;
}

//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateMutType::process()
{
	//dla wszystkich opcji
	for (size_t i = 0; i < StateMutType::crossTypesNames.size(); i++) {
		//zmiana size_t na enum
		MutationTypes state = static_cast<MutationTypes>(i);
		//wyœwietlanie wyró¿nienia
		if (this->currentStatus == state) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		//wyœwietlanie treœci elementu
		std::cout << StateMutType::crossTypesNames.at(state) << std::endl;
	}
}

//przetwarzanie wciœniêtych klawiszy
bool StateMutType::handleInput(char key)
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
		if (currentState >= StateMutType::crossTypesNames.size()) currentState = StateMutType::crossTypesNames.size() - 1;
		this->currentStatus = static_cast<MutationTypes>(currentState);
	}
	break;
	case 's':
	{
		//przejœcie w gó³ menu
		size_t currentState = static_cast<size_t>(this->currentStatus) + 1;
		if (currentState >= StateMutType::crossTypesNames.size()) currentState = 0;
		this->currentStatus = static_cast<MutationTypes>(currentState);
	}
	break;
	}
	return true;
}

//akcja po wybraniu opcji
bool StateMutType::selectOtption()
{
	switch (this->currentStatus)
	{
	case MutationTypes::INSERT:
		App::getInstance()->getWeightedTardiness()->mutationFunction = GeneticAlgorithm::insertMutation;
		break;
	case MutationTypes::TRANSPOSITION:
		App::getInstance()->getWeightedTardiness()->mutationFunction = GeneticAlgorithm::transpositionMutation;
		break;
	}
	//stan nie jest zakañczany

	return false;
}
