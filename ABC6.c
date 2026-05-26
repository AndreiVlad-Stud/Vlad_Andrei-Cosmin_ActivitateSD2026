//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Film {
//    int idFilm;
//    char* titlu;
//    float durata;
//} Film;
//
//typedef struct Nod {
//    Film info;
//    struct Nod* stanga;
//    struct Nod* dreapta;
//}Nod;
//
//Film constructorFilm(int idFilm, const char* titlu, float durata) {
//    Film f;
//
//    f.idFilm = idFilm;
//
//    f.titlu = (char*)malloc(strlen(titlu) + 1);
//    strcpy(f.titlu, titlu);
//
//    f.durata = durata;
//
//    return f;
//}
//
//void afisareFilm(Film f) {
//    printf("%d | %s | %.2f \n", f.idFilm, f.titlu, f.durata);
//}
//
////creareNod
//
//Nod* creareNod(Film f) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = constructorFilm(f.idFilm, f.titlu, f.durata);
//    nou->stanga = NULL;
//    nou->dreapta = NULL;
//    return nou;
//}
//
////inserareNod
//
//Nod* inserareNod(Nod* radacina, Film f) {
//    if (radacina == NULL)
//    {
//        return creareNod(f);
//    }
//    if (f.idFilm < radacina->info.idFilm)
//    {
//        radacina->stanga = inserareNod(radacina->stanga, f);
//    }
//    else if (f.idFilm > radacina->info.idFilm) {
//        radacina->dreapta = inserareNod(radacina->dreapta, f);
//    }
//
//    return radacina;
//
//}
//
////afisarile
//
//void afisarePreordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareFilm(radacina->info);
//        afisarePreordine(radacina->stanga);
//        afisarePreordine(radacina->dreapta);
//    }
//}
//
//void afisareInordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareInordine(radacina->stanga);
//        afisareFilm(radacina->info);
//        afisareInordine(radacina->dreapta);
//    }
//}
//
//void afisarePostordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisarePostordine(radacina->stanga);
//        afisarePostordine(radacina->dreapta);
//        afisareFilm(radacina->info);
//    }
//}
//
////citire obiect fisier
//
//Film citireFilmFisier(FILE* file) {
//    Film f;
//
//    f.idFilm = 0;
//    f.titlu = 0;
//    f.durata = 0;
//
//    char buffer[256];
//    char sep[] = ",\n";
//    char* token;
//
//    fgets(buffer, sizeof(buffer), file);
//
//    token = strtok(buffer, sep);
//
//    f.idFilm = atoi(token);
//
//    token = strtok(NULL, sep);
//
//    f.titlu = (char*)malloc(strlen(token) + 1);
//    strcpy(f.titlu, token);
//
//    token = strtok(NULL, sep);
//
//    f.durata = atof(token);
//
//    return f;
//}
//
////dezalocare
//
//void dezalocare(Nod* radacina) {
//    if (radacina)
//    {
//        dezalocare(radacina->stanga);
//        dezalocare(radacina->dreapta);
//        free(radacina->info.titlu);
//        free(radacina);
//    }
//
//}
//
//int main() {
//    Nod* radacina = NULL;
//
//    Film f1 = constructorFilm(3, "asidnm", 5362.f);
//    Film f2 = constructorFilm(2, "15", 56.f);
//    Film f3 = constructorFilm(1, "rq", 69.f);
//    Film f4 = constructorFilm(7, "ad", 44.f);
//    Film f5 = constructorFilm(4, "fasf", 985.f);
//
//    radacina = inserareNod(radacina, f1);
//    radacina = inserareNod(radacina, f2);
//    radacina = inserareNod(radacina, f3);
//    radacina = inserareNod(radacina, f4);
//    radacina = inserareNod(radacina, f5);
//
//    afisareInordine(radacina);
//    printf("\n");
//    afisarePreordine(radacina);
//    printf("\n");
//    afisarePostordine(radacina);
//
//
//
//
//    free(f1.titlu);
//    free(f2.titlu);
//    free(f3.titlu);
//    free(f4.titlu);
//    free(f5.titlu);
//    dezalocare(radacina);
//    radacina = NULL;
//
//    return 0;
//}