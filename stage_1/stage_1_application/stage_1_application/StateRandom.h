#pragma once
#include "AState.h"

class StateRandom : public AState
{
public:
	virtual void process();
	virtual bool handleInput(char key);
};

