#pragma once
/*
Struktura przechowuje dane dla dynamicznego programowania
*/
struct DbSubset {
	unsigned int	totalPunishment = UINT_MAX, //ca�kowita kara dla obecnego podzbioru
					totalTime=0; //ca�kowity czas przetwarzania dla obecnego podzbioru
};