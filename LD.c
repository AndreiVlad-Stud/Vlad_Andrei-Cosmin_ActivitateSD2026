#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct emu {
	float greutate;
	char* denumire;
}emu;

typedef struct nod {
	emu info;
	struct nod* next;
	struct nod* prev;
}nod;

typedef struct LD {
	struct nod* cap;
	struct nod* coada;
}LD;

//creare emu

emu creareEmu(float greutate, const char* denumire) {
	emu e;
	e.greutate = greutate;

	e.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(e.denumire, denumire);

	return e;
}

//afisare emu

void afisareEmu(emu e) {
	printf("==Detalii Emu==\n");
	printf("Greutate: %.2f \n", e.greutate);
	printf("Nume: %s \n", e.denumire);
}

//afisare lista emu

void afisareListaEmu(LD lista) {
	nod* nou = lista.cap;
	while (nou) {
		afisareEmu(nou->info);
		nou = nou->next;
	}
}


//afisare emu de la final
void afisareListaEmuInvers(LD lista) {
	nod* nou = lista.coada;
	while (nou)
	{
		afisareEmu(nou->info);
		nou = nou->prev;
	}
}

//inserare

void inserareLaInceput(LD* lista, emu e) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareEmu(e.greutate, e.denumire);
	nou->prev = NULL;
	nou->next = lista->cap;

	if (lista->cap) {
		lista->cap->prev = nou;
	}
	else
	{
		lista->coada = nou;
	}

	lista->cap = nou;

}

void inserareLaFinal(LD* lista, emu e) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareEmu(e.greutate, e.denumire);
	nou->next = NULL;

	nou->prev = lista->coada;

	if (lista->coada)
	{
		lista->coada->next = nou;
	}
	else
	{
		lista->cap = nou;
	}

	lista->coada = nou;
}

//citire obiect din fisier

emu citireEmudFisier(FILE* file) {
	emu e;

	e.greutate = 0;
	e.denumire = NULL;

	char buffer[256];
	char sep[] = ",\n";

	char* token;

	fgets(buffer, sizeof(buffer), file);

	token = strtok(buffer, sep);
	e.greutate = atof(token);

	token = strtok(NULL, sep);
	e.denumire = malloc(strlen(token) + 1);
	strcpy(e.denumire, token);

	return e;

}

//citire lista de emu
LD citireListaEmu(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");

	LD nou = { NULL, NULL };
	if (file) {
		while (!feof(file)) {
			emu e = citireEmudFisier(file);
			inserareLaInceput(&nou, e);
		}
		fclose(file);
	}
	return nou;
}

//stergere dupa pozitie

void stergereDupaPozitie(LD* lista, int pozitie) {
	if (!lista->cap)
	{
		return;
	}
	nod* nou = lista->cap;

	int i = 0;

	while (nou != NULL && i < pozitie) {
		nou = nou->next;
		i++;
	}

	if (nou == NULL) {
		return;
	}

	if (nou->prev) {
		nou->prev->next = nou->next;
	}
	else
	{
		lista->cap = nou->next;
	}

	if (nou->next) {
		nou->next->prev = nou->prev;
	}
	else
	{
		lista->coada = nou->prev;
	}

	free(nou->info.denumire);
	free(nou);

}

void dezalocare(LD* lista) {
	while (lista->cap) {
		nod* nou = lista->cap;
		lista->cap = nou->next;
		free(nou->info.denumire);
		free(nou);
	}
	lista->cap = NULL;
	lista->coada = NULL;
}

int main() {
	LD lista = { NULL, NULL };

	// creare obiecte
	emu e1 = creareEmu(35.5f, "Emu Alb");
	emu e2 = creareEmu(42.0f, "Emu Rosu");
	emu e3 = creareEmu(28.7f, "Emu Verde");

	// inserare in lista
	inserareLaInceput(&lista, e1);
	inserareLaFinal(&lista, e2);
	inserareLaInceput(&lista, e3);

	printf("Afisare lista de la inceput:\n");
	afisareListaEmu(lista);

	printf("\nAfisare lista invers:\n");
	afisareListaEmuInvers(lista);

	// stergere dupa pozitie
	stergereDupaPozitie(&lista, 1);

	printf("\nDupa stergerea elementului de pe pozitia 1:\n");
	afisareListaEmu(lista);

	// dezalocare obiecte create initial
	free(e1.denumire);
	free(e2.denumire);
	free(e3.denumire);

	// dezalocare lista
	dezalocare(&lista);

	return 0;
}