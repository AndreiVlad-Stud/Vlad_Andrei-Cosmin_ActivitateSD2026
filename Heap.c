//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Masina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//} Masina;
//
//typedef struct Heap {
//	int lungime;
//	int nrMasini;
//	Masina* vector;
//} Heap;
//
//// constructor obiect
//Masina creareMasina(int id, int nrUsi, float pret, const char* model) {
//	Masina m;
//	m.id = id;
//	m.nrUsi = nrUsi;
//	m.pret = pret;
//
//	m.model = (char*)malloc(strlen(model) + 1);
//	strcpy(m.model, model);
//
//	return m;
//}
//
//// afisare obiect
//void afisareMasina(Masina m) {
//	printf("Id: %d\n", m.id);
//	printf("Nr usi: %d\n", m.nrUsi);
//	printf("Pret: %.2f\n", m.pret);
//	printf("Model: %s\n\n", m.model);
//}
//
//// creare / initializare heap
//Heap initializareHeap(int lungime) {
//	Heap h;
//	h.lungime = lungime;
//	h.nrMasini = 0;
//	h.vector = (Masina*)malloc(sizeof(Masina) * lungime);
//	return h;
//}
//
//// inserare in heap maxim dupa id
//void inserareHeap(Heap* heap, Masina m) {
//	if (heap->nrMasini < heap->lungime) {
//		heap->vector[heap->nrMasini] = creareMasina(m.id, m.nrUsi, m.pret, m.model);
//
//		int poz = heap->nrMasini;
//		heap->nrMasini++;
//
//		// urcare in heap
//		while (poz > 0) {
//			int parinte = (poz - 1) / 2;
//
//			if (heap->vector[parinte].id < heap->vector[poz].id) {
//				Masina aux = heap->vector[parinte];
//				heap->vector[parinte] = heap->vector[poz];
//				heap->vector[poz] = aux;
//
//				poz = parinte;
//			}
//			else {
//				break;
//			}
//		}
//	}
//}
//
//// afisare heap
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrMasini; i++) {
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//// dezalocare heap
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->nrMasini; i++) {
//		free(heap->vector[i].model);
//	}
//
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrMasini = 0;
//}
//
//int main() {
//	Heap heap = initializareHeap(10);
//
//	Masina m1 = creareMasina(4, 4, 25000.5f, "Dacia");
//	Masina m2 = creareMasina(7, 2, 42000.0f, "BMW");
//	Masina m3 = creareMasina(2, 4, 18000.0f, "Ford");
//	Masina m4 = creareMasina(9, 4, 39000.0f, "Audi");
//
//	inserareHeap(&heap, m1);
//	inserareHeap(&heap, m2);
//	inserareHeap(&heap, m3);
//	inserareHeap(&heap, m4);
//
//	printf("Afisare heap:\n");
//	afisareHeap(heap);
//
//	free(m1.model);
//	free(m2.model);
//	free(m3.model);
//	free(m4.model);
//
//	dezalocareHeap(&heap);
//
//	return 0;
//}