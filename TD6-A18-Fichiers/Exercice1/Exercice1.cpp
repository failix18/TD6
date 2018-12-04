#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include "debogageMemoire.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "unicode.hpp"         // Nos fonctions pour l'utilisation d'Unicode sur wcin/wcout.

#include <iostream>
#include <fstream>
#include <string>
#include <cwchar>
#include <limits>
#include <algorithm>
using namespace std;

#pragma endregion//}

//TODO: Mettre les bons types pour le fichier binaire.
typedef unsigned char UInt8;
typedef unsigned short UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
wstring lireWstring(istream& fichier)
{
	wstring texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], sizeof(texte[0]) * texte.length());
	return texte;
}

#pragma endregion//}
void ajouterFilm(ListeFilms& liste, Film* film) {
	//TODO: Une fonction pour ajouter un Film à une ListeFilms, le film existant déjà; on veut uniquement ajouter le pointeur vers le film existant.  Vous pouvez vous inspirer de votre fonction du TD5.  Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.

	if (liste.capacite == 0) {
		liste.elements = new Film*[1];
		liste.capacite = 1;
		liste.nElements = 0;
		
	}
	else if (liste.capacite <= liste.nElements) {
		
		ListeFilms listeTampon;
		listeTampon.elements = new Film*[liste.capacite];

		for (int i = 0; i < liste.nElements; i++) {
			listeTampon.elements[i] = liste.elements[i];
		}

		delete liste.elements;
		liste.elements = new Film*[liste.capacite * 2];
		liste.capacite = liste.capacite * 2;

		for (int i = 0; i < liste.nElements; i++) {
			liste.elements[i] = listeTampon.elements[i];
		}
	
		delete listeTampon.elements;
	}

	liste.elements[liste.nElements] = film;
	liste.nElements++;


}

void enleverFilm(ListeFilms& liste, Film* film)
{
	//TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.  Encore une fois, vous pouvez vous inspirer de votre fonction du TD5.
	for (int i = 0; i < liste.nElements - 1; i++){
		if (film->titre == liste.elements[i]->titre) {
			for (int j = i; j < liste.nElements - 1; j++) {
				liste.elements[j] = liste.elements[j + 1];
			}
			liste.nElements--;
		}

	}
	if (film == liste.elements[liste.nElements-1]) {
		liste.nElements--;

		}

}



Acteur* trouverActeur(ListeFilms liste, wstring nom) {
	//TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.

	Acteur* acteurRetour = nullptr;


	for (int i = 0; i < liste.nElements; i++) {
		for (int j = 0; j < liste.elements[i]->acteurs.nElements; j++) {
			if (nom == liste.elements[i]->acteurs.elements[j]->nom) {
				acteurRetour = liste.elements[i]->acteurs.elements[j];
			}
		}
	}
	return acteurRetour;


}
//TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.  La ListeFilms devra être passée entre les fonctions, pour vérifier l'existence d'un Acteur avant de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).


Acteur* lireActeur(istream& fichier, ListeFilms& liste)
{
	//TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations, selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées; vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
	Acteur acteur = {};
	acteur.nom = lireWstring(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);

	Acteur* acteurBon;

	acteurBon = trouverActeur(liste, acteur.nom);

	if (acteurBon == nullptr) {
		acteurBon = new Acteur;
		*acteurBon = acteur;
		acteurBon->joueDans.capacite = 0;

		wcout << "Le nom de l'acteur est: " << acteurBon->nom << endl;
	}

	return acteurBon;
	   
}

Film* lireFilm(istream& fichier, ListeFilms& liste)
{
	Film film = {};
	film.titre = lireWstring(fichier);
	film.realisateur = lireWstring(fichier);
	film.anneeSortie = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	film.acteurs.nElements = lireUint8(fichier);  //NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs, sans faire de réallocation comme pour ListeFilms.  Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions et faire un remplacement de Film par Acteur, pour réutiliser cette réallocation.

	Film* filmBon;
	filmBon = new Film;
	*filmBon = film;
	filmBon->acteurs.elements = new Acteur*[filmBon->acteurs.nElements];
	filmBon->acteurs.capacite = film.acteurs.nElements;

	for (int i = 0; i < film.acteurs.nElements; i++) {
		filmBon->acteurs.elements[i] = lireActeur(fichier, liste); //TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		//TODO: Ajouter le film aux films dans lesquels l'acteur joue.
		ajouterFilm(filmBon->acteurs.elements[i]->joueDans, filmBon);
	}
	return filmBon; //TODO: Retourner le pointeur vers le nouveau film.
}

