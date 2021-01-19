#pragma once
#include <string>
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za wczytywanie plik�w problem�w
*/
class StateLoadFile : public AState
{
public:
	//wczytywanie pliku
	static bool loadFile(std::string name);
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

