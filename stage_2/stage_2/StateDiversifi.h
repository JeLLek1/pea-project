#pragma once
#include <map>
#include <string>
#include "AState.h"

class StateDiversifi : public AState
{
	bool currentChoose;
	static const std::map<bool, std::string> chooseNames;
public:
	StateDiversifi();
	// przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process();
	// przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key);

	void selectOtption();
};

