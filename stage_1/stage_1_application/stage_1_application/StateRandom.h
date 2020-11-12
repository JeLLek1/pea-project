#pragma once
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za generowanie struktury
*/
class StateRandom : public AState
{
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

