#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
  // Réduire le format d'affichage
  cout << setprecision(4);

  // Paramètres
  double taux_croissance_lapins(0.3);
  double taux_attaque(0.01);
  double taux_croissance_renards(0.008);
  double taux_mortalite(0.1);
  int duree(50);

  double renards_i(0.0);
  double lapins_i(0.0);

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  // ===== PARTIE 1 =====
  // Saisie des populations initiales

  do{
      cout << "Combien de renards au départ (>= 2) ? ";
      cin >> renards_i;
    }while(renards_i < 2.0);

  do{
      cout << "Combien de lapins au départ  (>= 5) ? ";
      cin >> lapins_i;
    }while(lapins_i < 5.0);

  // ===== PARTIE 2 =====
  // Première simulation
  double croissance_lapins = 0.0;
  double croissance_renards = 0.0;
  double nb_lapins_1 = lapins_i;
  double nb_renards_1 = renards_i;

  cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque * 100 << "%" <<  endl;

  for(int i = 1; i<=duree ;i++){
      croissance_lapins = (nb_lapins_1 * (1.0 + (taux_croissance_lapins) - (taux_attaque * nb_renards_1)));
      croissance_renards = (nb_renards_1 * (1.0 + (taux_attaque * nb_lapins_1 * taux_croissance_renards) - taux_mortalite));

      nb_lapins_1 = croissance_lapins;
      nb_renards_1 = croissance_renards;

      if(nb_renards_1 < 0.0){
          nb_renards_1 = 0.0;
      }

      if(nb_lapins_1 < 0.0){
          nb_lapins_1 = 0.0;
      }

      cout <<"Après "<< i << " mois, " <<"il y a " << nb_lapins_1
      << " lapins " << "et " << nb_renards_1 << " renards " << endl;
    }


  // ===== PARTIE 3 =====
  // Variation du taux d'attaque
  cout << endl;

  double taux_attaque_initial = 0.0;
  double taux_attaque_final = 0.0;
  double nb_lapins_2 = lapins_i;
  double nb_renards_2 = renards_i;
  int k_mois = 0;

  croissance_lapins = 0.0;
  croissance_renards = 0.0;

  do{
      cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
      cin >> taux_attaque_initial;
    }while(taux_attaque_initial < 0.5 || taux_attaque_initial > 6);

  do{
      cout << "taux d'attaque à la fin  en % (entre ";
      cout << taux_attaque_initial << " et 6) ? ";
      cin >> taux_attaque_final;

    }while(taux_attaque_final < taux_attaque_initial || taux_attaque_final > 6);

  taux_attaque_initial /= 100.0f;
  taux_attaque_final /= 100.0f;

  while(taux_attaque_initial < taux_attaque_final) {

       cout <<  endl << "***** Le taux d'attaque vaut "<< taux_attaque_initial * 100 << "%" <<  endl;

      bool lapins_extinction(false);
      bool renards_extinction(false);
      bool lapins_disparus(false);
      bool renards_disparus(false);
      bool est_remontee(false);
      bool disparition_total(false);

      for(k_mois = 0; !disparition_total && (k_mois < duree); k_mois++){

          croissance_lapins = (nb_lapins_2*(1.0 + (taux_croissance_lapins) - (taux_attaque_initial * nb_renards_2)));
          croissance_renards = (nb_renards_2*(1.0 + (taux_attaque_initial * nb_lapins_2 * taux_croissance_renards) - taux_mortalite));

          nb_lapins_2 = croissance_lapins;
          nb_renards_2 = croissance_renards;

          if(nb_lapins_2 >= 2 && nb_lapins_2 < 5){
              lapins_extinction = true;
          }else if(nb_renards_2 >= 2 && nb_renards_2 < 5){
              renards_extinction = true;
          }

          if(nb_renards_2 < 2){
              nb_renards_2 = 0.0;
              renards_disparus = true;
          }else if(nb_lapins_2 < 2){
              nb_lapins_2 = 0.0;
              lapins_disparus = true;
          }

          if((renards_extinction && nb_renards_2 > 5) || (lapins_extinction && nb_lapins_2 > 5)){
              est_remontee = true;
          }

          if(nb_lapins_2 == 0 && nb_renards_2 == 0) {
              disparition_total = true;
          }

        }


      cout <<"Après "<< k_mois << " mois, " <<"il y a " << nb_lapins_2
      << " lapins" << " et " << nb_renards_2 << " renards" << endl;

      if(renards_extinction){
        cout << "Les renards ont été en voie d'extinction" << endl;
      }

      if(renards_disparus){
        cout << "et les renards ont disparu :-(" << endl;
      }

      if(lapins_extinction){
        cout << "Les lapins ont été en voie d'extinction" << endl;
      }

      if(lapins_disparus){
        cout << "et les lapins ont disparu :-(" << endl;
      }

      if(est_remontee){
        cout << "mais la population est remontée ! Ouf !" << endl;
      }

      if(!renards_disparus && !renards_extinction &&
      !lapins_disparus && !lapins_extinction){
        cout << "Les lapins et les renards ont des populations stables." << endl;
      }

      taux_attaque_initial += 0.01;
      nb_lapins_2 = lapins_i;
      nb_renards_2 = renards_i;

    }

  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}
