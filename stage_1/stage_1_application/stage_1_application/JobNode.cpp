#include "JobNode.h"

JobNode::JobNode(std::list<size_t>* jobsOrder, size_t current, unsigned int time, unsigned int punishment, bool* ended, size_t size, unsigned int upperBound)
{
	//zapisanie obecnego wierzcho³ka
	this->current = current;
	//zapisanie czasu potrzebnego do zakoñczenia
	this->time = time;
	//zapisanie obecnej kary
	this->punishment = punishment;
	//skopiowanie listy kolejnoœci wierzcho³ków i dodanie na koniec obecnego
	this->jobsOrder = new std::list<size_t>(*jobsOrder);
	this->jobsOrder->push_back(current);
	//tablica z informacj¹, które elementy s¹ ju¿ dodane
	this->ended = new bool[size];
	std::copy(ended, ended +size, this->ended);
	this->ended[current] = true;
	//wyliczone górne ograniczenie
	this->upperBound = upperBound;
}
//konstruktor pierwszego wierzcho³ka
JobNode::JobNode(size_t size)
{
	//pusta lista kolejnoœci zadañ
	this->jobsOrder = new std::list<size_t>();
	//obecny wierzcho³ek nas nie obchodzi
	this->current = 0;
	//czas jest na pocz¹tku równy 0
	this->time = 0;
	//kara na pocz¹tku jest równa 0
	this->punishment = 0;
	//tablica odwiedzonych wierzcho³ków jest pusta
	this->ended = new bool[size];
	std::fill(this->ended, this->ended + size, 0);
	//górne ograniczenie (w pierwszym wierzcho³ku jest niewa¿ne)
	this->upperBound = 0;
}

JobNode::~JobNode()
{
	delete this->jobsOrder;
	delete[] this->ended;
}
