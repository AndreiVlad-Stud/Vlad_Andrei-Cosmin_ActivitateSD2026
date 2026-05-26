#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Pacient {
	int idPacient;
	char* numePacient;
	float costTratament;
}Pacient;

typedef struct Heap {
	Pacient* vector;
	int lungime;
	int nrPacienti;
}Heap;

Pacient constructorPacient(int idPacient, const char* numePacient, float costTratament) {
	Pacient p;
	p.idPacient = idPacient;

	p.numePacient = (char*)malloc(strlen(numePacient) + 1);
	strcpy(p.numePacient, numePacient);

	p.costTratament = costTratament;

	return p;
}

void afisarePacient(Pacient p) {
	printf("%d | %s | %.2f\n", p.idPacient, p.numePacient, p.costTratament);
}

//creareHeap
Heap creareHeap(int lungime) {
	Heap h;
	h.lungime = lungime;
	h.nrPacienti = 0;
	h.vector = (Pacient*)malloc(sizeof(Pacient) + lungime);
	return h;
}
//inserare
void inserareHeap(Heap* heap, Pacient p) {
	if (heap->nrPacienti < heap->lungime)
	{
		heap->vector[heap->nrPacienti] = constructorPacient(p.idPacient, p.numePacient, p.costTratament);
		int poz = heap->nrPacienti;
		heap->nrPacienti++;

		while (poz > 0) {
			int parinte = (poz - 1) / 2;
			if (heap->vector[poz].idPacient>heap->vector[parinte].idPacient)
			{
				Pacient  aux = heap->vector[parinte];
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
//afisare
void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrPacienti; i++)
	{
		afisarePacient(heap.vector[i]);
	}

}
//dezalocare
void dezalocare(Heap* heap) {
	for (int i = 0; i < heap->nrPacienti; i++)
	{
		free(heap->vector[i].numePacient);
	}
	free(heap->vector);
	heap->lungime = 0;
	heap->nrPacienti = 0;
	heap->vector = NULL;
}