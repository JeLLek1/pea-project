#include "StateDiversifi.h"
#include <iostream>
#include <conio.h>
#include "App.h"

//mapowanie typów akcji i nazw wyœwietlanych na ekranie
const std::map<bool, std::string> StateDiversifi::chooseNames = {
    {false, "Wylacz"},
    {true, "Wlacz"},
};

StateDiversifi::StateDiversifi() : AState()
{
    this->currentChoose = App::getInstance()->getWeightedTardiness()->getDiversification();
}

void StateDiversifi::process()
{
    std::cout << "Kryterium dywersyfikacji\n\n";
    std::map<bool, std::string>::iterator it;
    for (auto const& x : StateDiversifi::chooseNames)
    {
        if (this->currentChoose == x.first) {
            std::cout << " -> ";
        }
        else {
            std::cout << "    ";
        }
        std::cout << x.second << std::endl;
    }
}

bool StateDiversifi::handleInput(char key)
{
    switch (key)
    {
        //enter -> wykonanie wyró¿nionej akcji
    case 13:
        this->selectOtption();
        return false;
    case 'w':
    case 's':
        this->currentChoose = !this->currentChoose;
        break;
    }

    return true;
}

void StateDiversifi::selectOtption()
{
    App::getInstance()->getWeightedTardiness()->setDiversification(this->currentChoose);
}
