/*===============================
* Autor: Maciej Bronikowski
* Numer indeksu: 248838
* Teamat: Jednoprocesorowy problem szeregowania zadań przy kryterium minimalizacji ważonej sumy opóźnień zadań 
* Etap: 1
* ===============================*/
#include "App.h"
#include "StateMainMenu.h"
int main()
{
	//pobranie instancji aplikacji
	App* app = App::getInstance();
	//dodanie głównego menu jako obecny stan aplikacji
	app->pushState(new StateMainMenu());
	//uruchomienie pętli głównej
	app->loop();

	return 0;
}
