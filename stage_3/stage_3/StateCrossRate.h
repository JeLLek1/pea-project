#pragma once
#include "AState.h"

class StateCrossRate : public AState
{
public:
	// przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);
};

