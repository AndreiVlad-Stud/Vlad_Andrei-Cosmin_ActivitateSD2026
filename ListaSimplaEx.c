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

}Comanda;

//structura nod

typedef struct Nod {
	Comanda info;
	struct Nod* next;
}Nod;

// constructor

Comanda creareComanda(unsigned int idComanda, char* dataLansare, char* numeClient, int pret) {
	Comanda c;
	c.idComanda = idComanda;

	c.dataLansare = (char*)malloc(strlen(dataLansare) + 1);
	strcpy(c.dataLansare, dataLansare);

	c.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(c.numeClient, numeClient);

	c.pret = pret;

	return c;

}

 //afisare obiect

void afisareComanda(Comanda c) {
	printf("Id Comanda: %u | Data Lansare Comanda: %s | Nume Client: %s | Pret : %d\n",
		c.idComanda, c.dataLansare, c.numeClient, c.pret);

}

//afisare lista -> aici o sa afisam ceva dinamic, deci o sa avem pointer ca sa avem o adresa de plecare

void afisareListaComenzi(Nod* cap) {
	printf("Lista comenzi\n");
	while (cap != NULL) {   //atata timp cat exista cap
		afisareComanda(cap->info); // ne folosim de functia pt afisare obiect ca sa arata informatiile din cap
		cap = cap->next; // ne deplasam in urmatorul nod
	}
}

//
//functiile de inserare. La lista simpla avem inserare la inceput si inserare la final
//trebuie sa setam doar next-ul pt nou nod in functie de unde o sa fie acesta pozitionat

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

	if (*cap == NULL)
	{
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

//functia de citire obiect din fisier

Comanda citesteCoamndaDinFisier(FILE* file) {
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
	if (aux == NULL) return c;
	c.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy(c.numeClient, aux);

	aux = strtok(NULL, sep);
	if (aux == NULL) return c;
	c.pret = atoi(aux);

	return c;
}

//facem functia de citiree lista de obiected din fisier
// fiind vorba de o lista, o sa avem fie un for sau un while.
// o sa ne folosim de functia noastra de mai sus care citeste un obiect
// o sa fie clar de tip nod pt ca este o lista de obiecte, nu un simplu obiect

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (!file) return NULL;

	Nod* lista = NULL;

	while (!feof(file)) {
		Comanda c = citesteCoamndaDinFisier(file);

		if (c.dataLansare != NULL && c.numeClient != NULL) {
			inserareInceput(&lista, c);
			free(c.dataLansare);
			free(c.numeClient);
		}
	}

	fclose(file);
	return lista;

}

 //functiile de stergere

void  stergereNodPozitie(Nod** cap, int pozitie) {
	if (*cap == NULL) return;

	if (pozitie == 0) { //cazul in care sterg primul nod adica capul adica pozitia index  = 0
		Nod* temp = *cap;

		*cap = (*cap)->next;

		free(temp->info.dataLansare);
		free(temp->info.numeClient);
		free(temp);
		return;
	}

	Nod* curent = *cap;
	int i = 0;

	while (curent != NULL && i < pozitie - 1) { //aici ajungem pe nodul dinaintea celui pe care vrem sa-l stergem. Asta pt a face legatura intre nodul curent, si next-ul nodului pe care-l stergem
		curent = curent->next; //aici mergem la nodul urmator
		i++;
	}

	if (curent == NULL || curent->next == NULL) return; //tratam cazul in case curent sau curent de next este null, adica nodul pe care vrem sa-l stergem nu exista

	Nod* temp = curent->next; //aici ii spunem ca vrem ca noul nostru nod sa fie pe pozitia nodului urmator celui la care am ajuns cu while-ul de mai sus

	curent->next = temp->next; //aici ii spunem ca nodul nostru curent (danaintea celui pe care vrem sa-l stergem) trebuie sa pointeze catre nodul urmator celui pe care-l stergem, adica rupem legatura cu nodul pe care-l stergem
	free(temp->info.dataLansare);
	free(temp->info.numeClient);
	free(temp);
}


//stergere dupa un anumit parametru

void stergereComandaDupaID(Nod** cap, unsigned int idCautat) {
	while (*cap != NULL && (*cap)->info.idComanda == idCautat) {//trateaza cazul in care primul nod din lista trebuie sters
		Nod* temp = *cap; //Salvezi nodul curent de la început într-un pointer temporar, ca să-l poți elibera după.
		*cap = (*cap)->next; //cap->next o sa devina nou cap
		free(temp->info.dataLansare); //eliberam memoria in temp (fostul cap)
		free(temp->info.numeClient);
		free(temp);

		//dupa se repeta si merge mai departe pana cand primul nod din lista nu o sa mai contina parametru dorit
	}

	if (*cap == NULL) return; //basically daca cap == NULL, inseamna ca nu existas lista deci nu avem ce sterge
	//trebuie pus aici pt ca, dupa ce am sters noduri de mai sus, posibil ca lista sa devica goala

	Nod* curent = *cap; //ne facem un nou nod care retine info din cap. cap acum nu mai contine atributul dupa care noi stergem

	while (curent->next != NULL) { // atata timp cat avem un next, pt ca daca nu avem, inseamna ca nu mai avem noduri care sa contina val dupa care stergem, deoarece primul while se ocupa sa stearga doar din cap;

		if (curent->next->info.idComanda == idCautat) //daca in next-ul nodului curent gasim valoarea doria
		{
			Nod* temp = curent->next; //ne facem un nou nod care retine ce este in next-ul nodului in care ne aflam
			curent->next = temp->next; //legam nodul curent cu cel de dupa temp (adica dupa cel pe care vrem sa-l stergem)
			free(temp->info.dataLansare);
			free(temp->info.numeClient);
			free(temp);
		}
		else
		{
			curent = curent->next; //daca in next nu gasim valoarea dorita dupa care stergem, setam nodul de "inceput cautare" pe urmatorul nod si se reia procesul
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