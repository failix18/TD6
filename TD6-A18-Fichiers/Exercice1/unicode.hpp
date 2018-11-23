#pragma once
/// Fonctions de base pour l'utilisation d'Unicode sur wcin/wcout.
/// \author Francois-R.Boyer@PolyMtl.ca
/// \file
#include <iostream>
#include <string>
#ifdef _MSC_VER
#include <io.h>      // Pour _setmode et _fileno
#include <fcntl.h>   // Pour _O_U8TEXT et _O_U16TEXT
#endif
static int cin, cout; // Après l'initialisation d'Unicode, cin et cout plantent si on tente de les utiliser.  Ces variables feront une erreur de compilation "symbole ambigu" si le programme tente d'utiliser cin ou cout, pour détecter le problème à la compilation plutôt qu'à l'exécution.

/*************************************************************************//**
*  Initialise la bibliothèque pour pouvoir afficher en Unicode.
*  \return  \c true si réussi.
*/
inline bool initUnicode()
{
	bool reussi;
	// Sélectionne les paramètres régionnaux par défaut.
	reussi = setlocale(LC_ALL, "") != 0;

	// Sélectionne le mode de sortie et d'entrée;
	// nécessaire sur VisualC mais pas GCC et Clang.
	#ifdef _MSC_VER
	reussi = _setmode(_fileno(stdout), _O_U8TEXT) != -1 && reussi;
	reussi = _setmode(_fileno(stdin), _O_U16TEXT) != -1 && reussi;
	#endif
	return reussi;
}

/*************************************************************************//**
*  Conversion de 'wstring' en 'string' Latin-1.
*/
inline std::string versString(const std::wstring& chaine) {
	static const char CARACTERE_INCONNU = '?';
	std::string resultat;
	resultat.resize(chaine.length());
	for (size_t i = 0; i < chaine.length(); ++i) {
		if (chaine[i] < 256)
			resultat[i] = char(chaine[i]);
		else // Le caractère n'existe pas en 'char'.
			resultat[i] = CARACTERE_INCONNU; 
	}
	return resultat;
}

/*************************************************************************//**
*  Conversion de 'string' Latin-1/ASCII en 'wstring'.
*/
inline std::wstring versWstring(const std::string& chaine) {
	std::wstring resultat;
	resultat.resize(chaine.length());
	for (size_t i = 0; i < chaine.length(); ++i)
		resultat[i] = (unsigned char)chaine[i];
	return resultat;
}

/*************************************************************************//**
*  Permet d'afficher une 'string' sur 'wcout' avec l'opérateur << standard.
*/
inline std::wostream& operator <<(std::wostream& flot, const std::string& chaine)
{
	return flot << versWstring(chaine);
}
