#pragma once
/*
klasa abstrakcyjna z metodami u¿ywanymi podczas polimorfizmu
*/
class AState
{
public:
	//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
	virtual void process() = 0;
	//przetwarzanie wciœniêtych klawiszy
	virtual bool handleInput(char key) = 0;
};

