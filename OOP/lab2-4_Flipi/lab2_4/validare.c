#include "domain.h"
#include <string.h>

int validare(Masina* masina)
{
	/*Functia valideaza daca masina transmisa ca parametru este sau nu valida
	* este valida daca (se returneaza 1): -> lungimea numarului de inmatriculare este egal cu 7
	*									  -> lungimea modelului este diferita de 0
	*									  -> categoria este una dintre: suv / sport / mini / sedan
	*/
	if (strlen((*masina).nr_inmatriculare) != 7) return 0;
	if (strlen((*masina).model) == 0) return 0;
	if(strcmp((*masina).categorie, "mini") != 0 && strcmp((*masina).categorie, "suv") != 0 && strcmp((*masina).categorie, "sport") != 0 && strcmp((*masina).categorie, "sedan") != 0)
		return 0;
	return 1;
}