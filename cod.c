#define _CRT_SECURE_NO_WARNINGS //pentru a nu mai primi eroarea de la scanf/ putem sa adaugam 4996 la propietati
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *f; //pointer pt fisier
//lista principala va contine tarile cu denumirile lor iar in sublista vor fi vecinii
typedef struct sublista_vecini {//sublista

	char *nume_vecini;
	struct sublista_vecini *next2;

}vecini;
typedef struct lista_tara {//lista

	char *nume_tara;
	struct lista_tara *next1;
	struct sublista_vecini *sublista;
}tara;

tara *primul = NULL;

vecini *introducere_vecini(vecini *lista, vecini *aux)
{
	vecini *q1, *q2;
	for (q1 = q2 = lista; q1 != NULL && strcmp(q1->nume_vecini, aux->nume_vecini) > 0; q2 = q1, q1 = q1->next2);
	if (q1 == q2) { //daca il punem la inceput
		aux->next2 = lista;
		lista = aux;
	}
	else {
		q2->next2 = aux; //daca il punem pe parcurs
		aux->next2 = q1;
	}
	return lista; //am adaugat numele tarii vecine in sublista
}
tara *introducere_tara(tara *lista, tara *aux, vecini *aux_s)
{
	tara *a1, *a2;
	for (a1 = a2 = lista; a1 != NULL && strcmp(a1->nume_tara, aux->nume_tara) < 0; a2 = a1, a1 = a1->next1);
	if (a1 != NULL && strcmp(a1->nume_tara, aux->nume_tara) == 0) {
		a1->sublista = introducere_vecini(a1->sublista, aux_s);
		free(aux);
		return lista;
		if (a1 == a2)
		{
			aux->next1 = lista;
			lista = aux;
		}
		else
		{
			a2->next1 = aux;
			aux->next1 = a1;
		}aux->sublista = introducere_vecini(aux->sublista, aux_s);
		return lista;
	}
}
void citire_fisier()
{
	tara *aux;
	vecini *aux_s;
	char nume_tara[20], nume_vecini[20];
	if ((f = fopen("tari.txt", "r")) == NULL)
	{
		printf("eroare la deschiderea fisierului\n");
		exit(1);
	}
	while (!feof(f))//atat timp cat nu am ajuns la finalul fisierului citim informatii
	{
		fscanf(f, "%s%s%s", nume_tara, nume_vecini);
		aux = (tara*)malloc(sizeof(tara));
		aux->nume_tara = (char*)malloc(strlen(nume_tara) + 1);
		strcpy(aux->nume_tara, nume_tara);
		aux->sublista = NULL;
		aux_s = (vecini*)malloc(sizeof(vecini));
		aux_s->nume_vecini = (char*)malloc(strlen(nume_vecini) + 1);
		strcpy(aux_s->nume_vecini, nume_vecini);
		primul = introducere_tara(primul, aux, aux_s);

	}
}

void afisare(tara *lista)
{
	tara *q;//lista
	vecini *p;//sublista
	for (q = lista; q != NULL; q = q->next1)//q pleaca de la primul nod al listei si atata timp cat nu ajunge la nodul null printeaza numele tarii
	{									//si apoi trece la urmatorul nod 
		printf("%s:\n", q->nume_tara);
		for (p = q->sublista; q != NULL && p != NULL; p = p->next2)  //p pleaca de la primul nod al sublistei si cat timp e diferit de null vecinii tarii 
		{
			printf("\t%s\%s\n", p->nume_vecini);
		}printf("\n");
	}

}
int main() {

	int opt;
	do
	{

		printf("\t\tmeniu\n");
		printf("0.exit\n");
		printf("1.incarcarea din fisier\n");
		printf("dati optiunea:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 0: exit(0); break;
		case 1:citire_fisier();
			//afisare(primul);
			break;
		case 2: afisare(primul);
			break;
		default: printf("aceasta optiune nu este valida!\n");
			break;
		}
	} while (opt != 0);

	return 0;
}