#pragma once
/*
Struktura przechowuje dane dla dynamicznego programowania
*/
struct DbSubset {
	unsigned int	totalPunishment = UINT_MAX, //ca³kowita kara dla obecnego podzbioru
					totalTime=0; //ca³kowity czas przetwarzania dla obecnego podzbioru
};