#include <iostream>
using namespace std;

int main()
{
  cout << "Donnez l'heure de début de la location (un entier) : ";
  int debut;
  cin >> debut;

  cout << "Donnez l'heure de fin de la location (un entier) : ";
  int fin;
  cin >> fin;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  bool correctHours = true;

  if(debut < 0 || debut > 24 || fin < 0 || fin > 24) {
      correctHours = false;
      cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
  }else if(debut == fin) {
      correctHours = false;
      cout << "Bizarre, vous n'avez pas loué votre vélo bien longtemps !" << endl;
  }else if(debut > fin){
      correctHours = false;
      cout << "Bizarre, le début de la location est après la fin ..." << endl;
  }

  if(correctHours){
      double prix1 = 1.0, prix2 = 2.0, prix_total = 0.0;
      int duree1 = 0, duree2 = 0;

      bool firstHour = (debut >= 0 && debut <= 7);
      bool secondHour = (debut >= 7 && debut <= 17);
      bool thirdHour = (debut >= 17 && debut <= 24);

      if(firstHour) {
          if(fin >= 0 && fin <= 7) {
              duree1 = fin - debut;
          }else if(fin >= 7 && fin <= 17) {
              duree1 = 7 - debut;
              duree2 = fin - 7;
          }else {
              duree1 = 7 - debut + fin - 17;
              duree2 = 10;
          }
      }

      if(secondHour) {
          if(fin >= 17 && fin <= 24) {
              duree1 = fin - 17;
              duree2 = 17 - debut;
          }else {
              duree2 = fin - debut;
          }
      }

      if(thirdHour) {
          duree1 = fin - debut;
      }

      cout << "Vous avez loué votre vélo pendant" << endl;

      if(duree1 != 0) {
          cout << duree1 << " heure(s) au tarif horaire de " << prix1
               << " franc(s)" << endl;
      }

      if(duree2 != 0) {
          cout << duree2 << " heure(s) au tarif horaire de " << prix2
               << " franc(s)" << endl;
      }

      prix_total = (duree1 * prix1) + (duree2 * prix2);
      cout << "Le montant total à payer est de " << prix_total
           << " franc(s)." << endl;
  }

  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
