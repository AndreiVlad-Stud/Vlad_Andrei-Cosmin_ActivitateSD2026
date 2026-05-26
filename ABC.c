//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Carte {
//    unsigned int idCarte;
//    char* titlu;
//    float pret;
//} Carte;
//
////structura nod
//
//typedef struct Nod {
//    Carte info;
//    struct Nod* stanga;
//    struct Nod* dreapta;
//} Nod;
//
////constructor
//
//Carte creareCarte(unsigned int idCarte, const char* titlu, float pret) {
//    Carte c;
//    c.idCarte = idCarte;
//
//    c.titlu = (char*)malloc(strlen(titlu) + 1);
//    strcpy(c.titlu, titlu);
//
//    c.pret = pret;
//
//    return c;
//}
//
////fct de afisare
//
//void afisareCarte(Carte c) {
//    printf("%u | %s | %.2f\n", c.idCarte, c.titlu, c.pret);
//}
//
////citire din fisier
//Carte citireCarteDinFisier(FILE* file) {
//    Carte c;
//    c.idCarte = 0;
//    c.titlu = NULL;
//    c.pret = 0;
//
//    char buffer[256];
//    char sep[] = ",\n";
//    char* token;
//
//    if (fgets(buffer, sizeof(buffer), file) == NULL) {
//        return c;
//    }
//
//    token = strtok(buffer, sep);
//    if (token == NULL) return c;
//    c.idCarte = atoi(token);
//
//    token = strtok(NULL, sep);
//    if (token == NULL) return c;
//    c.titlu = (char*)malloc(strlen(token) + 1);
//    strcpy(c.titlu, token);
//
//    token = strtok(NULL, sep);
//    if (token == NULL) return c;
//    c.pret = atof(token);
//
//    return c;
//}
////creare nod
//
//Nod* creareNod(Carte c) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = creareCarte(c.idCarte, c.titlu, c.pret);
//    nou->stanga = NULL;
//    nou->dreapta = NULL;
//    return nou;
//}
//
//
////inserare nod
//
//Nod* inserareNod(Nod* radacina, Carte c) {
//    if (radacina == NULL) {
//        return creareNod(c);
//    }
//
//    if (c.idCarte < radacina->info.idCarte) {
//        radacina->stanga = inserareNod(radacina->stanga, c);
//    }
//    else if (c.idCarte > radacina->info.idCarte) {
//        radacina->dreapta = inserareNod(radacina->dreapta, c);
//    }
//
//    return radacina;
//}
//
////citire arbore din fisier
//Nod* citireArboreDinFisier(const char* numeFisier) {
//    FILE* file = fopen(numeFisier, "r");
//    Nod* radacina = NULL;
//
//    if (file) {
//        while (!feof(file)) {
//            Carte c = citireCarteDinFisier(file);
//            if (c.titlu != NULL) {
//                radacina = inserareNod(radacina, c);
//                free(c.titlu);
//            }
//        }
//        fclose(file);
//    }
//
//    return radacina;
//}
//
////afisarea in preordine
//void preordine(Nod* radacina) {
//    if (radacina) {
//        afisareCarte(radacina->info);
//        preordine(radacina->stanga);
//        preordine(radacina->dreapta);
//    }
//}
//
////afisarea in inordine
//void inordine(Nod* radacina) {
//    if (radacina) {
//        inordine(radacina->stanga);
//        afisareCarte(radacina->info);
//        inordine(radacina->dreapta);
//    }
//}
//
////afisarea in postordine
//
//void postordine(Nod* radacina) {
//    if (radacina) {
//        postordine(radacina->stanga);
//        postordine(radacina->dreapta);
//        afisareCarte(radacina->info);
//    }
//}
//
////fcst cautare dupa cheie
//
//Nod* cautaCarteDupaId(Nod* radacina, unsigned int idCautat) {
//    if (radacina == NULL) {
//        return NULL;
//    }
//
//    if (idCautat == radacina->info.idCarte) {
//        return radacina;
//    }
//
//    if (idCautat < radacina->info.idCarte) {
//        return cautaCarteDupaId(radacina->stanga, idCautat);
//    }
//    else {
//        return cautaCarteDupaId(radacina->dreapta, idCautat);
//    }
//}
//
////fct calcul nr total noduri
//
//int numarTotalNoduri(Nod* radacina) {
//    if (radacina == NULL) {
//        return 0;
//    }
//
//    return 1 + numarTotalNoduri(radacina->stanga) + numarTotalNoduri(radacina->dreapta);
//}
//
////fct nr total frunze
//
//int numarFrunze(Nod* radacina) {
//    if (radacina == NULL) {
//        return 0;
//    }
//
//    if (radacina->stanga == NULL && radacina->dreapta == NULL) {
//        return 1;
//    }
//
//    return numarFrunze(radacina->stanga) + numarFrunze(radacina->dreapta);
//}
//
////fct calculare inaltime
//
//int inaltimeArbore(Nod* radacina) {
//    if (radacina == NULL) {
//        return 0;
//    }
//
//    int inaltimeStanga = inaltimeArbore(radacina->stanga);
//    int inaltimeDreapta = inaltimeArbore(radacina->dreapta);
//
//    if (inaltimeStanga > inaltimeDreapta) {
//        return 1 + inaltimeStanga;
//    }
//    else {
//        return 1 + inaltimeDreapta;
//    }
//}
////fct min de dreapta
//Nod* minimDreapta(Nod* radacina) {
//    while (radacina && radacina->stanga) {
//        radacina = radacina->stanga;
//    }
//    return radacina;
//}
//
////fct stergere
//
//Nod* stergereNod(Nod* radacina, unsigned int idCautat) {
//    if (radacina == NULL) {
//        return NULL;
//    }
//
//    if (idCautat < radacina->info.idCarte) {
//        radacina->stanga = stergereNod(radacina->stanga, idCautat);
//    }
//    else if (idCautat > radacina->info.idCarte) {
//        radacina->dreapta = stergereNod(radacina->dreapta, idCautat);
//    }
//    else {
//        // cazul 1 si 2
//        if (radacina->stanga == NULL) {
//            Nod* temp = radacina->dreapta;
//            free(radacina->info.titlu);
//            free(radacina);
//            return temp;
//        }
//        else if (radacina->dreapta == NULL) {
//            Nod* temp = radacina->stanga;
//            free(radacina->info.titlu);
//            free(radacina);
//            return temp;
//        }
//
//        // cazul 3
//        Nod* temp = minimDreapta(radacina->dreapta);
//
//        free(radacina->info.titlu);
//        radacina->info = creareCarte(temp->info.idCarte, temp->info.titlu, temp->info.pret);
//
//        radacina->dreapta = stergereNod(radacina->dreapta, temp->info.idCarte);
//    }
//
//    return radacina;
//}
//
////fct de dezalocare
//
//void dezalocareArbore(Nod* radacina) {
//    if (radacina) {
//        dezalocareArbore(radacina->stanga);
//        dezalocareArbore(radacina->dreapta);
//        free(radacina->info.titlu);
//        free(radacina);
//    }
//}
//
//int main() {
//    Carte c1 = creareCarte(4, "A", 40);
//    Carte c2 = creareCarte(2, "B", 20);
//    Carte c3 = creareCarte(6, "C", 60);
//    Carte c4 = creareCarte(1, "D", 10);
//    Carte c5 = creareCarte(3, "E", 30);
//    Carte c6 = creareCarte(5, "F", 50);
//
//    Nod* radacina = NULL;
//    radacina = inserareNod(radacina, c1);
//    radacina = inserareNod(radacina, c2);
//    radacina = inserareNod(radacina, c3);
//    radacina = inserareNod(radacina, c4);
//    radacina = inserareNod(radacina, c5);
//    radacina = inserareNod(radacina, c6);
//
//    printf("Preordine:\n");
//    preordine(radacina);
//
//    printf("\nInordine:\n");
//    inordine(radacina);
//
//    printf("\nPostordine:\n");
//    postordine(radacina);
//
//    Nod* gasit = cautaCarteDupaId(radacina, 3);
//    if (gasit) {
//        printf("\nCartea gasita:\n");
//        afisareCarte(gasit->info);
//    }
//    else {
//        printf("Cartea nu a fost gasita.\n");
//    }
//
//    printf("Numar total noduri: %d\n", numarTotalNoduri(radacina));
//    printf("Numar total frunze: %d\n", numarFrunze(radacina));
//    printf("Inaltime arbore: %d\n", inaltimeArbore(radacina));
//
//    radacina = stergereNod(radacina, 4);
//
//    printf("\nDupa stergerea lui 4 - inordine:\n");
//    inordine(radacina);
//
//    dezalocareArbore(radacina);
//    radacina = NULL;
//
//    // test citire din fisier
//    Nod* radacinaFisier = citireArboreDinFisier("carti.txt");
//
//    printf("\nArbore citit din fisier - inordine:\n");
//    inordine(radacinaFisier);
//
//    dezalocareArbore(radacinaFisier);
//    radacinaFisier = NULL;
//
//    free(c1.titlu);
//    free(c2.titlu);
//    free(c3.titlu);
//    free(c4.titlu);
//    free(c5.titlu);
//    free(c6.titlu);
//
//    return 0;
//}