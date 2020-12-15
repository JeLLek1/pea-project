#pragma once
#include <string>
#include "AState.h"

class StateShowProblem : public AState
{
public:
	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
};

