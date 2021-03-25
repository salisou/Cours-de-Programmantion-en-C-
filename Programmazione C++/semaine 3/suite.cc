#include <iostream>
using namespace std;

int main()
{
  int debut(0);
  do {
    cout << "de (>= 1) ? ";
    cin >> debut;
  } while (debut < 1);

  int fin(0);
  do {
    cout << "a (>= " << debut << ") ? ";
    cin >> fin;
  } while (fin < debut);

  /*******************************************
   * Completez le programme a partir d'ici.
   *******************************************/
  while(debut <= fin) {
      int nbr = debut;
      int nb_operation = 0;
      while(nbr != 0) {

          if(nbr % 3 == 0) {
              nbr += 4;
            }else if(nbr % 4 == 0) {
              nbr /= 2;
            }else {
              nbr--;
            }

          nb_operation++;
        }
      cout << debut << " -> " << nb_operation << endl;
      debut++;
  }
  /*******************************************
   * Ne rien modifier apres cette ligne.
   *******************************************/

  return 0;
}
