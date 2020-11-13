#pragma once
#include <list>
/*
struktura Wierzcho�ka wykorzystywany do metody Branch & Bound
*/
struct JobNode {
	//lista wierzcho�k�w prowadz�cych do obecnego wierzcho�ka
	std::list<size_t>* jobsOrder;
	//przechowuje obecny numer zadania
	size_t current;
	//czas potrzebny do wykonania zada� do obecnej pozycji
	unsigned int time;
	//obecna kara
	unsigned int punishment;
	//ograniczenie g�rne (u�ywane dla Best First)
	unsigned int upperBound;
	//tablica wykorzystanych zada�
	bool* ended;
	
	JobNode(std::list<size_t>* jobsOrder, size_t current, unsigned int time, unsigned int punishment, bool* ended, size_t size, unsigned int upperBound = 0);
	//konstruktor pierwszego wierzcho�ka
	JobNode(size_t size);
	//destruktor
	~JobNode();
};