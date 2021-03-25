#include <iostream>
using namespace std;

int separer_chiffre_gauche(int& nombre)
{
  int dix(1);
  int temp(nombre);
  while (temp >= 10) {
    dix  *= 10;
    temp /= 10;
  }
  nombre %= dix;
  return temp;
}

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

void ajouter_chiffre_droit(int& nombre, int chiffre)
{
  nombre = (nombre * 10) + chiffre;
}

void dire_chiffre(int& nombre, int repetitions_chiffre, int chiffre)
{
  for(int i(0); i < 2; i++){
      ajouter_chiffre_droit(nombre, repetitions_chiffre);
      repetitions_chiffre = chiffre;
  }
}

int lire_et_dire(int nombre)
{
  int chiffres_droite = nombre;
  int chiffre_gauche = separer_chiffre_gauche(chiffres_droite);
  int compteur(1);
  int nombre_final(0);

  while(chiffre_gauche != 0){
      int prochain_chiffre_gauche = separer_chiffre_gauche(chiffres_droite);

      if(chiffre_gauche == prochain_chiffre_gauche){
          compteur++;
      }else{
          dire_chiffre(nombre_final, compteur, chiffre_gauche);
          compteur = 1;
      }
      
      chiffre_gauche = prochain_chiffre_gauche;
  }

  return nombre_final;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void repeter_lire_et_dire(int& nombre, int fois)
{
  while (fois-- > 0) {
    nombre = lire_et_dire(nombre);
  }
}

int main()
{
  int nombre(1);
  int fois(1);
  cin >> nombre >> fois;
  repeter_lire_et_dire(nombre, fois);
  cout << nombre << endl;
  return 0;
}
