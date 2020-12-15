#pragma once
#include <string>
#include "AState.h"

class StateShowProblem : public AState
{
public:
	// przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

