#pragma once
/*
struktura przechowuje dane o zadaniu
*/
struct Job
{
	unsigned int	number, //numer zadania (s� inne ni� indeksy w tablicach)
					processingTime, //czas przetwarzania
					expectedEnd, //oczekiwany czas zako�czenia
					priority; //priorytet
	//konstruktor (przypisanie wszystkich element�w)
	Job(unsigned int number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority);
	//obliczanie wa�onej straty danego zadania na podstawie podanego czasu przetworzenia
	unsigned int getWeightedDelay(unsigned int calculationEnd);
};

