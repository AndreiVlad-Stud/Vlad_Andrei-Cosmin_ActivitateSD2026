#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct abonament {
	unsigned int idAbonament;
	char* numeClient;
	char* tipAbonament;
	float pret;
	int numarSedinte;
}abonament;

typedef struct nod {
	abonament info;
	struct nod* next;
}nod;

//functia de creere

abonament creareAbonament(unsigned int idAbonament, const char* numeClient, const char* tipAbonament, float pret, int numarSedinte) {
	abonament a;

	a.idAbonament = idAbonament;

	a.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(a.numeClient, numeClient);

	a.tipAbonament = (char*)malloc(strlen(tipAbonament) + 1);
	strcpy(a.tipAbonament, tipAbonament);

	a.pret = pret;

	a.numarSedinte = numarSedinte;

	return a;
}

//functia de afisare

void afisareAbonament(abonament a) {
	printf("ID Abonament: %u\n", a.idAbonament);
	printf("Nume Client: %s\n", a.numeClient);
	printf("Tip Abonament: %s\n", a.tipAbonament);
	printf("Pret: %.2f\n", a.pret);
	printf("Numar Sedinte: %d\n", a.numarSedinte);
	printf("\n\n");
}

//Implementați o funcție care afișează toate abonamentele din listă.

void afisareListaAbonamente(nod* cap) {
	printf("== Lista Abonamente ==");
	while (cap) {
		afisareAbonament(cap->info);
		cap = cap->next;
	}

}

// adaugare in lista la inceput

void adaugareAbonamentLaInceput(nod** cap, abonament a) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareAbonament(a.idAbonament, a.numeClient, a.tipAbonament, a.pret, a.numarSedinte);

	nou->next = *cap;

	*cap = nou;
}

// adaugare in lista la final

void adaugareAbonamentLaFinal(nod** cap, abonament a) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareAbonament(a.idAbonament, a.numeClient, a.tipAbonament, a.pret, a.numarSedinte);
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else
	{
		nod* temp = *cap;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}

}


//citirea unui obiect din fisier

abonament citireAbonamentDinFisier(FILE* file) {
	abonament a;

	a.idAbonament = 0;
	a.numeClient = NULL;
	a.tipAbonament = NULL;
	a.pret = 0;
	a.numarSedinte = 0;

	char buffer[256];
	char separator[] = ",\n";

	char* token;

	fgets(buffer, sizeof(buffer), file);

	token = strtok(buffer, separator);

	a.idAbonament = atoi(token);

	token = strtok(NULL, separator);
	a.numeClient = malloc(strlen(token) + 1);
	strcpy(a.numeClient, token);

	token = strtok(NULL, separator);
	a.tipAbonament = malloc(strlen(token) + 1);
	strcpy(a.tipAbonament, token);

	token = strtok(NULL, separator);
	a.pret = atof(token);

	token = strtok(NULL, separator);
	a.numarSedinte = atoi(token);

	return a;

}

//citire din fisier a unei liste

nod* citireListaAbonamenteFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) return NULL;

	nod* lista = NULL;

	while (!feof(file)) {
		abonament a = citireAbonamentDinFisier(file);
		if (a.numeClient != NULL && a.tipAbonament != NULL) {
			adaugareAbonamentLaInceput(&lista, a);
			free(a.numeClient);
			free(a.tipAbonament);
		}
	}
	fclose(file);
	return lista;

}


///functia de stergere

void stergereNodPozitie(nod** cap, int pozitie) {
	if (*cap == NULL) return;

	if (pozitie == 0) {
		nod* temp = *cap;
		*cap = (*cap)->next;

		free(temp->info.numeClient);
		free(temp->info.tipAbonament);
		free(temp);

		return;
	}

	nod* curent = *cap;
	int i = 0;



	while (curent != NULL && i < pozitie - 1) {
		curent = curent->next;
		i++;
	}

	if (curent == NULL || curent->next == NULL) return;


	nod* temp = curent->next;
	curent->next = temp->next;

	free(temp->info.numeClient);
	free(temp->info.tipAbonament);
	free(temp);

}

//Implementați o funcție care calculează valoarea totală a tuturor abonamentelor din listă și afișează rezultatul în main(). 

float calculeazaValoareTotalaAbonamente(nod* cap) {
	float sumaTotala = 0;
	nod* aux = cap;

	while (aux) {
		sumaTotala += aux->info.pret;
		aux = aux->next;
	}

	return sumaTotala;
}

//Implementați o funcție care modifică prețul pentru abonamentele de un anumit tip primit ca parametru.

void modificarePret(nod* cap, const char* tipAbModificata, float pretNou) {
	nod* aux = cap;
	while (aux) {
		if (strcmp(aux->info.tipAbonament, tipAbModificata) == 0) {
			aux->info.pret = pretNou;
		}
		aux = aux->next;
	}
}

//Implementați o funcție care determină numărul de abonamente cu numarSedinte mai mare decât o valoare primită ca parametru. 

void determinareNrAbonamente(nod* cap, int valoareSedinte) {
	nod* aux = cap;
	int contor = 0;
	while (aux) {
		if (aux->info.numarSedinte > valoareSedinte)
		{
			contor++;
		}
		aux = aux->next;
	}

	printf("\n Numarul de abonamente cu numar de sedinte mai mare decat valoarea data este: %d\n", contor);
}


void dezalocare(nod** cap) {
	while (*cap) {
		nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux->info.numeClient);
		free(aux->info.tipAbonament);
		free(aux);

	}
}

int main() {

	nod* listaSimpla = NULL;

	abonament a1 = creareAbonament(3, "Ion", "Top", 22.5f, 22);
	abonament a2 = creareAbonament(2, "Mihai", "Mid", 252.5f, 33);
	abonament a3 = creareAbonament(1, "Razvan", "Jos", 32.5f, 21);

	adaugareAbonamentLaInceput(&listaSimpla, a1);
	adaugareAbonamentLaInceput(&listaSimpla, a2);
	adaugareAbonamentLaInceput(&listaSimpla, a3);

	afisareListaAbonamente(listaSimpla);

	printf("Suma totala a abonamentelor este: %.2f\n", calculeazaValoareTotalaAbonamente(listaSimpla));


	modificarePret(listaSimpla, "Top", 99.99f);

	printf("\nDupa modificare:\n");
	afisareListaAbonamente(listaSimpla);

	printf("Suma totala a abonamentelor este: %.2f\n", calculeazaValoareTotalaAbonamente(listaSimpla));

	determinareNrAbonamente(listaSimpla, 21);


	free(a1.numeClient);
	free(a1.tipAbonament);
	free(a2.numeClient);
	free(a2.tipAbonament);
	free(a3.numeClient);
	free(a3.tipAbonament);

	dezalocare(&listaSimpla);

	return 0;
}