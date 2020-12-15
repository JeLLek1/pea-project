#pragma once
/*
klasa abstrakcyjna z metodami u�ywanymi podczas polimorfizmu
*/
class AState
{
public:
	//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
	virtual void process() = 0;
	//przetwarzanie wci�ni�tych klawiszy
	virtual bool handleInput(char key) = 0;
};

