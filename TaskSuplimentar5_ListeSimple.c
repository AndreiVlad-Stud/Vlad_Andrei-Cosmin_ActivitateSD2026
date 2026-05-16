#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Avocat {
    char* nume;
    int varsta;
    int aniExperienta;
    float salariuAnual;
    char* specializare;
} Avocat;

typedef struct Nod {
    Avocat info;
    struct Nod* next;
} Nod;

Avocat creareAvocat(const char* nume, int varsta, int ani, float salariu, const char* spec) {
    Avocat a;
    a.nume = malloc(strlen(nume) + 1);
    strcpy(a.nume, nume);
    a.varsta = varsta;
    a.aniExperienta = ani;
    a.salariuAnual = salariu;
    a.specializare = malloc(strlen(spec) + 1);
    strcpy(a.specializare, spec);
    return a;
}

void afisareAvocat(Avocat a) {
    printf("%s | %d | %d | %.2f | %s\n", a.nume, a.varsta, a.aniExperienta, a.salariuAnual, a.specializare);
}

void afisareLista(Nod* cap) {
    while (cap) {
        afisareAvocat(cap->info);
        cap = cap->next;
    }
}

void inserareSortata(Nod** cap, Avocat a) {
    Nod* nou = malloc(sizeof(Nod));
    nou->info = a;
    nou->next = NULL;
    if (*cap == NULL || (*cap)->info.salariuAnual > a.salariuAnual) {
        nou->next = *cap;
        *cap = nou;
    }
    else {
        Nod* temp = *cap;
        while (temp->next && temp->next->info.salariuAnual < a.salariuAnual)
            temp = temp->next;
        nou->next = temp->next;
        temp->next = nou;
    }
}

void stergePozitie(Nod** cap, int pozitie) {
    if (*cap == NULL) return;
    Nod* temp = *cap;
    if (pozitie == 0) {
        *cap = temp->next;
        free(temp->info.nume);
        free(temp->info.specializare);
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < pozitie - 1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL) return;
    Nod* next = temp->next->next;
    free(temp->next->info.nume);
    free(temp->next->info.specializare);
    free(temp->next);
    temp->next = next;
}

Avocat* filtreazaLista(Nod* cap, int* dim) {
    *dim = 0;
    Nod* temp = cap;
    Avocat* vector = NULL;
    while (temp) {
        if (temp->info.aniExperienta > 10) {
            vector = realloc(vector, ((*dim) + 1) * sizeof(Avocat));
            vector[*dim].nume = strdup(temp->info.nume);
            vector[*dim].specializare = strdup(temp->info.specializare);
            vector[*dim].varsta = temp->info.varsta;
            vector[*dim].aniExperienta = temp->info.aniExperienta;
            vector[*dim].salariuAnual = temp->info.salariuAnual;
            (*dim)++;
        }
        temp = temp->next;
    }
    return vector;
}

void interschimbaPozitii(Nod* cap, int poz1, int poz2) {
    if (poz1 == poz2) return;
    Nod* p1 = NULL, * p2 = NULL;
    Nod* temp = cap;
    int i = 0;
    while (temp) {
        if (i == poz1) p1 = temp;
        if (i == poz2) p2 = temp;
        temp = temp->next;
        i++;
    }
    if (p1 && p2) {
        Avocat aux = p1->info;
        p1->info = p2->info;
        p2->info = aux;
    }
}

void eliberareLista(Nod** cap) {
    while (*cap) {
        Nod* temp = *cap;
        *cap = (*cap)->next;
        free(temp->info.nume);
        free(temp->info.specializare);
        free(temp);
    }
}

int main() {
    Nod* lista = NULL;
    inserareSortata(&lista, creareAvocat("Ion", 40, 5, 60000, "Penal"));
    inserareSortata(&lista, creareAvocat("Maria", 50, 25, 95000, "Civil"));
    inserareSortata(&lista, creareAvocat("George", 38, 12, 72000, "Comercial"));
    inserareSortata(&lista, creareAvocat("Ana", 33, 7, 67000, "Muncii"));
    inserareSortata(&lista, creareAvocat("Cristina", 45, 18, 88000, "Penal"));

    printf("\nLista initiala sortata dupa salariu:\n");
    afisareLista(lista);

    printf("\nDupa stergere pozitia 2:\n");
    stergePozitie(&lista, 2);
    afisareLista(lista);

    printf("\nDupa interschimbare pozitii 0 si 2:\n");
    interschimbaPozitii(lista, 0, 2);
    afisareLista(lista);

    int dim;
    Avocat* filtrati = filtreazaLista(lista, &dim);
    printf("\nVector cu avocati cu experienta > 10 ani:\n");
    for (int i = 0; i < dim; i++) {
        afisareAvocat(filtrati[i]);
        free(filtrati[i].nume);
        free(filtrati[i].specializare);
    }
    free(filtrati);

    eliberareLista(&lista);
    return 0;
}