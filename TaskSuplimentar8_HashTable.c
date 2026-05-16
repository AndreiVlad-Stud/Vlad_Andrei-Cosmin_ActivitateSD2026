#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Cladire {
    int id;
    char* adresa;
    int anConstructie;
    int nrEtaje;
} Cladire;

typedef struct NodHash {
    Cladire info;
    struct NodHash* next;
} NodHash;

int hashFunction(int an) {
    return an % SIZE;
}

Cladire creareCladire(int id, const char* adr, int an, int etaje) {
    Cladire c;
    c.id = id;
    c.adresa = strdup(adr);
    c.anConstructie = an;
    c.nrEtaje = etaje;
    return c;
}

void inserareCladire(NodHash** tabela, Cladire c) {
    int index = hashFunction(c.anConstructie);
    NodHash* nou = malloc(sizeof(NodHash));
    nou->info = c;
    nou->next = tabela[index];
    tabela[index] = nou;
}

void afisareCladire(Cladire c) {
    printf("ID: %d | Adresa: %s | An: %d | Etaje: %d\n", c.id, c.adresa, c.anConstructie, c.nrEtaje);
}

void afisareCluster(NodHash** tabela, int an) {
    int index = hashFunction(an);
    NodHash* temp = tabela[index];
    printf("\nCladiri din anul %d:\n", an);
    while (temp) {
        if (temp->info.anConstructie == an)
            afisareCladire(temp->info);
        temp = temp->next;
    }
}

void stergereCladireByIdAn(NodHash** tabela, int id, int an) {
    int index = hashFunction(an);
    NodHash* temp = tabela[index];
    NodHash* prev = NULL;
    while (temp) {
        if (temp->info.id == id && temp->info.anConstructie == an) {
            if (prev)
                prev->next = temp->next;
            else
                tabela[index] = temp->next;
            free(temp->info.adresa);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void stergereCladireById(NodHash** tabela, int id) {
    for (int i = 0; i < SIZE; i++) {
        NodHash* temp = tabela[i];
        NodHash* prev = NULL;
        while (temp) {
            if (temp->info.id == id) {
                if (prev)
                    prev->next = temp->next;
                else
                    tabela[i] = temp->next;
                free(temp->info.adresa);
                free(temp);
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }
}

// Obs: functia de la pct. 4 e mai generala decat cea de la pct. 3 deoarece nu presupune cunoasterea clusterului (anConstructie)

Cladire* cladiriDinAn(NodHash** tabela, int an, int* dim) {
    *dim = 0;
    int index = hashFunction(an);
    NodHash* temp = tabela[index];
    Cladire* vector = NULL;
    while (temp) {
        if (temp->info.anConstructie == an) {
            vector = realloc(vector, ((*dim) + 1) * sizeof(Cladire));
            vector[*dim].id = temp->info.id;
            vector[*dim].adresa = strdup(temp->info.adresa);
            vector[*dim].anConstructie = temp->info.anConstructie;
            vector[*dim].nrEtaje = temp->info.nrEtaje;
            (*dim)++;
        }
        temp = temp->next;
    }
    return vector;
}

void modificaAnConstructie(NodHash** tabela, int id, int anVechi, int anNou) {
    int index = hashFunction(anVechi);
    NodHash* temp = tabela[index];
    NodHash* prev = NULL;
    while (temp) {
        if (temp->info.id == id) {
            Cladire c = temp->info;
            if (prev)
                prev->next = temp->next;
            else
                tabela[index] = temp->next;
            free(temp);
            c.anConstructie = anNou;
            inserareCladire(tabela, c);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void afisareTabela(NodHash** tabela) {
    for (int i = 0; i < SIZE; i++) {
        printf("\nIndex %d:\n", i);
        NodHash* temp = tabela[i];
        while (temp) {
            afisareCladire(temp->info);
            temp = temp->next;
        }
    }
}

void eliberareTabela(NodHash** tabela) {
    for (int i = 0; i < SIZE; i++) {
        NodHash* temp = tabela[i];
        while (temp) {
            NodHash* aux = temp;
            temp = temp->next;
            free(aux->info.adresa);
            free(aux);
        }
    }
}

int main() {
    NodHash* tabela[SIZE] = { 0 };
    inserareCladire(tabela, creareCladire(1, "Str. Aviatorilor", 1990, 10));
    inserareCladire(tabela, creareCladire(2, "Bd. Unirii", 1977, 8));
    inserareCladire(tabela, creareCladire(3, "Str. Dorobanti", 1990, 5));
    inserareCladire(tabela, creareCladire(4, "Calea Victoriei", 2005, 12));

    afisareTabela(tabela);

    afisareCluster(tabela, 1990);

    modificaAnConstructie(tabela, 3, 1990, 2000);
    printf("\nDupa modificare an construire pentru id=3:\n");
    afisareTabela(tabela);

    int nr;
    Cladire* vect = cladiriDinAn(tabela, 2000, &nr);
    printf("\nCladiri din 2000 in vector:\n");
    for (int i = 0; i < nr; i++) {
        afisareCladire(vect[i]);
        free(vect[i].adresa);
    }
    free(vect);

    stergereCladireByIdAn(tabela, 1, 1990);
    stergereCladireById(tabela, 2);

    printf("\nDupa stergeri:\n");
    afisareTabela(tabela);

    eliberareTabela(tabela);
    return 0;
}