#pragma once
/*
struktura przechowuje dane o zadaniu
*/
struct Job
{
	size_t			number; //numer zadania (s¹ inne ni¿ indeksy w tablicach)
	unsigned int	processingTime, //czas przetwarzania
					expectedEnd, //oczekiwany czas zakoñczenia
					priority; //priorytet
	//konstruktor (przypisanie wszystkich elementów)
	Job(size_t number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority);
	//obliczanie wa¿onej straty danego zadania na podstawie podanego czasu przetworzenia
	unsigned int getWeightedDelay(unsigned int calculationEnd);
};

