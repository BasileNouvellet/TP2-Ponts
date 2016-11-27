// Imagine++ project
// Project:  Tennis
// Author:   renaud
// Date:     2007/10/9
// TP #2 du cours de C++ de l'ENPC

#include <Imagine/Graphics.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace Imagine;

//////////////////////////////////////////////////////////////////
// Fonction de gestion du clavier
// Pour l'instant, utiliser sans se soucier du fontionnement
// Retourne dans sens1 (resp. sens2) -1, 1 ou 0 pour le joueur 1
// (resp. joueur 2) suivant qu'il appuie sur la touche gauche,
// droite ou sur aucune touche.

//Défintion des variables constantes
const int width = 1000;
const int height = 1000;
const int ball_size = 28;
const int longueurRaquette = 200;
const int epaisseurRaquette = 50;
//Définition des variables de points
int scoreJoueur1=0, scoreJoueur2=0;

void DessineBalle (int x, int y, Color col){
    // Affichage de la balle
    fillRect(x,y,ball_size,ball_size,RED);
    // Temporisation
    milliSleep(20);
    // Effacement de la balle
    fillRect(x,y,ball_size,ball_size,WHITE);
}

bool BougeBalle (int& x, int& y, int&u, int&v, int rx1, int ry1, int rx2, int ry2){

    // Rebond
    if (x+u>(width-(ball_size/2)))
        u=-u;
    if (y+v>(height-(ball_size/2)))
        v=-v;
    if (y+v<ball_size)
        v=-v;
    if (x+u<ball_size)
        u=-u;
    if (x+u>rx1 && x+u<(rx1+longueurRaquette) && y+v<1+epaisseurRaquette+ball_size)
        v=-v;
    if (x+u>rx2 && x+u<(rx2+longueurRaquette) && y+v>height-epaisseurRaquette-1)
        v=-v;

    if ((x+u<rx1 || x+u>(rx1+longueurRaquette)) && y+v<epaisseurRaquette){
        ++scoreJoueur2;
        cout <<scoreJoueur1 <<" - " <<scoreJoueur2 <<endl;
        return false;
    }
    if ((x+u<rx2 || x+u>(rx2+longueurRaquette)) && y+v>height-epaisseurRaquette){
        ++scoreJoueur1;
        cout <<scoreJoueur1 <<" - " <<scoreJoueur2 <<endl;
        return false;
    }
    // Mise a jour de la position de la balle
    x+=u;
    y+=v;

    return true;
}

void DessineRaquette (int rx1, int ry1, int rx2, int ry2, Color col){
    fillRect(rx1,ry1,longueurRaquette,epaisseurRaquette, GREEN);
    fillRect(rx2,ry2,longueurRaquette,epaisseurRaquette, BLUE);


}

void Clavier (int& sens1, int& sens2) {
	static bool left1=false,right1=false,left2=false,right2=false;
	Event e;
	do {
		getEvent(0,e);
		if (e.type==EVT_KEY_ON || e.type==EVT_KEY_OFF) {
			bool push=(e.type==EVT_KEY_ON);
			switch (e.key) {
                case 's':
					left1=push;
					break;
                case 'd':
					right1=push;
					break;
                case 'k':
					left2=push;
					break;
                case 'l':
					right2=push;
					break;
			}
		}
	} while (e.type!=EVT_NONE);
	sens1=(left1?-1:(right1?1:0));
	sens2=(left2?-1:(right2?1:0));
}

void BougeRaquette (int& x, int sens){
    //Defintion des crans de déplacements
    if (sens==1)
        sens=10;
    else if (sens==0)
        sens=0;
    else
        sens=-10;

    if (x+sens+longueurRaquette<width && x+sens>0){
        x+=sens;

    }

}

//////////////////////////////////////////////////////////////////
// Fonction principale
int main()
{
    // Ouverture de la fenetre
    openWindow(width,height);

    while (true) {
    //Définitions des variables des raquettes
    int rx1=width/2, ry1=1, rx2=width/2, ry2=height-epaisseurRaquette-1;

    cout <<"------------- SCORES -------------" <<endl <<endl <<endl;
    cout <<"Joueur 1 - Joueur 2" <<endl <<endl;



	// Position et vitesse de la balle
    int xb=100,
        yb=100,
        ub=10,
        vb=5;

    //Initialisation clavier
    int sens1 = 0,sens2 = 0;

	// Boucle principale
	while (true) {


        Clavier(sens1,sens2);
        BougeRaquette(rx1,sens1);
        BougeRaquette(rx2,sens2);

        DessineRaquette(rx1,ry1,rx2,ry2,GREEN);

        if(BougeBalle(xb,yb,ub,vb,rx1,ry1,rx2,ry2)==false)
            break;
        DessineBalle(xb-ball_size,yb-ball_size,BLACK);
        fillRect(rx1,ry1,longueurRaquette,epaisseurRaquette, WHITE);
        fillRect(rx2,ry2,longueurRaquette,epaisseurRaquette, WHITE);
	}
    fillRect(rx1,ry1,longueurRaquette,epaisseurRaquette, WHITE);
    fillRect(rx2,ry2,longueurRaquette,epaisseurRaquette, WHITE);
   }
	endGraphics();
	return 0;

}
