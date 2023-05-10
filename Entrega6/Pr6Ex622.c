#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Persona{
    char nom[20];
    int nf;
    struct Persona *fills[10];
    unsigned prof;
}Persona;

typedef struct Element{
    Persona * prsn;
    struct Element * seg;
}ElementStack;

typedef struct{
    ElementStack *inici;
}Stack;

void push(Stack *, Persona *);
ElementStack* pop(Stack *);

int main()
{
    FILE * dades;
    int nfills=0,id,ll,npersones=0,i,fill;
    unsigned depth;
    Persona **llista;
    Persona * arrel;
    Stack Fila;
    Fila.inici=NULL;
    
    dades=fopen("ArbreG.csv","r");
    if(dades==NULL)
    {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    while((ll=fgetc(dades)) != EOF)
    {
        if(ll=='\n'){npersones++;}
    }
    rewind(dades);
    if((llista = (Persona **) malloc(npersones * sizeof(Persona*))) == NULL)
    {
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }
    for(i=0;i<npersones;i++)
    {
        if((llista[i] = (Persona *) malloc(sizeof(Persona))) == NULL)
        {
            printf ("\nNo es possible assignar la memoria necessaria...\n\n");
            return 1;
        }
        llista[i]->prof = UINT_MAX;
    }
    for(i=0;i<npersones;i++)
    {
        nfills=0;
        fscanf(dades,"%i;",&id);
        fscanf(dades,"%[a-zA-Z]",llista[i]->nom);
        while(fgetc(dades)!='\n')
        {
            fscanf(dades,"%i",&fill);
            llista[i]->fills[nfills]=llista[fill]; //és una adreça a memòria
            nfills++;
        }
        llista[i]->nf=nfills;
    }
    fclose(dades);
    arrel=llista[0];
    arrel->prof = 0;
    free(llista);//ja no podem seguir fent servir la llista

    push(&Fila,arrel);
    i=0;
    ElementStack* pare;
	pare=(ElementStack*)malloc(sizeof(ElementStack));
	if(pare==NULL){
		printf("No s'ha pogut fer la reserva de memòria\n");
		return 0;
	}
	printf("(Index, profunditat) Nom\n--------------------\n");
    while(Fila.inici !=NULL){
		pare = pop(&Fila);
        printf("(%d, %u) %s\nNFills= %d\n",i, pare->prsn->prof,
			pare->prsn->nom,pare->prsn->nf);
		depth = pare->prsn->prof;	//Guarda la seva profunditat
        for(int j=0; j<pare->prsn->nf; j++){
			pare->prsn->fills[j]->prof = depth+1;	//Assigna a cada fill la profunditat del pare + 1
            printf("Fill %d, %s. ", j+1, pare->prsn->fills[j]->nom);
			push(&Fila, pare->prsn->fills[j]);
        }
        if(pare->prsn->nf>0) printf("\n");
        i++;
    }
    return 0;
}

void push(Stack* Fila, Persona* prs){
	ElementStack* aux;
	aux=(ElementStack*)malloc(sizeof(ElementStack));
	if(aux==NULL){
		printf("No s'ha pogut fer la reserva de memòria\n");
		return;
	}
	aux->prsn=prs;
	aux->seg=Fila->inici;
	Fila->inici=aux;
}

ElementStack* pop(Stack* Fila){
	if(Fila->inici==NULL){
		printf("La fila ja és buida\n");
		return NULL;
	}	
	ElementStack* aux;
	aux=(ElementStack*)malloc(sizeof(ElementStack));
	if(aux==NULL){
		printf("No s'ha pogut fer la reserva de memòria\n");
		return NULL;
	}
	aux=Fila->inici;
	Fila->inici=aux->seg;
	return aux;
}
