#pragma once
/*
struktura przechowuje dane o zadaniu
*/
struct Job
{
	unsigned int	number, //numer zadania (s¹ inne ni¿ indeksy w tablicach)
					processingTime, //czas przetwarzania
					expectedEnd, //oczekiwany czas zakoñczenia
					priority; //priorytet
	//konstruktor (przypisanie wszystkich elementów)
	Job(unsigned int number, unsigned int processingTime, unsigned int expectedEnd, unsigned int priority);
	//obliczanie wa¿onej straty danego zadania na podstawie podanego czasu przetworzenia
	unsigned int getWeightedDelay(unsigned int calculationEnd);
};

