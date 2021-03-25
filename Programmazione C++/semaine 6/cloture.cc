#include <iostream>
#include <vector>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

struct Position {
		int i;
		int j;
};
typedef vector<vector<int>> Carte;
bool binaire(Carte const& carte);
void affiche(Carte const& carte);
bool verifie_et_modifie(Carte& carte);
double longueur_cloture(Carte const& carte, double echelle = 2.5);
int rechercheIndex(int ligneDepart, int start, bool aGauche, Carte const& carte);
void testVoisins(Carte& carte, vector<Position> coordonnees, int composante);
void ajoute_unique(vector<int>& ensemble, int valeur);
bool convexite_lignes(Carte& carte, vector<int> const& labels_bords);
bool convexite_lignes(Carte& carte);
void marque_composantes(Carte& carte);

bool binaire(Carte const& carte) {

	for (int i = 0; i < carte.size(); i++) {
		for (int j = 0; j < carte[i].size(); j++) {
			if (carte[i][j] != 0 && carte[i][j] != 1) {
				return false;
			}
		}
	}
	return true;
}

void affiche(Carte const& carte) {
	for (auto vector : carte) {
		for (auto elt : vector) {
			cout << elt;
		}
		cout << endl;
	}

	cout << "----" << endl;
}

bool verifie_et_modifie(Carte& carte) {

	if (!binaire(carte)) {
		cout << "Votre carte du terrain ne contient pas que des 0 et des 1." << endl;
		return false;
	}

	if (!convexite_lignes(carte)) {
		return false;
	}



	//On efface les étangs maintenant.
	for (int i = 0; i < carte.size(); i++) {

		//Recherche du tout premier 1 à gauche.
		int leftIndex = rechercheIndex(i, 0, true, carte);

		if (leftIndex != -1) {

			//rechercher du tout premier 1 à droite
			int rightIndex = rechercheIndex(i, carte[i].size() - 1, false, carte);

			while (leftIndex < rightIndex) {
				if (carte[i][leftIndex] != 1) {
					carte[i][leftIndex] = 1;
				}
				leftIndex++;
			}

		}
	}
	return true;

}

void marque_composantes(Carte& carte) {

	vector<Position> coordonnees;
	Position positions;
	int composante(1);

	for (int oy(0); oy < carte.size(); oy++) {

		for (int ox = 0; ox < carte[oy].size(); ox++) {
			if (carte[oy][ox] == 0) {
				positions = { oy, ox };
				coordonnees.push_back(positions);
				testVoisins(carte, coordonnees, ++composante);
			}
		}
	}
}

void testVoisins(Carte& carte, vector<Position> coordonnees, int composante) {

	Position posRecup, posNew;

	while (!coordonnees.empty()) {

		posRecup = coordonnees.back();
		coordonnees.pop_back();

		if (carte[posRecup.i][posRecup.j] == 0) {
			carte[posRecup.i][posRecup.j] = composante;

			//Voisins NORD (on regarde si l'index de la ligne courante - 1 est plus grand ou égal à zéro
			if ((posRecup.i - 1) >= 0 && carte[posRecup.i - 1][posRecup.j] == 0) {
				posNew = { posRecup.i - 1, posRecup.j };
				coordonnees.push_back(posNew);
			}

			//Voisins SUD (on regarde si l'index de la ligne courante + 1 est plus petit que le nombre maximal de lignes.
			if ((posRecup.i + 1) < carte.size() && carte[posRecup.i + 1][posRecup.j] == 0) {
				posNew = { posRecup.i + 1, posRecup.j };
				coordonnees.push_back(posNew);
			}

			//Voisins OUEST (on regarde si l'index de la colonne courante - 1 est plus grand ou égal à zéro
			if ((posRecup.j - 1) >= 0 && carte[posRecup.i][posRecup.j-1] == 0) {
				posNew = { posRecup.i, posRecup.j - 1};
				coordonnees.push_back(posNew);
			}

			//Voisins EST (on regarde si l'index de la colonne courante + 1 est plus petit que le nombre maximal de colonnes.
			if ((posRecup.j + 1) < carte[posRecup.i].size() && carte[posRecup.i][posRecup.j + 1] == 0) {
				posNew = { posRecup.i, posRecup.j + 1 };
				coordonnees.push_back(posNew);
			}
		}
	}
}

void ajoute_unique(vector<int>& ensemble, int valeur) {
	
	bool estPresente(false);
	size_t i(0);

	while (!estPresente && i < ensemble.size()) {
		if (ensemble[i++] == valeur) {
			estPresente = true;
		}
	}

	if (!estPresente) {
		ensemble.push_back(valeur);
	}
}

int rechercheIndex(int ligneDepart, int start, bool aGauche, Carte const& carte) {

	int col = start;
	//Si la recherche commence tout à gauche
	if (aGauche) {
		while (col < carte[ligneDepart].size()) {
			if (carte[ligneDepart][col] == 1) {
				return col;
			}
			col++;
		}
	}else {
		//sinon c'est à droite.
		while (col >= 0) {
			if (carte[ligneDepart][col] == 1) {
				return col;
			}
			col--;
		}
	}
	//On retourne -1 pour dire que l'index recherché n'a pas été trouvé!
	return -1;
}