ListeFilms creerListe(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);

	ListeFilms liste;
	liste.capacite = 0;

	//TODO: Créer une liste de films vide.
	for (int i = 0; i < nElements; i++) {
		ajouterFilm(liste, lireFilm(fichier, liste));
	}

	return liste; //TODO: Retourner la liste de films.
}

void detruireFilm(ListeFilms& liste, Film* film) {
	//TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film, et les acteurs qui ne jouent plus dans aucun films de la collection).  Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.  Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
	
	for (int i = 0; i < film->acteurs.nElements; i++) {
		enleverFilm(film->acteurs.elements[i]->joueDans, film);
		if (film->acteurs.elements[i]->joueDans.nElements == 0) {
			wcout << film->acteurs.elements[i]->nom<<endl;
			delete film->acteurs.elements[i];
			film->acteurs.elements[i] = nullptr;
			//film->acteurs.elements[i]->anneeNaissance = 0;
			//film->acteurs.elements[i]->sexe = 0;///////////////////////////////////////
		}
	}
	enleverFilm(liste, film);
	film = nullptr;
	//film->realisateur = nullptr;//////////////////////////////
	//film->anneeSortie = 0;
	//film->recette = 0;
	delete film;
}


void detruireListeFilm(ListeFilms& liste) {
	//TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.

	for (int i = 0; i < liste.nElements; i) {
		detruireFilm(liste,liste.elements[0]);
	}
	delete[] liste.elements;
	liste.elements = NULL;
	
}

void afficherActeur(const Acteur& acteur)
{
	wcout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

void afficherFilm(Film* film){
	//TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).
	for (int i = 0; i < film->acteurs.nElements; i++) {
		afficherActeur(*film->acteurs.elements[i]); 
	}
	wcout << "Année de sortie: " << film->anneeSortie << endl
		<< "Nom du réalisateur: " << film->realisateur << endl
		<< "Recette du film: " << film->recette << endl
		<< "Titre du film: " << film->titre << endl;
}

void afficherListeFilm(ListeFilms listeFilm) {
	//TODO: Une fonction pour afficher tous les films d'une ListeFilms.
	for (int i=0; i<listeFilm.nElements;i++){
		wcout << listeFilm.elements[i]->titre<<endl;

	}

}

 void filmsActeur(wstring nom, ListeFilms liste ) {
	//TODO: Une fonction pour afficher tous les films dans lesquels un acteur joue, prenant en paramètre le nom de l'acteur.  Cette fonction devrait presque uniquement faire des appels aux autres fonctions écrites.  Elle doit se comporter correctement si l'acteur n'existe pas.
		 
	 Acteur* acteur= trouverActeur(liste, nom);
	 afficherListeFilm(acteur->joueDans);
	 	
}

 
int main()

{
	initDebogageMemoire(); // Affichera dans la "Sortie" de VisualStudio les fuites de mémoire, si exécuté avec débogage.
	initUnicode(); // Permet d'afficher des caractères Unicode (pas seulement les accents latin).
	
	static const wstring LIGNE_DE_SEPARATION = L"\n════════════════════════════════════════\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	//TODO: Lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms liste;
	liste =creerListe("films.bin");
	
	wcout << LIGNE_DE_SEPARATION << L"Le premier film de la liste est:" << endl;
	//TODO: Afficher le premier film de la liste.  Devrait être Alien.
	wcout <<  liste.elements[0]->titre << endl;
	
	wcout << LIGNE_DE_SEPARATION << L"Les films sont:" << endl;
	//TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	afficherListeFilm(liste);

	//TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).
	wstring nom = L"Benedict Cumberbatch";
	Acteur* acteur = trouverActeur(liste, nom);
	acteur->anneeNaissance = 1976;
	
	wcout << LIGNE_DE_SEPARATION << L"Liste des films où Benedict Cumberbatch joue sont:" << endl;
	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	filmsActeur(nom, liste);

	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	enleverFilm(liste, liste.elements[0]);

	wcout << LIGNE_DE_SEPARATION << L"Les films sont maintenant:" << endl;
	//TODO: Afficher la liste des films.
	afficherListeFilm(liste);

	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	afficherFilm(liste.elements[0]);
	

	//TODO: Détruire tout avant de terminer le programme.  Il ne devrait y avoir aucun message "Detected memory leaks!" dans la fenêtre de Sortie de VisualStudio.
	detruireListeFilm(liste);

	}
