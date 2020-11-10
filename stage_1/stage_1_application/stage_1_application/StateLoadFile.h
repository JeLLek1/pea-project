#pragma once
#include <string>
#include "AState.h"
class StateLoadFile : public AState
{
	bool loadFile(std::string name);
public:
	virtual void process();
	virtual bool handleInput(char key);
};