bool convexite_lignes(Carte& carte, vector<int> const& labels_bords) {

	
	for (int oy = 0; oy < carte.size(); oy++) {

		//Recherche du tout premier 1 à gauche.
		int firstLeftIndex = rechercheIndex(oy, 0, true, carte);

		//Si le premier 1 tout à gauche a été trouvé, 
		//alors on va chercher le tout premier à droite.
		//et ensuite on procède au test de la convexité del a carte.
		if (firstLeftIndex != -1) {

			//rechercher du tout premier 1 à droite
			int firstRightIndex = rechercheIndex(oy, carte[oy].size() - 1, false, carte);


			if (firstRightIndex != -1) {

				//indexes pour parcourir la ligne
				int debut = firstLeftIndex + 1;
				int fin = firstRightIndex - 1;

				//Recherche de toute valeur non 1 comprise entre le premier 1
				//et le dernier 1 de cette ligne courante (i.e., oy)
				while (debut <= fin) {

					//On ne regarde que la valeur 1 non comprise entre le premier et le dernier 1
					if (carte[oy][debut] != 1) {
						size_t i(0);
						//On parcourt tout notre tableau de valeurs de bords.
						while (i < labels_bords.size()) {

							int badValue = labels_bords[i];
							//si la valeur est présente dans notre tableau
							//alors la carte n'est pas convexe et on retourne 'false'.
							if (carte[oy][debut] == badValue) {
								cout << "Votre carte du terrain n'est pas convexe par lignes :" << endl;
								cout << "bord extérieur entrant trouvé en position [";
								cout << oy;
								cout << "][";
								cout << debut;
								cout << "]" << endl;
								return false;
							}
							i++;
						}
					}
					debut++;
				}
			}
		}
	}

	return true;
}

bool convexite_lignes(Carte& carte) {

	marque_composantes(carte);

	vector<int> values;

	// 1) bord tout en haut...il faut fixer la ligne à zéro.
	// 2) bord tout au fond...il faut fixer la ligne à carte.size()-1
	for (int ox = 0; ox < carte[0].size(); ox++) {

		// 1)
		if (carte[0][ox] != 1) {
			ajoute_unique(values, carte[0][ox]);
		}

		// 2)
		if (carte[carte.size() - 1][ox] != 1) {
			ajoute_unique(values, carte[carte.size() - 1][ox]);
		}
	}

	// 1) bord tout à droite...Il faut fixer la colonne à zéro.
	// 2) bord tout à gauche..il faut fixer la colonne à carte[0].size()
	for (int oy = 0; oy < carte.size(); oy++) {

		// 1)
		if (carte[oy][0] != 1) {
			ajoute_unique(values, carte[oy][0]);
		}

		// 2)
		if (carte[oy][carte[0].size()-1] != 1) {
			ajoute_unique(values, carte[oy][carte[0].size()-1]);
		}
	}

	return convexite_lignes(carte, values);
}

double longueur_cloture(Carte const& carte, double echelle) {

	int nbFaces(0);
	int tailleLignes = carte.size();
	int tailleColonnes = carte[0].size();

	//On boucle sur toutes les positions de la carte
	for (int oy = 0; oy < tailleLignes; oy++) {
		for (int ox = 0; ox < tailleColonnes; ox++) {

			//on regarde si à la position courante la valeur vaut 1
			//Si tel est le cas
			if (carte[oy][ox] == 1) {

				//alors on procède d'abord au comptage des cases vides (i.e., on regarde si les voisins du '1' sont des cases vides).
				int i = -1;
				while (i < 2) {
					int posX = ox + i;
					int posY = oy + i;

					//vérifie que le voisin OUEST est une case vide
					if (posX < 0) {
						nbFaces++;
					}

					//vérifie que le voisin EST est une case vide
					if (posX >= tailleColonnes) {
						nbFaces++;
					}

					//vérifie que le voisin NORD est une case vide
					if (posY < 0) {
						nbFaces++;
					}

					//vérifie que le voisin SUD est une case vide
					if (posY >= tailleLignes) {
						nbFaces++;
					}
					i++;
				}

				//Maintenant on vérifie qu'un point du pourtour a une valeur différente de 1 comme voisin NORD, SUD,... 
				//Si le voisin NORD à une valeur différente de 1
				if ((oy - 1) >= 0 && carte[oy - 1][ox] != 1) {
					nbFaces++;
				}

				//Si le voisin SUD à une valeur différente de 1
				if ((oy + 1) < tailleLignes && carte[oy + 1][ox] != 1) {
					nbFaces++;
				}

				//Si le voisin EST à une valeur différente de 1
				if ((ox + 1) < tailleColonnes && carte[oy][ox + 1] != 1) {
					nbFaces++;
				}

				//Si le voisin OUEST à une valeur différente de 1
				if ((ox - 1) >= 0 && carte[oy][ox - 1] != 1) {
					nbFaces++;
				}

			}
		}
	}

	return nbFaces * echelle;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Carte carte = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  cout << "Carte au départ :" << endl;
  affiche(carte);
  if (verifie_et_modifie(carte)) {
    cout << "Carte après modification :" << endl;
    affiche(carte);
    cout << "Il vous faut " << longueur_cloture(carte)
         << " mètres de clôture pour votre terrain."
         << endl;
  }

  return 0;
}
