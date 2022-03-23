/*
* Student: Spaczai Carla Noemi
* Grupa: 30229
* Am realizat interclasarea a 'k' liste aleatoare ordonate ('n' elemente in total).
* 
* Acest algoritm are scopul de a realiza interclasarea a 'k' liste aleatoare ordonate care contin 'n' elemente in total. Cele 'n' elemente sunt impartite astfel:
* daca 'n % k != 0', primele 'k - 1' liste contin cate 'n / k + 1' elemente si ultima lista contine elementele care au mai ramas pana la n, iar daca 'n % k = 0',
* fiecare lista va avea cate 'n / k' elemente. Toate aceste elemente urmeaza sa fie puse intr-o singura lista unde trebuie sa fie ordonate. Pentru a face acest
* lucru, am ales sa imi creez o lista care sa cuprinda cele 'k' liste. Cu ajutorul primit de la 'Build-Heap' (Bottom_Up) si 'Min-Heap' (Bottom_Up_2), extragem
* primul element din fiecare lista si obtinem un heap (cu aceste elemente) care are pe prima pozitie cel mai mic element. Mutam elementul de pe prima pozitie in
* lista finala (cea care va cuprinde rezultatul final). Cu fiecare introducere de element in lista finala, introducem urmatorul element al ultimului element
* introdus in lista finala, in fostul heap. Ne folosim in continuare de 'Build-Heap' (Bottom_Up) si 'Min-Heap' (Bottom_Up_2) pentru a repeta acest proces pana
* cand se vor introduce toate elementele din toate listele in lista finala.
* 
* Complexitate: O(n*log(k)).
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler p("INTERCLASARE");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

typedef struct Nod
{
	int Data;
	struct Nod* Next;
} Nod;

typedef struct Lista
{
	Nod* First;
	Nod* Last;
} Lista;

Lista* ListaNoua()
{
	Lista* LN = (Lista*)malloc(sizeof(Lista));
	LN->First = NULL;
	LN->Last = NULL;
	return LN;
}

void InserareInLista(Lista* L, int D)
{
	Nod* NodNou = (Nod*)malloc(sizeof(Nod));
	NodNou->Data = D;
	NodNou->Next = NULL;
	if (L->First != NULL)
	{
		L->Last->Next = NodNou;
	}
	else
	{
		L->First = NodNou;
	}
	L->Last = NodNou;
}

Lista* UmplereLista(int n)
{
	Lista* L = ListaNoua();
	int v[10000];
	FillRandomArray(v, n, -150, 150, false, 1);
	for (int i = 0; i < n; i++)
	{
		InserareInLista(L, v[i]);
	}
	return L;
}

Lista** CreareKListe(int k)
{
	Lista** L = (Lista**)malloc(k * sizeof(Lista*));
	for (int i = 1; i <= k; i++)
	{
		L[i] = NULL;
	}
	return L;
}

void swap(Lista** a, Lista** b)
{
	Lista* aux = *a;
	*a = *b;
	*b = aux;
}

void Bottom_Up_2(Lista** L, int i, int s, int n) //heapify
{
	Operation OP = p.createOperation("Interclasare", n);

	int k = i;
	int left = i * 2 + 1;
	int right = (i + 1) * 2;
	if (left < s)
	{
		OP.count();
		if (L[left]->First->Data < L[i]->First->Data)
		{
			k = left;
		}
	}
	if (right < s)
	{
		OP.count();
		if (L[right]->First->Data < L[k]->First->Data)
		{
			k = right;
		}
	}
	if (k != i)
	{
		OP.count(3);
		swap(&L[i], &L[k]);
		Bottom_Up_2(L, k, s, n);
	}
}

void Bottom_Up(Lista** L, int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		Bottom_Up_2(L, i, n, n);
	}
}

Lista* Interclasare(Lista** L, int k, int n)
{
	Operation OP = p.createOperation("Interclasare", n);

	Lista* LF = ListaNoua();
	for (int j = 0; j < n; j++)
	{
		Bottom_Up(L, k);
		InserareInLista(LF, L[0]->First->Data);
		if (L[0]->First->Next == NULL)
		{
			OP.count();
			L[0] = L[k - 1];
			k--;
		}
		else
		{
			OP.count();
			L[0]->First = L[0]->First->Next;
		}
	}
	LF->Last->Next = NULL;
	return LF;
}

void Afisare(Lista* L)
{
	Nod* N = L->First;
	int i = 1;
	if (N == NULL)
	{
		printf("Nu avem elemente in lista!");
	}
	else
	{
		while (i)
		{
			printf("%d ", N->Data);
			if (N->Next != NULL)
			{
				N = N->Next;
			}
			else
			{
				i = 0;
			}
		}
	}
}

Nod* creare(int key)
{
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->Data = key;
	p->Next = NULL;
	return p;
}

Lista* inserare(int v[], int n)
{
	Lista* L = ListaNoua();
	Nod* NodNou = (Nod*)malloc(sizeof(Nod));
	NodNou->Data = v[0];
	NodNou->Next = NULL;
	L->First = NodNou;
	for (int i = 1; i < n; i++)
	{
		NodNou->Next = creare(v[i]);
		NodNou = NodNou->Next;
	}
	return L;
}

void demo()
{
	/*int k = 2, n = 10;
	//int v[] = { 1, 2, 3, 4, 11 };
	int y[] = { -1, 7, 8, 9, 10 };*/
	int k = 4, n = 20;
	int x = n;
	Lista** L = CreareKListe(k);
	/*L[0] = inserare(v, 5);
	L[1] = inserare(y, 5);*/
	for (int i = 0; i < k; i++)
	{
		if (n % k == 0)
		{
			L[i] = UmplereLista(n / k);
		}
		else
		{
			if (x / k > 1)
			{
				L[i] = UmplereLista(n / k + 1);
				x = x - n / k - 1;

			}
			else
			{
				L[i] = UmplereLista(x);
			}
		}
		Afisare(L[i]);
		/*Afisare(L[0]);
		printf("\n");
		Afisare(L[1]);*/
		printf("\n");
	}
	Lista* LF = Interclasare(L, k, n);
	Afisare(LF);
}

