//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Bilet {
//    int idBilet;
//    char* numeClient;
//    float pret;
//} Bilet;
//
//typedef struct Nod {
//    Bilet info;
//    struct Nod* stanga;
//    struct Nod* dreapta;
//}Nod;
//
//Bilet constructorBilet(int idBilet, const char* numeClient, float pret) {
//    Bilet b;
//
//    b.idBilet = idBilet;
//
//    b.numeClient = (char*)malloc(strlen(numeClient) + 1);
//    strcpy(b.numeClient, numeClient);
//
//    b.pret = pret;
//
//    return b;
//}
//
//void afisareBilet(Bilet b) {
//    printf(" %d | %s | %.2f \n", b.idBilet, b.numeClient, b.pret);
//}
//
//Bilet citireBiletFisier(FILE* file) {
//    Bilet b;
//
//    b.idBilet = 0;
//    b.numeClient = NULL;
//    b.pret = 0;
//
//    char buffer[256];
//    char sep[] = ",\n";
//    char* token;
//
//    fgets(buffer, sizeof(buffer), file);
//
//    token = strtok(buffer, sep);
//
//    b.idBilet = atoi(token);
//
//    token = strtok(NULL, sep);
//
//    b.numeClient = (char*)malloc(strlen(token)+1);
//    strcpy(b.numeClient, token);
//
//    token = strtok(NULL, sep);
//
//    b.pret = atof(token);
//
//    return b;
//}
//
////creare in nod
//
//Nod* creareNod(Bilet b) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = constructorBilet(b.idBilet, b.numeClient, b.pret);
//    nou->stanga = NULL;
//    nou->dreapta = NULL;
//    return nou;
//}
//
////inserareNod
//
//Nod* inserareNod(Nod* radacina, Bilet b) {
//    if (radacina == NULL)
//    {
//        return creareNod(b);
//    }
//    if (b.idBilet<radacina->info.idBilet)
//    {
//        radacina->stanga = inserareNod(radacina->stanga, b);
//    }
//    else if(b.idBilet>radacina->info.idBilet){
//        radacina->dreapta = inserareNod(radacina->dreapta, b);
//    }
//    return radacina;
//}
//
////afisari
//
//void afisarePreordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareBilet(radacina->info);
//        afisarePreordine(radacina->stanga);
//        afisarePreordine(radacina->dreapta);
//    }
//}
//
//void afisareInordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareInordine(radacina->stanga);
//        afisareBilet(radacina->info);
//        afisareInordine(radacina->dreapta);
//    }
//}
//
//void afisarePostordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisarePostordine(radacina->stanga);
//        afisarePostordine(radacina->dreapta);
//        afisareBilet(radacina->info);
//    }
//}
//
//void dezalocare(Nod* radacina) {
//    if (radacina)
//    {
//        dezalocare(radacina->stanga);
//        dezalocare(radacina->dreapta);
//        free(radacina->info.numeClient);
//        free(radacina);
//    }
//}
//
//int main() {
//    Nod* radacina = NULL;
//
//    Bilet b1 = constructorBilet(1, "M", 685.f);
//    Bilet b2 = constructorBilet(3, "f", 44.5f);
//    Bilet b3= constructorBilet(4, "Sas", 25.f);
//
//    radacina= inserareNod(radacina, b1);
//    radacina = inserareNod(radacina, b2);
//    radacina = inserareNod(radacina, b3);
//
//    afisareInordine(radacina);
//    printf("\n");
//    afisarePreordine(radacina);
//    printf("\n");
//    afisarePostordine(radacina);
//    printf("\n");
//
//    return 0;
//}