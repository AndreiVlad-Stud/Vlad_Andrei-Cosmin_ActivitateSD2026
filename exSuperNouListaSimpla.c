#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bilet {
	unsigned int idBilet;
	char* numeClient;
	float pret;
}bilet;
//structura nod

typedef struct nod {
	bilet info;
	struct nod* next;
}nod;

//constructor bilet

bilet constructorBilet(unsigned int idBilet, const char* numeClient, float pret) {
	bilet b;

	b.idBilet = idBilet;
	b.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(b.numeClient, numeClient);

	b.pret = pret;

	return b;
}

//afisare bilet

void afisareBilet(bilet b) {
	printf("==Detalii Bilet==\n");
	printf("ID Bilet: %u\n", b.idBilet);
	printf("Nume Client: %s\n", b.numeClient);
	printf("Pret Bilet: %.2f\n", b.pret);
}

void afisareListaBilete(nod* cap) {
	while (cap) {
		afisareBilet(cap->info);
		cap = cap->next;
	}
}

//afaugare nod la inceput

void adaugareNodLaInceput(nod** cap, bilet b) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = constructorBilet(b.idBilet, b.numeClient, b.pret);

	nou->next = *cap;
	*cap = nou;
}

void adaugareLaFinal(nod** cap, bilet b) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = constructorBilet(b.idBilet, b.numeClient, b.pret);
	nou->next = NULL;

	if (!*cap) {
		*cap = nou;
	}
	else {
		nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

//citire fisier
bilet citireBiletDinFisier(FILE* file) {
	bilet b;

	char buffer[256];
	char sep[] = ",\n";
	char* token;

	b.idBilet = 0;
	b.numeClient = NULL;
	b.pret = 0;

	fgets(buffer, sizeof(buffer), file);

	token = strtok(buffer, sep);

	b.idBilet = atoi(token);

	token = strtok(NULL, sep);

	b.numeClient = malloc(strlen(token) + 1);
	strcpy(b.numeClient, token);

	token = strtok(NULL, sep);
	b.pret = atof(token);

	return b;

}

//citire lista din fisier
nod* citireLista(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		return NULL;
	}

	nod* nou = NULL;

	while (!feof(file)) {
		bilet b = citireBiletDinFisier(file);
		if (b.numeClient != NULL)
		{
			adaugareNodLaInceput(&nou, b);
			free(b.numeClient);
		}
	}
	fclose(file);
	return nou;
}

//stergere nod

void stergereNod(nod** cap, int pozitie) {
	if (!*cap)
	{
		return;
	}

	if (pozitie == 0) {
		nod* nou = *cap;
		*cap = (*cap)->next;
		free(nou->info.numeClient);
		free(nou);
		return;
	}

	nod* temp = *cap;
	int i = 0;
	while (temp && i < pozitie - 1) {
		temp = temp->next;
		i++;
	}

	if (temp == NULL || temp->next == NULL) {
		return;
	}

	nod* nou = temp->next;
	temp->next = nou->next;

	free(nou->info.numeClient);
	free(nou);
}
void dezalocare(nod** cap) {
	while (*cap) {
		nod* nou = *cap;
		*cap = (*cap)->next;
		free(nou->info.numeClient);
		free(nou);
	}
}

int main() {
	nod* lista = NULL;

	// creare bilete
	bilet b1 = constructorBilet(1, "Ion", 45.5f);
	bilet b2 = constructorBilet(2, "Maria", 60.0f);
	bilet b3 = constructorBilet(3, "Andrei", 32.75f);

	// adaugare la inceput
	adaugareNodLaInceput(&lista, b1);
	adaugareNodLaInceput(&lista, b2);

	// adaugare la final
	adaugareLaFinal(&lista, b3);

	printf("Lista dupa adaugari:\n");
	afisareListaBilete(lista);

	// stergere nod de pe pozitia 1
	stergereNod(&lista, 1);

	printf("\nLista dupa stergerea de pe pozitia 1:\n");
	afisareListaBilete(lista);

	// dezalocare bilete initiale (copiile lor sunt deja in lista)
	free(b1.numeClient);
	free(b2.numeClient);
	free(b3.numeClient);

	// dezalocare lista
	dezalocare(&lista);

	// citire din fisier
	printf("\nLista citita din fisier:\n");
	lista = citireLista("bilete.txt");
	afisareListaBilete(lista);

	dezalocare(&lista);

	return 0;
}