#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Comanda {
	unsigned int idComanda;
	char* dataLansare;
	char* numeClient;
	int pret;
} Comanda;

// structura nod
typedef struct Nod {
	Comanda info;
	struct Nod* next;
} Nod;

// constructor
Comanda creareComanda(unsigned int idComanda, const char* dataLansare, const char* numeClient, int pret) {
	Comanda c;
	c.idComanda = idComanda;

	c.dataLansare = (char*)malloc(strlen(dataLansare) + 1);
	strcpy(c.dataLansare, dataLansare);

	c.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(c.numeClient, numeClient);

	c.pret = pret;

	return c;
}

// afisare obiect
void afisareComanda(Comanda c) {
	printf("Id Comanda: %u | Data Lansare Comanda: %s | Nume Client: %s | Pret: %d\n",
		c.idComanda, c.dataLansare, c.numeClient, c.pret);
}

// afisare lista
void afisareListaComenzi(Nod* cap) {
	printf("Lista comenzi:\n");
	while (cap != NULL) {
		afisareComanda(cap->info);
		cap = cap->next;
	}
}

// functiile de inserare
void inserareInceput(Nod** cap, Comanda c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareComanda(c.idComanda, c.dataLansare, c.numeClient, c.pret);
	nou->next = *cap;
	*cap = nou;
}

void inserareFinal(Nod** cap, Comanda c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareComanda(c.idComanda, c.dataLansare, c.numeClient, c.pret);
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

// functia de citire obiect din fisier
Comanda citesteComandaDinFisier(FILE* file) {
	Comanda c;
	c.idComanda = 0;
	c.dataLansare = NULL;
	c.numeClient = NULL;
	c.pret = 0;

	char buffer[256];
	char sep[] = ",\n";
	char* aux;

	if (fgets(buffer, sizeof(buffer), file) == NULL) {
		return c;
	}

	aux = strtok(buffer, sep);
	if (aux == NULL) return c;
	c.idComanda = (unsigned int)atoi(aux);

	aux = strtok(NULL, sep);
	if (aux == NULL) return c;
	c.dataLansare = (char*)malloc(strlen(aux) + 1);
	strcpy(c.dataLansare, aux);

	aux = strtok(NULL, sep);
	if (aux == NULL) {
		free(c.dataLansare);
		c.dataLansare = NULL;
		return c;
	}
	c.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy(c.numeClient, aux);

	aux = strtok(NULL, sep);
	if (aux == NULL) {
		free(c.dataLansare);
		free(c.numeClient);
		c.dataLansare = NULL;
		c.numeClient = NULL;
		return c;
	}
	c.pret = atoi(aux);

	return c;
}

// functia de citire lista de obiecte din fisier
Nod* citireListaComenziDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) return NULL;

	Nod* lista = NULL;

	while (!feof(file)) {
		Comanda c = citesteComandaDinFisier(file);

		if (c.dataLansare != NULL && c.numeClient != NULL) {
			inserareInceput(&lista, c);
			free(c.dataLansare);
			free(c.numeClient);
		}
	}

	fclose(file);
	return lista;
}

// functiile de stergere
void stergereNodPozitie(Nod** cap, int pozitie) {
	if (*cap == NULL) return;

	if (pozitie == 0) {
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.dataLansare);
		free(temp->info.numeClient);
		free(temp);
		return;
	}

	Nod* curent = *cap;
	int i = 0;

	while (curent != NULL && i < pozitie - 1) {
		curent = curent->next;
		i++;
	}

	if (curent == NULL || curent->next == NULL) return;

	Nod* temp = curent->next;
	curent->next = temp->next;
	free(temp->info.dataLansare);
	free(temp->info.numeClient);
	free(temp);
}

// stergere dupa un anumit parametru
void stergereComandaDupaID(Nod** cap, unsigned int idCautat) {
	while (*cap != NULL && (*cap)->info.idComanda == idCautat) {
		Nod* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.dataLansare);
		free(temp->info.numeClient);
		free(temp);
	}

	if (*cap == NULL) return;

	Nod* curent = *cap;

	while (curent->next != NULL) {
		if (curent->next->info.idComanda == idCautat) {
			Nod* temp = curent->next;
			curent->next = temp->next;
			free(temp->info.dataLansare);
			free(temp->info.numeClient);
			free(temp);
		}
		else {
			curent = curent->next;
		}
	}
}

void dezalocareLista(Nod** cap) {
	while (*cap) {
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux->info.dataLansare);
		free(aux->info.numeClient);
		free(aux);
	}
}

int main() {
	Nod* lista = NULL;

	Comanda c1 = creareComanda(1, "2025-05-01", "Ion", 120);
	Comanda c2 = creareComanda(2, "2025-05-02", "Maria", 250);
	Comanda c3 = creareComanda(3, "2025-05-03", "Andrei", 180);

	inserareInceput(&lista, c1);
	inserareFinal(&lista, c2);
	inserareInceput(&lista, c3);

	printf("Lista initiala:\n");
	afisareListaComenzi(lista);

	printf("\nDupa stergerea pozitiei 1:\n");
	stergereNodPozitie(&lista, 1);
	afisareListaComenzi(lista);

	printf("\nDupa stergerea comenzii cu ID = 1:\n");
	stergereComandaDupaID(&lista, 1);
	afisareListaComenzi(lista);

	free(c1.dataLansare);
	free(c1.numeClient);
	free(c2.dataLansare);
	free(c2.numeClient);
	free(c3.dataLansare);
	free(c3.numeClient);

	dezalocareLista(&lista);

	return 0;
}