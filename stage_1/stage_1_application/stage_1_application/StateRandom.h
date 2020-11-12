#pragma once
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za generowanie struktury
*/
class StateRandom : public AState
{
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
};

