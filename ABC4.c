//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Comanda {
//    int idComanda;
//    char* numeClient;
//    float valoare;
//} Comanda;
//
//typedef struct Nod {
//    Comanda info;
//    struct Nod* nodStanga;
//    struct Nod* nodDreapta;
//}Nod;
//
//Comanda constructorComanda(int idComanda, const char* numeClient, float valoare) {
//    Comanda c;
//
//    c.idComanda = idComanda;
//    c.numeClient = (char*)malloc(strlen(numeClient) + 1);
//    strcpy(c.numeClient, numeClient);
//    c.valoare = valoare;
//
//    return c;
//}
//
//void afisareComanda(Comanda c) {
//    printf("%d | %s | %.2f\n", c.idComanda, c.numeClient, c.valoare);
//}
//
//Nod* creareNod(Comanda c) {
//    Nod* nou = (Nod*)malloc(sizeof(Nod));
//    nou->info = constructorComanda(c.idComanda, c.numeClient, c.valoare);
//    nou->nodDreapta = NULL;
//    nou->nodStanga = NULL;
//
//    return nou;
//}
//
////citire obiect fisier
//
//Comanda citireComandaFisier(FILE* file) {
//    Comanda c;
//    c.idComanda = 0;
//    c.numeClient = NULL;
//    c.valoare = 0;
//
//    char buffer[256];
//    char sep[] = ",\n";
//    char* token;
//
//    fgets(buffer, sizeof(buffer), file);
//
//    token = strtok(buffer, sep);
//
//    c.idComanda = atoi(token);
//
//    token = strtok (NULL, sep);
//
//    c.numeClient = (char*)malloc(strlen(token) + 1);
//    strcpy(c.numeClient, token);
//    
//    token = strtok(NULL, sep);
//    c.valoare = atof(token);
//
//    return c;
//
//}
//
////inserare Nod
//
//Nod* inserareNod(Nod* radacina, Comanda c) {
//    if (radacina == NULL)
//    {
//        return creareNod(c);
//    }
//    if (c.idComanda < radacina->info.idComanda)
//    {
//        radacina->nodStanga = inserareNod(radacina->nodStanga, c);
//    }
//    else if(c.idComanda > radacina->info.idComanda){
//        radacina->nodDreapta = inserareNod(radacina->nodDreapta, c);
//    }
//
//    return radacina;
//}
//
////afisare preordine
//
//void afisarePreordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareComanda(radacina->info);
//        afisarePreordine(radacina->nodStanga);
//        afisarePreordine(radacina->nodDreapta);
//    }
//}
//
//void afisareInordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisareInordine(radacina->nodStanga);
//        afisareComanda(radacina->info);
//        afisareInordine(radacina->nodDreapta);
//    }
//
//}
//
//
//void afisrePostordine(Nod* radacina) {
//    if (radacina)
//    {
//        afisrePostordine(radacina->nodStanga);
//        afisrePostordine(radacina->nodDreapta);
//        afisareComanda(radacina->info);
//    }
//}
//
//void dezalocare(Nod* radacina) {
//    if (radacina)
//    {
//        dezalocare(radacina->nodStanga);
//        dezalocare(radacina->nodDreapta);
//        free(radacina->info.numeClient);
//        free(radacina);
//    }
//}
//
//int main() {
//    Nod* radacina = NULL;
//
//    Comanda c1 = constructorComanda(1, "Miha", 22.f);
//    Comanda c2 = constructorComanda(4, "Tiha", 9.f);
//    Comanda c3 = constructorComanda(5, "Biha", 45.f);
//    Comanda c4 = constructorComanda(6, "Riha", 66.f);
//
//    radacina = inserareNod(radacina, c1);
//    radacina = inserareNod(radacina, c2);
//    radacina = inserareNod(radacina, c3);
//    radacina = inserareNod(radacina, c4);
//
//    afisareComanda(c1);
//    printf("\n");
//    afisarePreordine(radacina);
//    printf("\n");
//    afisareInordine(radacina);
//    printf("\n");
//    afisrePostordine(radacina);
//    printf("\n");
//
//    free(c1.numeClient);
//    free(c2.numeClient);
//    free(c3.numeClient);
//    free(c4.numeClient);
//
//    dezalocare(radacina);
//    radacina = NULL;
//
//    return 0;
//}