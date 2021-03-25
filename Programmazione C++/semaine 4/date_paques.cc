#include <iostream>
using namespace std;

/**
 * @brief demander_annee
 * @return
 */
int demander_annee(){
  int demander_annee(0);

  do{
      cout <<"Entrez une annee (1583-4000) : ";cin >> demander_annee;

  }while ((demander_annee < 1583) || (demander_annee > 4000));


  return demander_annee;
}

int date_Paques(int annee){

  int siecle(0);
  int jour(0);
  int p(0);
  int q(0);
  int M(0);
  int N(0);
  int d(0);
  int e(0);

  siecle = annee/100;
  p = (13 + (8*siecle))/25;
  q = siecle/4;
  M = (15 - p + siecle - q) % 30;
  N = (4 + siecle - q) % 7;
  d = (M + (19 * (annee%19)))%30;
  e = (2 * (annee % 4) + 4 * (annee % 7) + 6 * d + N) % 7;
  jour = e+d+22;

  if((e== 6) && ((d==29) || ((d==28) && (((11*(M+1))%30) < 19)))){
      jour -= 7;
  }

  return jour;
}

void affiche_date(int annee, int nombre_jours){

  if (nombre_jours >= 22 && nombre_jours <= 56){
      if(nombre_jours <= 31){
          cout <<"Date de Paques en " << annee << " : ";
          cout << nombre_jours << " mars ";
      }else if(nombre_jours >= 32){
          int nb_jours = nombre_jours;
          nb_jours -= 31;

          cout <<"Date de Paques en " << annee << " : ";
          cout << nb_jours <<" avril ";
      }
  }
}

int main(){

  int a(0);
  int b(0);
  a = demander_annee();
  b = date_Paques(a);
  affiche_date(a, b);
  return 0;
}
