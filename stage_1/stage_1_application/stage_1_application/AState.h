#pragma once
class AState
{
public:
	virtual void process() = 0;
	virtual bool handleInput(char key) = 0;
};

