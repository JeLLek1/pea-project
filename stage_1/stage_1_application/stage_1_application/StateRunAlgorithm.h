#pragma once
#include "AState.h"
#include "StateMenuAlgorithms.h"
/*
Klasa stanu aplikacji odpowiedzialnego za uruchomienie odpowiedniego algorytmu
*/
class StateRunAlgorithm : public AState
{
	//przechowywany wybrany algorytm
	StateMenuAlgorithms::MenuStatuses state;
public:
	//inny konstruktor (z danym typem algorytmu)
	StateRunAlgorithm(StateMenuAlgorithms::MenuStatuses state);
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

