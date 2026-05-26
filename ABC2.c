#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Pacient {
	int idPacient;
	char* numePacient;
	float costTratament;
}Pacient;

//struct nod arbore 

typedef struct Nod {
	Pacient info;
	struct Nod* nodStanga;
	struct Nod* nodDreapta;
}Nod;

//constructor

Pacient constructorPacient(int idPacient, const char* numePacient, float costTratament) {
	Pacient p;
	p.idPacient = idPacient;
	p.numePacient = (char*)malloc(strlen(numePacient) + 1);
	strcpy(p.numePacient, numePacient);
	p.costTratament = costTratament;

	return p;
}

//fct de afisare

void afisarePacient(Pacient p) {
	printf("%d | %s | %.2f\n", p.idPacient, p.numePacient, p.costTratament);
}

//citirea din fisiser
Pacient citirePacientDinFisier(FILE* file) {
	Pacient p;

	p.idPacient = 0;
	p.numePacient = NULL;
	p.costTratament = 0;

	char buffer[256];
	char sep[] = ",\n";
	char* token;
	
	fgets(buffer, sizeof(buffer), file);

	token = strtok(buffer, sep);

	p.idPacient = atoi(token);

	token = strtok(NULL, sep);

	p.numePacient = (char*)malloc(strlen(token) + 1);
	strcpy(p.numePacient, token);

	token = strtok(NULL, sep);

	p.costTratament = atof(token);

	return p;
}

//Creare Nod

Nod* creareNod(Pacient p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = constructorPacient(p.idPacient, p.numePacient, p.costTratament);
	nou->nodDreapta = NULL;
	nou->nodStanga = NULL;

	return nou;
}

//fct de inserare a un
// 
// ui nod intr-un arbore

Nod* inserareNod(Nod* radacina, Pacient p) {
	if (radacina == NULL)
	{
		return creareNod(p);
	}

	if (p.idPacient<radacina->info.idPacient)
	{
		radacina->nodStanga = inserareNod(radacina->nodStanga, p);
	}

	if (p.idPacient > radacina->info.idPacient) {
		radacina->nodDreapta = inserareNod(radacina->nodDreapta, p);
	}

	return radacina;
}

//fct de citire arbore din fisier

Nod* citireArboreFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	if (file)
	{
		while (!feof(file)) {
			Pacient p = citirePacientDinFisier(file);
			radacina = inserareNod(radacina, p);
			free(p.numePacient);
		}
		fclose(file);
	}
	return radacina;
}

//afisarea in preordine
void afisarePreordine(Nod* radacina) {
	if (radacina)
	{
		afisarePacient(radacina->info);
		afisarePreordine(radacina->nodStanga);
		afisarePreordine(radacina->nodDreapta);
	}
}

//afisare inordine

void afisareInordine(Nod* radacina) {
	if (radacina)
	{
		afisareInordine(radacina->nodStanga);
		afisarePacient(radacina->info);
		afisareInordine(radacina->nodDreapta);
	}
}

//afisare postordine

void afisarePostordine(Nod* radacina) {
	if (radacina)
	{
		afisarePostordine(radacina->nodStanga);
		afisarePostordine(radacina->nodDreapta);
		afisarePacient(radacina->info);
	}
}

//cautare nod dupa cheie

Nod* cautareDupaID(Nod* radacina, int idCautat) {
	if (radacina == NULL)
	{
		return NULL;
	}
	if (idCautat == radacina->info.idPacient) 
	{
		return radacina;
	}

	if (idCautat < radacina->info.idPacient)
	{
		return cautareDupaID(radacina->nodStanga, idCautat);
	}
	else
	{
		return cautareDupaID(radacina->nodDreapta, idCautat);
	}
}

//calculare nr noduri

int nrTotalNoduri(Nod* radacina) {
	if (radacina == NULL)
	{
		return 0;
	}
	return 1 + nrTotalNoduri(radacina->nodStanga) + nrTotalNoduri(radacina->nodDreapta); 
}

//fct total frunze

int nrFrunze(Nod* radacina) {
	if (radacina == NULL)
	{
		return 0;
	}

	if (radacina->nodStanga == NULL && radacina->nodDreapta == NULL)
	{
		return 1;
	}
	return nrFrunze(radacina->nodStanga) + nrFrunze(radacina->nodDreapta);
}

//fct inaltimeArbore
int inaltimeArbore(Nod* radacina) {
	if (radacina == NULL)
	{
		return 0;
	}

	int inaltimeStanga = inaltimeArbore(radacina->nodStanga);
	int inaltimeDreapta = inaltimeArbore(radacina->nodDreapta);

	if (inaltimeStanga > inaltimeDreapta)
	{
		return 1 + inaltimeStanga;
	}
	else {
		return 1 + inaltimeDreapta;
	}
}

