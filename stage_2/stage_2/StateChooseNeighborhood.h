#pragma once
#include "AState.h"
#include "ANeighborhood.h"

class StateChooseNeighborhood : public AState
{
private:
	// obecnie wyr�niony typ sasiedztwa
	NeigborhoodTypes currentType = NeigborhoodTypes::EXCHANGE;

public:
	StateChooseNeighborhood();

	// przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key);

	void selectOption();
};

