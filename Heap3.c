#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Medicament {
    int idMedicament;
    char* denumire;
    float pret;
} Medicament;

typedef struct Heap {
    Medicament* vector;
    int lungime;
    int nrMedicamente;
}Heap;

Medicament constructor(int idMedicament, const char* denumire, float pret) {
    Medicament m;

    m.idMedicament = idMedicament;

    m.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(m.denumire, denumire);

    m.pret = pret;

    return m;

}

void afisareMedicament(Medicament m) {
    printf(" %d | %s | %.2f \n", m.idMedicament, m.denumire, m.pret);
}

//fct creare heap

Heap creareHeap(int lungime) {
    Heap h;
    h.lungime = lungime;
    h.nrMedicamente = 0;
    h.vector = (Medicament*)malloc(sizeof(Medicament) + lungime);

    return h;
}

void inserareHeap(Heap* heap, Medicament m) {
    if (heap->nrMedicamente <heap->lungime)
    {
        heap->vector[heap->nrMedicamente] = constructor(m.idMedicament, m.denumire, m.pret);
        int poz = heap->nrMedicamente;
        heap->nrMedicamente++;

        while (poz > 0) {
            int parinte = (poz - 1) / 2;

            if (heap->vector[poz].idMedicament>heap->vector[parinte].idMedicament)
            {
                Medicament aux = heap->vector[parinte];
                heap->vector[parinte] = heap->vector[poz];
                heap->vector[poz] = aux;
                poz = parinte;
            }
            else
            {
                break;
            }

        }

    }

}

void afisareHeap(Heap heap) {
    for (int i = 0; i < heap.nrMedicamente; i++) {
        afisareMedicament(heap.vector[i]);
    }
}

void dezalocare(Heap* heap) {
    for (int i = 0; i < heap->nrMedicamente; i++) {
        free(heap->vector[i].denumire);
    }
    free(heap->vector);
    heap->lungime = 0;
    heap->nrMedicamente = 0;
    heap->vector = NULL;
}