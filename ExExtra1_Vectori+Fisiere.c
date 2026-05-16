////Se definește structura Carte, care conține :
////
////titlu
////autor
////nrPagini
////pret
////
////Să se implementeze :
////
////funcție de creare obiect
////funcție de afișare obiect
////funcție de citire din fișier în vector
////funcție care creează un vector nou cu cărțile mai scumpe de 50
////funcție care salvează vectorul într - un fișier text
////funcție de dezalocare”
//
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Carte {
//	char* titlu;
//	char* autor;
//	int nrPagini;
//	float pret;
//}Carte;
//
////functie creare obiect de tip Carte aka constructor
//
//Carte creareCarte(const char* titlu, const char* autor, int nrPagini, float pret) {
//	Carte c;
//	c.titlu = malloc(strlen(c.titlu) + 1);
//	strcpy(c.titlu, titlu);
//	c.autor = malloc(strlen(c.autor) + 1);
//	strcpy(c.autor, autor);
//	c.nrPagini = nrPagini;
//	c.pret = pret;
//	return c;
//}
////functia de afisare
//
//void afisareCarte(Carte carte) {
//	printf("Titlu %s \n", carte.titlu);
//	printf("Autor %s \n", carte.autor);
//	printf("Numar Pagini %d \n", carte.nrPagini);
//	printf("Pret %.2f \n", carte.pret);
//}
//
//
//
//
//
