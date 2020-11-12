#include "StateDisplay.h"
#include <iostream>
#include "App.h"

void StateDisplay::process()
{
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

bool StateDisplay::handleInput(char key)
{
    return false;
}
