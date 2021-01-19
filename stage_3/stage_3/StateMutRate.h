#pragma once
#include "AState.h"

class StateMutRate : public AState
{
public:
	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);
};

