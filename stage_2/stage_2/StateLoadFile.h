#pragma once
#include <string>
#include "AState.h"
/*
Klasa stanu aplikacji odpowiedzialnego za wczytywanie plików problemów
*/
class StateLoadFile : public AState
{
public:
	//wczytywanie pliku
	static bool loadFile(std::string name);
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
};

