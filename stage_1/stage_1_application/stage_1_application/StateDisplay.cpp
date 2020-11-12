#include "StateDisplay.h"
#include <iostream>
#include "App.h"
//przetwarzanie rz�da� i wy�wietlanie informacji na ekranie
void StateDisplay::process()
{
    //wy�wietlanie problemu lub komunikat o braku wygenerowanej struktury
    WeightedTardiness* problem = App::getInstance()->getWeightedTardiness();
    if (problem == nullptr) {
        std::cout << "Nalezy najpierw wczytac lub wygenerowac strukture" << std::endl;
    }
    else {
        std::cout << "Przechowywana struktura: " << std::endl << std::endl;
        problem->display();
    }
    
    std::cout << std::endl << "Nacisnij dowolny klawisz by zakonczyc..";
}
//przetwarzanie wci�ni�tych klawiszy
bool StateDisplay::handleInput(char key)
{
    //zawsze ma si� zako�czy� po wci�ni�ciu klawisza
    return false;
}
