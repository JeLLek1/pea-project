#pragma once
#include <list>
/*
struktura Wierzcho³ka wykorzystywany do metody Branch & Bound
*/
struct JobNode {
	//lista wierzcho³ków prowadz¹cych do obecnego wierzcho³ka
	std::list<size_t>* jobsOrder;
	//przechowuje obecny numer zadania
	size_t current;
	//czas potrzebny do wykonania zadañ do obecnej pozycji
	unsigned int time;
	//obecna kara
	unsigned int punishment;
	//ograniczenie górne (u¿ywane dla Best First)
	unsigned int upperBound;
	//tablica wykorzystanych zadañ
	bool* ended;
	
	JobNode(std::list<size_t>* jobsOrder, size_t current, unsigned int time, unsigned int punishment, bool* ended, size_t size, unsigned int upperBound = 0);
	//konstruktor pierwszego wierzcho³ka
	JobNode(size_t size);
	//destruktor
	~JobNode();
};