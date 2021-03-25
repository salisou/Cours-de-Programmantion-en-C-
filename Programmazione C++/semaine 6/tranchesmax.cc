#include <iostream>
#include <vector>
using namespace std;

int somme_consecutifs_max(vector<int> tab) {
	int max_so_far(0);
	int max_ending_here(0);

	for (auto elt : tab) {
		if (elt > 0) {
			max_so_far += elt;

			if (max_ending_here < max_so_far) {
				max_ending_here = max_so_far;
			}
		}else {
			max_so_far = 0;
		}
	}
	return max_ending_here;
}

vector<size_t> lignes_max(vector<vector<int>> tab) {

	vector<size_t> maxLines;
	vector<int> decompte;
	int maxLine(0);
	int greatestMax(0);

	for (int i = 0; i < tab.size(); i++) {

		//recherche de la somme maximal consécutive.
		maxLine = somme_consecutifs_max(tab[i]);
		//stockage du max pour chaque ligne dans un tableau.
		decompte.push_back(maxLine);
		//stockage du plus grand max du tableau à 2 dimensions.
		if (greatestMax < maxLine) {
			greatestMax = maxLine;
		}
	}

	//maintenant on stocke dans le tableau maxLines, les indices où la plus grande somme maximale est atteinte(i.e., greatestMax)
	for (int i = 0; i < decompte.size(); i++) {
		if (decompte[i] == greatestMax) {
			maxLines.push_back(i);
		}
	}

	return maxLines;
}

vector<vector<int>> tranches_max(vector<vector<int>> tab) {
	vector<vector<int>> tranchesMaximales;
	vector<size_t> maxIndexes = lignes_max(tab);

	for (auto index : maxIndexes) {
		tranchesMaximales.push_back(tab[index]);
	}

	return tranchesMaximales;
}

int main(){
    
    cout << somme_consecutifs_max({ 0, 2, 2, 0 }) << endl;
	cout << somme_consecutifs_max({ 2, 3, 0, 0, 4 }) << endl;
	cout << somme_consecutifs_max({ 4, 0, 2, 3 }) << endl;
	cout << somme_consecutifs_max({ 0, 0, 0, 0, 0 }) << endl;
	cout << endl;

	vector<vector<int>> tableau = {
		{2, 1, 0, 2},
		{0, 1, 0, 3},
		{1, 3, 0, 0},
		{0, 2, 2, 0}
	};
	vector<size_t> resultant = lignes_max(tableau);
	
	bool virg = false;
	cout << "{";
	for (auto element : resultant) {
		if (virg)
			cout << ", ";
		else
			virg = true;
		cout << element;
	}
	cout << "}" << endl;
	cout << endl;

	tableau = {
		{2, 1, 0, 2, 0, 3, 2},
		{0, 1, 0, 7, 0},
		{1, 0, 1, 3, 2, 0, 3, 0, 4},
		{5, 0, 5},
		{1, 1, 1, 1, 1, 1, 1}
	};
	
	vector<vector<int>> res = tranches_max(tableau);
	for (auto ligne : res) {
		virg = false;
		cout << "{";
		for (auto element : ligne) {
			if (virg)
				cout << ", ";
			else
				virg = true;
			cout << element;
		}
		cout << "}" << endl;
	}
cout << endl;
    return 0;
}
