#include "StateDisplay.h"
#include <iostream>
#include "App.h"
//przetwarzanie rz¹dañ i wyœwietlanie informacji na ekranie
void StateDisplay::process()
{
    //wyœwietlanie problemu lub komunikat o braku wygenerowanej struktury
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
//przetwarzanie wciœniêtych klawiszy
bool StateDisplay::handleInput(char key)
{
    //zawsze ma siê zakoñczyæ po wciœniêciu klawisza
    return false;
}
