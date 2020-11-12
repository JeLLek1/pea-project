#pragma once
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za wyœwietlanie struktury
*/
class StateDisplay : public AState
{
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
};

