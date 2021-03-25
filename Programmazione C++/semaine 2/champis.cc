#include<iostream>
#include <string>
using namespace std;


int main(){

    //Initialisation des variables
    string champi = "";
    bool foret = false;
    bool lamelles = false;
    bool anneau = false;


    cout << "Pensez a un champignon : amanite tue mouches, pied bleu, girolle," << endl;
    cout << "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl;

    cout << "Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ";
    bool convexe;
    cin >> convexe;

    if(convexe){
        cout << "Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ";
        cin >> foret;

        if(foret){
            cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
            cin >> anneau;

            if(anneau){
                champi = "l'amanite tue-mouches";
            }else{
                champi = "le pied bleu";
            }
        }else{
            champi = "l'agaric jaunissant";
        }

    }else{
        cout << "Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ";
        cin >> anneau;

        if(anneau){
            champi = "le coprin chevelu";
        }else{
            cout << "Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ";
            cin >> lamelles;

            if(lamelles){
                champi = "la girolle";
            }else{
                champi = "le cèpe de Bordeaux";
            }
        }
    }

    cout << "==> Le champignon auquel vous pensez est ";
    cout << champi;

    return 0;
}