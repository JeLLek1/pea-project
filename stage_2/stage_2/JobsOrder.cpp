#include "JobsOrder.h"
#include <iostream>
#include "App.h"
#include "WeightedTardiness.h"
//konstruktor
JobsOrder::JobsOrder()
{
	//pocz¹tkowo maksymalna strata to oo
	this->totalLoos = UINT_MAX;
}
//kopiowanie kolejnoœci zadañ i obecnej straty
void JobsOrder::setOrder(std::vector<size_t>* order, unsigned int loos)
{
	//je¿eli by³a ju¿ jakaœ lista trzeba j¹ usun¹æ
	if (this->order != nullptr) {
		delete this->order;
	}
	//kopiowanie zawartoœci przekazanej tablicy kolejnoœci
	this->order = new std::vector<size_t>(*order);
	//strata
	this->totalLoos = loos;
}

//wyœwietlanie
void JobsOrder::display()
{
	if (this->order == nullptr) return;
	//kara
	std::cout << "Sumaryczne wazone opoznienie: " << this->totalLoos << std::endl;
	std::cout << "Kolejnosc wykonywania zadan: " << std::endl;
	//lista zadañ
	WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
	for (auto const& jobIndex : *this->order) {
		std::cout << problem->getJob(jobIndex)->number << " ";
	}
	std::cout << std::endl;
}

JobsOrder::~JobsOrder()
{
	delete order;
}
