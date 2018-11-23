#pragma once
// Pour avoir un rapport de fuites incluant les numéros de lignes où l'allocation a été faite.
// (source http://msdn.microsoft.com/en-us/library/x98tx3cf%28v=vs.100%29.aspx)
#define _CRTDBG_MAP_ALLOC ///< Utilise les allocations avec débogage.
#include <stdlib.h>
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ ) ///< Ajoute le numéro de ligne au rapport de fuites.

inline void initDebogageMemoire()
{
	_CrtSetDbgFlag(0
		| _CRTDBG_ALLOC_MEM_DF    // Débogage d'allocation mémoire.
		| _CRTDBG_LEAK_CHECK_DF   // Rapport de fuites à la sortie du programme.  Noter que le rapport de fuites sera affiché dans la fenêtre "Sortie" de Visual Studio.
		| _CRTDBG_CHECK_ALWAYS_DF // Vérifie la corruption à chaque new/delete (lent).
		);
}
