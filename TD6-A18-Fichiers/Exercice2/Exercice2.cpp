#include <iostream>
#include <string>

using namespace std;

string lireEntree()
{
	string texte;
	getline(cin, texte);
	return texte;
}
void afficherTexte(const string& texte)
{
	cout.write(&texte[0], texte.size());
}

//TODO: Fonction dec2int.
//TODO: Fonction hex2int.
//TODO: Fonction int2dec.

int main()
{
	afficherTexte("Entrer un nombre decimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.

	afficherTexte("Entrer un nombre hexadecimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.

	//TODO: Utiliser vos fonctions dec2int, hex2int et int2dec pour calculer la somme des deux nombres.

	afficherTexte("La somme decimale est: ");
	//TODO: Afficher la somme en utilisant afficherTexte.
}