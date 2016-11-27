#include <Imagine/Graphics.h>
#include <cmath>
#include <iostream>

using namespace Imagine;

//Definition des variables constantes
int const width = 1000;
int const height = 800;
int button = 1;
int nbPoints = 0;
int premierx, premiery;


//////////////////////////////////////////////////////////////////
// Fonction principale
int main()
{
    // Ouverture de la fenetre
    Imagine::openWindow(width,height);

    int x=0, y=0;
    button = Imagine::getMouse(x, y);
    premierx = x;
    premiery = y;
    ++nbPoints;

    int stop = 0;


    while(stop == 0){
        int xprime=200, yprime=100;
        button = Imagine::getMouse(xprime, yprime);
        ++nbPoints;

        if(nbPoints >= 4 && button == 3){
            Imagine::drawLine(premierx, premiery, x, y, Imagine::RED);
            stop=1;
        }

        else{
            Imagine::drawLine(x, y, xprime, yprime, Imagine::RED);
            x=xprime;
            y=yprime;
        }
    }

    Imagine::getMouse(x, y);
	return 0;

}