//fct de a afla minimul din subarborele drept
Nod* minim(Nod* radacina) {
	while (radacina && radacina->nodStanga){
		radacina = radacina->nodStanga;
		}
	return radacina;
}

//fct de max

Nod* maxim(Nod* radacina) {
	while (radacina && radacina->nodDreapta) {
		radacina = radacina->nodDreapta;
	}
	return radacina;
}

// Conversie AVL

//calcul grad echilibru
int gradEchilibru(Nod* radacina) {
	if (radacina) {
		return inaltimeArbore(radacina->nodStanga) - inaltimeArbore(radacina->nodDreapta);
	}
	return 0;
}

//rotatie dreapta -> se foloseste cand arborele este prea greu in stanga (cand fct gradEchilibru de mai sus da pozitiva)
void rotireDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->nodStanga;
	(*radacina)->nodStanga = aux->nodDreapta;
	aux->nodDreapta = *radacina;
	*radacina = aux;
}

//rotatie stanga -> se foloseste cand arborele este prea greu in dreapta (cand fct gradEchilibru de mai sus da negativa)

void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->nodDreapta;
	(*radacina)->nodDreapta = aux->nodStanga;
	aux->nodStanga = *radacina;
	*radacina = aux;
}

//inserarea in AVL

void inserareAVL(Nod** radacina, Pacient p) {
	if (*radacina) {
		if (p.idPacient < (*radacina)->info.idPacient) {
			inserareAVL(&(*radacina)->nodStanga, p);
		}
		else if (p.idPacient > (*radacina)->info.idPacient) {
			inserareAVL(&(*radacina)->nodDreapta, p);
		}
	}
	else {
		*radacina = creareNod(p);
		return;
	}

	int grad = gradEchilibru(*radacina);

	// caz stanga
	if (grad == 2) {
		// caz stanga-dreapta
		if (gradEchilibru((*radacina)->nodStanga) == -1) {
			rotireStanga(&(*radacina)->nodStanga);
			rotireDreapta(radacina);
		}
		// caz stanga-stanga
		else {
			rotireDreapta(radacina);
		}
	}

	// caz dreapta
	if (grad == -2) {
		// caz dreapta-stanga
		if (gradEchilibru((*radacina)->nodDreapta) == 1) {
			rotireDreapta(&(*radacina)->nodDreapta);
		}
		// caz dreapta-dreapta
		rotireStanga(radacina);
	}
}

//citire fisier AVL

Nod* citireAVLFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	if (file) {
		while (!feof(file)) {
			Pacient p = citirePacientDinFisier(file);

			// fata de ABC, aici nu mai apelez inserareNod,
			// ci inserareAVL, ca arborele sa se echilibreze automat
			inserareAVL(&radacina, p);

			free(p.numePacient);
		}
		fclose(file);
	}

	return radacina;
}



//dezalocarea
void dezalocare(Nod* radacina) {
	if (radacina)
	{
		dezalocare(radacina->nodDreapta);
		dezalocare(radacina->nodStanga);
		free(radacina->info.numePacient);
		free(radacina);

	}
}

int main() {
	// ==================== ABC ====================
	printf("========== ABC ==========\n");

	Nod* radacina = citireArboreFisier("pacienti.txt");

	printf("Preordine:\n");
	afisarePreordine(radacina);

	printf("\nInordine:\n");
	afisareInordine(radacina);

	printf("\nPostordine:\n");
	afisarePostordine(radacina);

	printf("\nPacient cautat dupa ID:\n");
	afisarePacient(cautareDupaID(radacina, 3)->info);

	printf("\nNumar total noduri: %d\n", nrTotalNoduri(radacina));
	printf("Numar total frunze: %d\n", nrFrunze(radacina));
	printf("Inaltime arbore: %d\n", inaltimeArbore(radacina));

	printf("\nMinim din arbore:\n");
	afisarePacient(minim(radacina)->info);

	printf("\nMaxim din arbore:\n");
	afisarePacient(maxim(radacina)->info);

	printf("\nMinim din subarborele stang:\n");
	afisarePacient(minim(radacina->nodStanga)->info);

	printf("\nMaxim din subarborele drept:\n");
	afisarePacient(maxim(radacina->nodDreapta)->info);

	// ==================== AVL ====================
	printf("\n\n========== AVL ==========\n");

	// fata de ABC, aici construim arborele cu functia de citire AVL,
	// care foloseste inserareAVL si il echilibreaza automat
	Nod* radacinaAVL = citireAVLFisier("pacienti.txt");

	// afisam doar cat sa vedem diferenta fata de ABC
	printf("Preordine AVL:\n");
	afisarePreordine(radacinaAVL);

	printf("\nInaltime AVL: %d\n", inaltimeArbore(radacinaAVL));

	dezalocare(radacina);
	radacina = NULL;

	dezalocare(radacinaAVL);
	radacinaAVL = NULL;

	return 0;
}