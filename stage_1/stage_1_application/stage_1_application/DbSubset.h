#pragma once
/*
Struktura przechowuje dane dla dynamicznego programowania
*/
struct DbSubset {
	size_t	subIndex = 0, //indeks zadania przejœcia na obecny podzbiór
			subMask = 0; //maska przejœcia zadania na obecny podzbiór
	unsigned int	totalPunishment = UINT_MAX, //ca³kowita kara dla obecnego podzbioru
					totalTime=0; //ca³kowity czas przetwarzania dla obecnego podzbioru
};