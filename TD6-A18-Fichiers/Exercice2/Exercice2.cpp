////////////////////////////////////////////////////////////////////////////////
/// \file    Exercice2.cpp
/// \author  Félix Dumont(1954787) et Mark Weber-Sadler(1947609)
/// \version 2018-12-4
///
/// Ce programme lit un nombre décimal en string et le convertie en double, et lit un nombre hexadecimal en string et le convertie en double. Ensuite le programme additione ces deux nombres et affiche le résultat en hexadécimal.
////////////////////////////////////////////////////////////////////////////////








#include <iostream>
#include <string>
#include <cmath>

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

double dec2int(string dec) {
	//TODO: Fonction dec2int.
	int DEC_SIZE = dec.size();
	int positionDecimale = DEC_SIZE;
	double nombre =0;
	for (int i = 0; i < DEC_SIZE; i++) {
		if (dec[i] == '.')
			positionDecimale = i;	
	}
	int tampon = 0;
	for (int i = 0; i < DEC_SIZE; i++) {
		char chiffre = dec[i];
		int exposant = (positionDecimale - 1) - tampon;
		double multiplicatif;
		if (chiffre != '.') {
			multiplicatif = pow(10, exposant);
			switch (chiffre) {
				case '0': nombre += (0 * multiplicatif);
					break;
				case '1': nombre += (1 * multiplicatif);
					break;
				case '2': nombre += (2 * multiplicatif);
					break;
				case '3': nombre += (3 * multiplicatif);
					break;
				case '4': nombre += (4 * multiplicatif);
					break;
				case '5': nombre += (5 * multiplicatif);
					break;
				case '6': nombre += (6 * multiplicatif);
					break;
				case '7': nombre += (7 * multiplicatif);
					break;
				case '8': nombre += (8 * multiplicatif);
					break;
				case '9': nombre += (9 * multiplicatif);
					break;
				default: nombre += 0;
			}
		}
		else
			tampon--; //ajustement de la decimale
		tampon++;
	}
	return nombre;
}

double hex2int(string hex) {
	//TODO: Fonction hex2int.
	int HEX_SIZE = hex.size();
	double nombre = 0;

	for (int i = 0; i < HEX_SIZE; i++) {
		char chiffre = hex[i];
		int exposant = (HEX_SIZE-1) - i;
		double multiplicatif;
	
		multiplicatif = pow(16, exposant);
		switch (toupper(chiffre)) {
		case '0': nombre += (0 * multiplicatif);
			break;
		case '1': nombre += (1 * multiplicatif);
			break;
		case '2': nombre += (2 * multiplicatif);
			break;
		case '3': nombre += (3 * multiplicatif);
			break;
		case '4': nombre += (4 * multiplicatif);
			break;
		case '5': nombre += (5 * multiplicatif);
			break;
		case '6': nombre += (6 * multiplicatif);
			break;
		case '7': nombre += (7 * multiplicatif);
			break;
		case '8': nombre += (8 * multiplicatif);
			break;
		case '9': nombre += (9 * multiplicatif);
			break;
		case 'A': nombre += (10 * multiplicatif);
			break;
		case 'B': nombre += (11 * multiplicatif);
			break;
		case 'C': nombre += (12 * multiplicatif);
			break;
		case 'D': nombre += (13 * multiplicatif);
			break;
		case 'E': nombre += (14 * multiplicatif);
			break;
		case 'F': nombre += (15 * multiplicatif);
			break;
		default: nombre += 0;
		}
	}
	return nombre;
}

string int2dec(double resultat) {
	//TODO: Fonction int2dec.
	int valeurHexa = resultat;
	int moduloValeur = 0;
	int i = 0;
	string nombreHexa;
	do {
		moduloValeur = (valeurHexa % int(pow(16, i)));
		int chiffre =  int ((valeurHexa - moduloValeur) / (pow(16,i))) % 16;
		if (moduloValeur != valeurHexa) {
			switch (chiffre) {
			case 0: nombreHexa = nombreHexa + '0';
				break;
			case 1: nombreHexa = '1' + nombreHexa;
				break;
			case 2: nombreHexa = '2' + nombreHexa;
				break;
			case 3: nombreHexa = '3' + nombreHexa;
				break;
			case 4: nombreHexa = '4' + nombreHexa;
				break;
			case 5: nombreHexa = '5' + nombreHexa;
				break;
			case 6: nombreHexa = '6' + nombreHexa;
				break;
			case 7: nombreHexa = '7' + nombreHexa;
				break;
			case 8: nombreHexa = '8' + nombreHexa;
				break;
			case 9: nombreHexa = '9' + nombreHexa;
				break;
			case 10: nombreHexa = 'A' + nombreHexa;
				break;
			case 11: nombreHexa = 'B' + nombreHexa;
				break;
			case 12: nombreHexa = 'C' + nombreHexa;
				break;
			case 13: nombreHexa = 'D' + nombreHexa;
				break;
			case 14: nombreHexa = 'E' + nombreHexa;
				break;
			case 15: nombreHexa = 'F' + nombreHexa;
				break;
			default: nombreHexa += "";
			}
		}
		i++;
	} while (moduloValeur != valeurHexa);
	
	return nombreHexa ;
}


int main()
{
	afficherTexte("Entrer un nombre decimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string nombreDecimal = lireEntree();

	afficherTexte("Entrer un nombre hexadecimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string nombreHexadecimal = lireEntree();

	//TODO: Utiliser vos fonctions dec2int, hex2int et int2dec pour calculer la somme des deux nombres.
	double decimal = dec2int(nombreDecimal);
	double decimalHexa = hex2int(nombreHexadecimal);
	double resultat = decimal + decimalHexa;
	string resultatHexa = int2dec(resultat);


	afficherTexte("La somme decimale est: ");
	//TODO: Afficher la somme en utilisant afficherTexte.
	afficherTexte(resultatHexa);

}