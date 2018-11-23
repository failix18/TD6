#pragma once
// Structures mémoires pour une collection de films.

#include <string>
using std::wstring;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

struct ListeFilms {
	int capacite, nElements;
	Film** elements; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements;
};

struct Film
{
	wstring titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	wstring nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
