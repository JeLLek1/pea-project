#pragma once
/*
Struktura przechowuje dane dla dynamicznego programowania
*/
struct DbSubset {
	size_t	subIndex = 0, //indeks zadania przej�cia na obecny podzbi�r
			subMask = 0; //maska przej�cia zadania na obecny podzbi�r
	unsigned int	totalPunishment = UINT_MAX, //ca�kowita kara dla obecnego podzbioru
					totalTime=0; //ca�kowity czas przetwarzania dla obecnego podzbioru
};