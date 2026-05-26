//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Angajat {
//	int idAngajat;
//	char* numeAngajat;
//	float salariu;
//}Angajat;
//
////structura nod
//
//typedef struct Nod {
//	Angajat info;
//	struct Nod* nodStanga;
//	struct Nod* nodDreapta;
//}Nod;
//
////constructor 
//Angajat constructorAngajat(int idAngajat, const char* numeAngajat, float salariu) {
//	Angajat a;
//	a.idAngajat = idAngajat;
//	a.numeAngajat = (char*)malloc(strlen(numeAngajat) + 1);
//	strcpy(a.numeAngajat, numeAngajat);
//	a.salariu = salariu;
//
//	return a;
//}
//
//void afisareAngajat(Angajat a) {
//	printf("%d | %s | %.2f \n", a.idAngajat, a.numeAngajat, a.salariu);
//}
//
////fct citire din fisier
//
//Angajat citireAngFisier(FILE* numeFisier) {
//	Angajat a;
//
//	a.idAngajat = 0;
//	a.numeAngajat = NULL;
//	a.salariu = 0;
//
//	char buffer[256];
//	char sep[] = ",\n";
//	char* token;
//
//	fgets(buffer, sizeof(buffer), numeFisier);
//
//	token = strtok(buffer, sep);
//
//	a.idAngajat = atoi(token);
//
//	token = strtok(NULL, sep);
//
//	a.numeAngajat = (char*)malloc(strlen(token) + 1);
//	strcpy(a.numeAngajat, token);
//
//	token = strtok(NULL, sep);
//
//	a.salariu = atof(token);
//
//	return a;
//
//}
//
////creare nod
//
//Nod* creareNodABC(Angajat a) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = constructorAngajat(a.idAngajat, a.numeAngajat, a.salariu);
//	nou->nodDreapta = NULL;
//	nou->nodStanga = NULL;
//
//	return nou;
//}
//
//Nod* inserareNodInArbore(Nod* radacina, Angajat a) {
//	if (radacina == NULL)
//	{
//		return creareNodABC(a);
//	}
//	if (a.idAngajat < radacina->info.idAngajat )
//	{
//		radacina->nodStanga = inserareNodInArbore(radacina->nodStanga, a);
//	}
//	if (a.idAngajat > radacina->info.idAngajat)
//	{
//		radacina->nodDreapta = inserareNodInArbore(radacina->nodDreapta, a);
//	}
//
//	return radacina;
//}
//
//void afisareArborePreordine(Nod* radacina) {
//	if (radacina)
//	{
//		afisareAngajat(radacina->info);
//		afisareArborePreordine(radacina->nodStanga);
//		afisareArborePreordine(radacina->nodDreapta);
//	}
//}
//
//void afisareArboreInordine(Nod* radacina) {
//	if (radacina)
//	{
//		afisareArboreInordine(radacina->nodStanga);
//		afisareAngajat(radacina->info);
//		afisareArboreInordine(radacina->nodDreapta);
//	}
//}
//
//void afisareArborePostordine(Nod* radacina) {
//	if (radacina)
//	{
//		afisareArborePostordine(radacina->nodStanga);
//		afisareArborePostordine(radacina->nodDreapta);
//		afisareAngajat(radacina->info);
//
//	}
//}
//
//void dezalocare(Nod* radacina) {
//	if (radacina)
//	{
//		dezalocare(radacina->nodStanga);
//		dezalocare(radacina->nodDreapta);
//		free(radacina->info.numeAngajat);
//		free(radacina);
//	}
//}
//
//int main() {
//	Nod* radacina = NULL;
//
//	Angajat a1 = constructorAngajat(4, "Ion", 4500.5f);
//	Angajat a2 = constructorAngajat(2, "Maria", 5200.0f);
//	Angajat a3 = constructorAngajat(6, "Andrei", 6100.0f);
//	Angajat a4 = constructorAngajat(1, "Elena", 3900.0f);
//	Angajat a5 = constructorAngajat(3, "Radu", 4700.0f);
//
//	radacina = inserareNodInArbore(radacina, a1);
//	radacina = inserareNodInArbore(radacina, a2);
//	radacina = inserareNodInArbore(radacina, a3);
//	radacina = inserareNodInArbore(radacina, a4);
//	radacina = inserareNodInArbore(radacina, a5);
//
//	printf("Preordine:\n");
//	afisareArborePreordine(radacina);
//
//	printf("\nInordine:\n");
//	afisareArboreInordine(radacina);
//
//	printf("\nPostordine:\n");
//	afisareArborePostordine(radacina);
//
//	free(a1.numeAngajat);
//	free(a2.numeAngajat);
//	free(a3.numeAngajat);
//	free(a4.numeAngajat);
//	free(a5.numeAngajat);
//
//	dezalocare(radacina);
//	radacina = NULL;
//
//	return 0;
//}