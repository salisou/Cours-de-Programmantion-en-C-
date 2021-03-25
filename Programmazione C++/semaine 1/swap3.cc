#include <iostream>

using namespace std;

int main()
{
 cout << "Entrez la premiere  valeur : ";
 int a(0);
 cin >> a;
 cout << "Entrez la deuxieme  valeur : ";
 int b(0);
 cin >> b;
 cout << "Entrez la troisieme valeur : ";
 int c(0);
 cin >> c;

 cout << "Les valeurs entrees sont : a = " << a << ", b = " << b
      << " et c = " << c << endl;

 cout << "Permutation: a ==> b, b ==> c, c ==> a" << endl;

 /*****************************************************
  * Compléter le code à partir d'ici
  *****************************************************/
 int temp = a;
 a = c;
 c = temp;

 int temp1 = b;
 b = c;
 c = temp1;
 /*******************************************
  * Ne rien modifier après cette ligne.
  *******************************************/

 cout << "Les valeurs permutees sont : a = " << a << ", b = " << b
      << " et c = " << c << endl;

 return 0;
}
