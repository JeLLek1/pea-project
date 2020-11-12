#pragma once
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za wy�wietlanie struktury
*/
class StateDisplay : public AState
{
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

