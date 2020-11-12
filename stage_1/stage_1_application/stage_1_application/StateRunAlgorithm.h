#pragma once
#include "AState.h"
#include "StateMenuAlgorithms.h"

class StateRunAlgorithm : public AState
{
	StateMenuAlgorithms::MenuStatuses state;
public:
	StateRunAlgorithm(StateMenuAlgorithms::MenuStatuses state);
	virtual void process();
	virtual bool handleInput(char key);
};

