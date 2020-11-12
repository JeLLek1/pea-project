#pragma once
#include "AState.h"

class StateDisplay : public AState
{
public:
	virtual void process();
	virtual bool handleInput(char key);
};