Lista* Interclasare_10(Lista** L, int k, int n)
{
	Operation OP = p.createOperation("Interclasare", n);

	Lista* LF = ListaNoua();
	for (int j = 0; j < n; j++)
	{
		Bottom_Up(L, k);
		InserareInLista(LF, L[0]->First->Data);
		if (L[0]->First->Next == NULL)
		{
			OP.count();
			L[0] = L[k - 1];
			k--;
		}
		else
		{
			OP.count();
			L[0]->First = L[0]->First->Next;
		}
	}
	LF->Last->Next = NULL;
	return LF;
}

Lista* Interclasare_100(Lista** L, int k, int n)
{
	Operation OP = p.createOperation("Interclasare", n);

	Lista* LF = ListaNoua();
	for (int j = 0; j < n; j++)
	{
		Bottom_Up(L, k);
		InserareInLista(LF, L[0]->First->Data);
		if (L[0]->First->Next == NULL)
		{
			OP.count();
			L[0] = L[k - 1];
			k--;
		}
		else
		{
			OP.count();
			L[0]->First = L[0]->First->Next;
		}
	}
	LF->Last->Next = NULL;
	return LF;
}

void perf()
{
	int k;
	for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int j = 0; j < NR_TESTS; j++)
		{
			k = 5;
			Lista** L = (Lista**)malloc(k * sizeof(Lista*));
			CreareKListe(k);
			Interclasare(L, k, n);
			for (int i = 1; i <= k; i++)
			{
				free(L[i]);
			}
			free(L);
			k = 10;
			Lista** L_10 = (Lista**)malloc(k * sizeof(Lista*));
			CreareKListe(k);
			Interclasare_10(L_10, k, n);
			for (int i = 1; i <= k; i++)
			{
				free(L_10[i]);
			}
			free(L_10);
			k = 100;
			Lista** L_100 = (Lista**)malloc(k * sizeof(Lista*));
			CreareKListe(k);
			Interclasare_100(L_100, k, n);
			for (int i = 1; i <= k; i++)
			{
				free(L_100[i]);
			}
			free(L_100);
		}
	}
	p.divideValues("Interclasare", NR_TESTS);
	p.divideValues("Interclasare_10", NR_TESTS);
	p.divideValues("Interclasare_100", NR_TESTS);
	p.createGroup("Comparare", "Interclasare", "Interclasare_10", "Interclasare_100");
	p.showReport();

	// (+) n = 10000, 10 <= k <= 50 (+10)
}

int main()
{
	//demo();
	perf();
	return 0;
}