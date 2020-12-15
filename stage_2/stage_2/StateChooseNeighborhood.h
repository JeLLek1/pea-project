#pragma once
#include "AState.h"
#include "ANeighborhood.h"

class StateChooseNeighborhood : public AState
{
private:
	// obecnie wyró¿niony typ sasiedztwa
	NeigborhoodTypes currentType = NeigborhoodTypes::EXCHANGE;

public:
	StateChooseNeighborhood();

	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);

	void selectOption();
};

