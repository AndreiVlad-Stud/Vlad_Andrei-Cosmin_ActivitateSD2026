#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITATE 100

typedef struct Pacient {
    char* nume;
    int varsta;
    int gradUrgenta;  // 1-10
    int sositCuAmbulanta; // 0 sau 1
} Pacient;

typedef struct Heap {
    Pacient* vector;
    int dim;
} Heap;

int prioritate(Pacient p) {
    return p.gradUrgenta + (p.sositCuAmbulanta ? 5 : 0);
}

Pacient crearePacient(const char* nume, int varsta, int grad, int ambulanta) {
    Pacient p;
    p.nume = strdup(nume);
    p.varsta = varsta;
    p.gradUrgenta = grad;
    p.sositCuAmbulanta = ambulanta;
    return p;
}

void afisarePacient(Pacient p) {
    printf("%s | %d ani | Urgenta: %d | Ambulanta: %s\n", p.nume, p.varsta, p.gradUrgenta, p.sositCuAmbulanta ? "DA" : "NU");
}

void swap(Pacient* a, Pacient* b) {
    Pacient t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(Heap* h, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (prioritate(h->vector[index]) > prioritate(h->vector[parent])) {
            swap(&h->vector[index], &h->vector[parent]);
            index = parent;
        }
        else break;
    }
}

void heapifyDown(Heap* h, int index) {
    int max = index;
    int st = 2 * index + 1;
    int dr = 2 * index + 2;
    if (st < h->dim && prioritate(h->vector[st]) > prioritate(h->vector[max])) max = st;
    if (dr < h->dim && prioritate(h->vector[dr]) > prioritate(h->vector[max])) max = dr;
    if (max != index) {
        swap(&h->vector[index], &h->vector[max]);
        heapifyDown(h, max);
    }
}

void inserareHeap(Heap* h, Pacient p) {
    if (h->dim < CAPACITATE) {
        h->vector[h->dim] = p;
        heapifyUp(h, h->dim);
        h->dim++;
    }
}

Pacient extrageMax(Heap* h) {
    Pacient top = h->vector[0];
    h->vector[0] = h->vector[h->dim - 1];
    h->dim--;
    heapifyDown(h, 0);
    return top;
}

void afisareHeap(Heap h) {
    printf("\nPacienti in Heap:\n");
    for (int i = 0; i < h.dim; i++) {
        afisarePacient(h.vector[i]);
    }
}

void eliberareHeap(Heap* h) {
    for (int i = 0; i < h->dim; i++) {
        free(h->vector[i].nume);
    }
    free(h->vector);
    h->dim = 0;
}

int main() {
    Heap h;
    h.vector = malloc(CAPACITATE * sizeof(Pacient));
    h.dim = 0;

    inserareHeap(&h, crearePacient("Ion", 60, 6, 1));
    inserareHeap(&h, crearePacient("Maria", 45, 8, 0));
    inserareHeap(&h, crearePacient("Andrei", 34, 9, 1));
    inserareHeap(&h, crearePacient("Elena", 27, 3, 0));
    inserareHeap(&h, crearePacient("Vlad", 70, 7, 1));

    afisareHeap(h);

    printf("\nExtragere pacienti in ordinea urgentei:\n");
    while (h.dim > 0) {
        Pacient p = extrageMax(&h);
        afisarePacient(p);
        free(p.nume);
    }

    eliberareHeap(&h);
    return 0;
}