#include "JobNode.h"

JobNode::JobNode(std::list<size_t>* jobsOrder, size_t current, unsigned int time, unsigned int punishment, bool* ended, size_t size, unsigned int upperBound)
{
	//zapisanie obecnego wierzcho�ka
	this->current = current;
	//zapisanie czasu potrzebnego do zako�czenia
	this->time = time;
	//zapisanie obecnej kary
	this->punishment = punishment;
	//skopiowanie listy kolejno�ci wierzcho�k�w i dodanie na koniec obecnego
	this->jobsOrder = new std::list<size_t>(*jobsOrder);
	this->jobsOrder->push_back(current);
	//tablica z informacj�, kt�re elementy s� ju� dodane
	this->ended = new bool[size];
	std::copy(ended, ended +size, this->ended);
	this->ended[current] = true;
	//wyliczone g�rne ograniczenie
	this->upperBound = upperBound;
}
//konstruktor pierwszego wierzcho�ka
JobNode::JobNode(size_t size)
{
	//pusta lista kolejno�ci zada�
	this->jobsOrder = new std::list<size_t>();
	//obecny wierzcho�ek nas nie obchodzi
	this->current = 0;
	//czas jest na pocz�tku r�wny 0
	this->time = 0;
	//kara na pocz�tku jest r�wna 0
	this->punishment = 0;
	//tablica odwiedzonych wierzcho�k�w jest pusta
	this->ended = new bool[size];
	std::fill(this->ended, this->ended + size, 0);
	//g�rne ograniczenie (w pierwszym wierzcho�ku jest niewa�ne)
	this->upperBound = 0;
}

JobNode::~JobNode()
{
	delete this->jobsOrder;
	delete[] this->ended;
}
