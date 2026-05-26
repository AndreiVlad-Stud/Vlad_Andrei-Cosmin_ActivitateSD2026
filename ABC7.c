#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Abonament {
    int idAbonament;
    char* numeClient;
    float pretLunar;
} Abonament;

typedef struct Nod {
    Abonament info;
    struct Nod* stanga;
    struct Nod* dreapta;
}Nod;

Abonament constructor(int idAbonament, const char* numeClient, float pretLunar) {
    Abonament a;
    a.idAbonament = idAbonament;

    a.numeClient = (char*)malloc(strlen(numeClient) + 1);
    strcpy(a.numeClient, numeClient);

    a.pretLunar = pretLunar;

    return a;
}

void afisareAbonament(Abonament a) {
    printf(" %d | %s | %.2f \n", a.idAbonament, a.numeClient, a.pretLunar);
}

Nod* creareNod(Abonament a) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = constructor(a.idAbonament, a.numeClient, a.pretLunar);
    nou->stanga = NULL;
    nou->dreapta = NULL;

    return nou;
}

Nod* inserareNod(Nod* radacina, Abonament a) {
    if (radacina == NULL)
    {
        return creareNod(a);
    }
    if (radacina->info.idAbonament > a.idAbonament )
    {
        radacina->stanga = inserareNod(radacina->stanga, a);
    }
    else if (radacina->info.idAbonament < a.idAbonament)
    {
        radacina->dreapta = inserareNod(radacina->dreapta, a);
    }

    return radacina;
}

void afisarePreordine(Nod* radacina) {
    if (radacina)
    {
        afisareAbonament(radacina->info);
        afisarePreordine(radacina->stanga);
        afisarePreordine(radacina->dreapta);
    }
}

void afisareInordine(Nod* radacina) {
    if (radacina) {
        afisareInordine(radacina->stanga);
        afisareAbonament(radacina->info);
        afisareInordine(radacina->dreapta);
    }
}

void afisarePostordine(Nod* radacina) {
    if (radacina)
    {
        afisarePostordine(radacina->stanga);
        afisarePostordine(radacina->dreapta);
        afisareAbonament(radacina->info);
    }
}

//extra citire din fisier ob
Abonament citireAbonamentFisier(FILE* file) {
    Abonament a;
    a.idAbonament = 0;
    a.numeClient = NULL;
    a.pretLunar = 0;

    char buffer[256];
    char sep[] = ",\n";
    char* token;

    fgets(buffer, sizeof(buffer), file);

    token = strtok(buffer, sep);

    a.idAbonament = atoi(token);
    
    token = strtok(NULL, sep);

    a.numeClient = (char*)malloc(strlen(token) + 1);
    strcpy(a.numeClient, token);

    token = strtok(NULL, sep);

    a.pretLunar = atof(token);

    return a;

}

void dezalocare(Nod* radacina) {
    if (radacina)
    {
        dezalocare(radacina->stanga);
        dezalocare(radacina->dreapta);
        free(radacina->info.numeClient);
        free(radacina);
    }
}

int main() {
    Nod* radacina = NULL;

    Abonament abonament1 = constructor(1, "asda0", 56.f);
    Abonament abonament2 = constructor(5, "vbc", 852.f);
    Abonament abonament3 = constructor(21, "fdg", 86.f);
    Abonament abonament4 = constructor(7, "ku", 77.f);
    Abonament abonament5 = constructor(89, "fgh", 410.f);
    Abonament abonament6 = constructor(33, "ol", 56.f);

    radacina = inserareNod(radacina, abonament1);
    radacina = inserareNod(radacina, abonament2);
    radacina = inserareNod(radacina, abonament3);
    radacina = inserareNod(radacina, abonament4);
    radacina = inserareNod(radacina, abonament5);
    radacina = inserareNod(radacina, abonament6);

    afisarePreordine(radacina);
    printf("\n");
    afisareInordine(radacina);
    printf("\n");
    afisarePostordine(radacina);
    printf("\n");

    free(abonament1.numeClient);
    free(abonament2.numeClient);
    free(abonament3.numeClient);
    free(abonament4.numeClient);
    free(abonament5.numeClient);
    free(abonament6.numeClient);

    dezalocare(radacina);
    radacina = NULL;

    return 0;
}