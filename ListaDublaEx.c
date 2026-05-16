#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct film {
	int idFilm;
	char* titlu;
	char* gen;
	double durataMinute;
}film;

//definim un nod  dublu

typedef struct nod { // aici avem legaturile dintre noduri
	film info;
	struct nod* next;
	struct nod* prev;

}nod;

//definim lista dubla 

typedef struct listaDubla { //aici avem inceputul si finalul listei
	nod* cap;
	nod* final;
}listaDubla;


//functia de creare adica constructorul

film creareFilm(int idFilm, char* titlu, char* gen, double durataMinute) {
	film f;

	f.idFilm = idFilm;
	f.titlu = (char*)(malloc(strlen(titlu) + 1));
	strcpy(f.titlu, titlu);

	f.gen = (char*)malloc(strlen(gen) + 1);
	strcpy(f.gen, gen);

	f.durataMinute = durataMinute;

	return f;
}

//functie de afisare obiect film

void afisareFilm(film f) {
	printf("Id Film: %d \n",f.idFilm);
	printf("Nume Film: %s \n",f.titlu);
	printf("gen Film: %s \n",f.gen);
	printf("Durata Film: %.2f \n",f.durataMinute); //de retinut ca la double e la fel ca la float
}

//functia de afisarea  unei liste duble de filme
//o sa fie clasic, tip void ca doar afiseaza ceva
//fiind listas dubla, putem afisa din ambele sensuri

//afisare de la cap

void afisareListaFilmeInceput(listaDubla lista) {//ne folosim de listaDubla ca aici avem definit cap si final /  nu avem pointer ca doar accesam info, nu ne trebuie sa modificam nimic
	nod* temp = lista.cap;
	while (temp) {
		afisareFilm(temp->info);
		temp = temp->next;
	}
}

void afisareListaFilmeFinal(listaDubla lista) {
	nod* temp = lista.final;
	while (temp) {
		afisareFilm(temp->info);
		temp = temp->prev;
	}
}

//inserare in lista

//la inceput

void inserareLaInceput(listaDubla* lista, film f) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareFilm(f.idFilm, f.titlu, f.gen, f.durataMinute);
	nou->prev = NULL;
	nou->next = lista->cap;

	if (lista->cap) {
		lista->cap->prev = nou;
	}
	else
	{
		lista->final = nou;
	}
	lista->cap = nou;
	//ca si explicatie, noi la o lista dubla trebuie sa definim corect si inceputul si finalul. Deci in else zicem ca daca nu exista lista de cap, adunci nou-ul nostru od device final, iar la iesirea din else nou device si CAP. 
}

void inserareLaFinal(listaDubla* lista, film f) {
	nod* nou = malloc(sizeof(nod));
	nou->info = creareFilm(f.idFilm, f.titlu, f.gen, f.durataMinute);
	nou->next = NULL;
	nou->prev = lista->final; 

	if (lista->final) {
		lista->final->next = nou;
	}
	else
	{
		lista->cap = nou;
	}
	lista->final = nou;
}


//citirea din fisier a unui obiect

film citireFilmFisier(FILE* file) {
	char buffer[256];
	char sep[] = ",\n";
	char* token;

	fgets(buffer, sizeof(buffer), file);
	film f;

	token = strtok(buffer, sep);

	f.idFilm = atoi(token);

	token = strtok(NULL, sep);
	f.titlu = malloc(strlen(token) + 1);
	strcpy(f.titlu, token);

	token = strtok(NULL, sep);
	f.gen = malloc(strlen(token) + 1);
	strcpy(f.gen, token);

	token = strtok(NULL, sep);
	f.durataMinute = atof(token);


	return f;

}


//incarcare in lista dubla

listaDubla incarcareListaDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	listaDubla lista = { NULL, NULL }; // aici setam inceputul si finalul listei ca null sa stie programul ca e o lista goala

	if (file) { //verificat daca exista fisier
		while (!feof(file)) {
			film f = citireFilmFisier(file);
			inserareLaInceput(&lista, f);
		}

		fclose(file);
	}

	return lista;
}


//functiile de stergere

//dupa pozitie

void stergeNodPozitie(listaDubla* lista, int pozitie) {
	if (!lista->cap) return; // verificam daca lista e goala

	nod* temp = lista->cap; //aici incepem de la cap 
	int  i = 0; //incepem un contor

	while (temp && i < pozitie) { //aici mergem pana la pozitia ceruta 
		temp = temp->next;
		i++;
	}

	if (!temp) return; //daca pozitia ceruta nu exista, iesim

	//urmatoarele if-else-uri refac legaturile intre noduri dupa ce noi stergem nodul cerut

	if (temp->prev)  //daca temp-ul nostru are un prev (deci nu este cap)
	{
		temp->prev->next = temp->next; //face legatura intre nodul precedent si nodul urmator, scotand din schema nodul pe care vrem sa-l stergem
	}
	else 
	{
		lista->cap = temp->next; // daca notul nu are prev, inseaman ca e pe nodul de start (cap). daca stergem capul, trebuie sa mentionam ca urmatorul nod din lista o sa devina cap.
	}

	if (temp->next) { // daca nodul pe care vrem sa-l stergem are un next, trebuie sa-i refacem legatura de prev acelui nod
		temp->next->prev = temp->prev; // aici ii spunem ca prev-ul nodului urmator celui pe care vrem sa-l stergem trebuie sa pointeze de acum catre nodul precedent nodului pe care noi vrem sa-l stergem din lista
	}
	else
	{
		lista->final = temp->prev; // daca nodul nu are un next, inseamna ca suntem la coada (final), deci trebuie sa definim un nou final. Asta inseaman ca nodul precedent celui pe care-l stergem o sa fie noul final. 
	}

	free(temp->info.titlu); //eliberam memoria
	free(temp->info.gen);
	free(temp);

}

//stergere dupa un parametru anume

void stergereFilmDupaID(listaDubla* lista, int id) {
	nod* temp = lista->cap;
	if (!lista->cap) return;
	while (temp && temp->info.idFilm != id) { //atata timp cat exista temp, dar id-ul cerut nu se gaseste in nodul curent, ne deplasam la urmatorul
		temp = temp->next; 
	}

	if (!temp) return; //  daca nu mai exista temp (adica nu mai avem unde sa ne deplasam) iesim din cod

	if (temp->prev)
	{
		temp->prev->next = temp->next;
	}
	else
	{
		lista->cap = temp->next;
	}

	if (temp->next)
	{
		temp->next->prev = temp->prev;
	}
	else
	{
		lista->final = temp->prev;
	}

	free(temp->info.titlu);
	free(temp->info.gen);
	free(temp);

}


//dezalocarea

void dezalocareLista(listaDubla* lista) {
	while (lista->cap) {
		nod* temp = lista->cap;
		lista->cap = temp->next;
		free(temp->info.titlu);
		free(temp->info.gen);
		free(temp);
	}
	lista->final = NULL;
}