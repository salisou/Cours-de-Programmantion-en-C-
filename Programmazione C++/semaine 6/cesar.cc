#include <iostream>
#include <string>
using namespace std;

char code(char c, int decalage);
string code(string chaine, int decalage);
char decale(char c, char debut, int decalage);
string decode(string chaine, int decalage);

char code(char c, int decalage) {

	if (c >= 'a' && c <= 'z') {
		return decale(c, 'a', decalage);
	}else if (c >= 'A' && c <= 'Z') {
		return decale(c, 'A', decalage);
	}
	return c;
}

string code(string chaine, int decalage) {
	string chaineCodee = "";
	size_t taille(chaine.size());
	size_t i(0);

	while (i < taille) {
		char c = code(chaine[i], decalage);
		chaineCodee += c;
		i++;
	}
	return chaineCodee;
}

char decale(char c, char debut, int decalage) {

	while (decalage < 0) decalage += 26;

	return debut + (((c - debut) + decalage) % 26);
}

string decode(string chaine, int decalage) {
	string chaineDecodee = code(chaine, -decalage);
	return chaineDecodee;
}

int main()
{
	// Codage
	cout << code("Fuyez manants", 4) << endl;
	cout << code("Fuyez manants", 6) << endl;
	cout << code("Fuyez manants", -4) << endl;
	cout << code("Avez-vous vu mes 3 chats et mes 2 chiens ?", 4) << endl;
    cout << code("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG", 3) << endl;
    cout << code("defend the east wall of the castle", 1) << endl;
	cout << endl;
	
	// Décodage
	cout << decode("Jycid qererxw", 4) << endl;
	cout << decode("Laekf sgtgtzy", 6) << endl;
	cout << decode("Bquav iwjwjpo", -4) << endl;
	cout << decode("Ezid-zsyw zy qiw 3 glexw ix qiw 2 glmirw ?", 4) << endl;
    cout << decode("QEB NRFZH YOLTK CLU GRJMP LSBO QEB IXWV ALD", 3) << endl;
    cout << decode("efgfoe uif fbtu xbmm pg uif dbtumf", 1) << endl;

	return 0;
}
