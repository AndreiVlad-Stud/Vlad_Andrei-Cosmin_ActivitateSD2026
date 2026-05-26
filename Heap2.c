//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Produs {
//    int idProdus;
//    char* denumire;
//    float pret;
//} Produs;
//
//typedef struct Heap {
//    Produs* vector;
//    int lungime;
//    int nrProduse;
//
//}Heap;
//
//Produs constructorProdus(int idProdus, const char* denumire, float pret) {
//    Produs p;
//
//    p.idProdus = idProdus;
//    p.denumire = (char*)malloc(strlen(denumire) + 1);
//    strcpy(p.denumire, denumire);
//
//    p.pret = pret;
//
//    return p;
//}
//
//void afisareProdus(Produs p) {
//    printf(" %d | %s | %.2f", p.idProdus, p.denumire, p.pret);
//}
//
////creare heap
//
//Heap initializareHeap(int lungime) {
//    Heap h;
//    h.vector = (Produs*)malloc(sizeof(Produs) + lungime);
//    h.lungime = lungime;
//    h.nrProduse = 0;
//    return h;
//}
//
////inserareHeap Heap
//
//void inserareHeap(Heap* heap, Produs p) {
//    if (heap->nrProduse < heap->lungime)
//    {
//        heap->vector[heap->nrProduse] = constructorProdus(p.idProdus, p.denumire, p.pret);
//
//        int poz = heap->nrProduse; //aici retinem pozitia unde am pus produsul
//        heap->nrProduse++; //crestem nr de produse din heap
//
//        while (poz > 0) { //daca pozitia >0 inseamna ca deja avem pe poz 0 parintele si putem compara cu el mai jos
//            int parinte = (poz - 1) / 2; //de memorat
//            if (heap->vector[parinte].idProdus < heap->vector[poz].idProdus) //comparare produs cu parinte. Aici zicem ca daca parintele e mai mic decat produsul, facem schimb intre pozitiile lor
//            {
//                Produs aux = heap->vector[parinte]; //facem un aux unde punem parintele
//                heap->vector[parinte] = heap->vector[poz]; //copilul ia pozitia parintelui
//                heap->vector[poz] = aux; //punem fostul parinte (care acum e in aux) pe pozitia copilului
//                poz = parinte; //spunem ca nou parinte este copilul / nodul nou
//            }
//            else {
//                break;
//            }
//        }
//    }
//}
//
////afisareHeap
//void afisareHeap(Heap heap) {
//    for (int i =0; i< heap.nrProduse; i++)
//    {
//        afisareProdus(heap.vector[i]);
//    }
//}
////dezalocare
//void dezalocare(Heap* heap) {
//    for (int i = 0; i < heap->nrProduse; i++)
//    {
//        free(heap->vector[i].denumire);
//    }
//    free(heap->vector);
//    heap->lungime = 0;
//    heap->nrProduse = 0;
//    heap->vector = NULL;
//}