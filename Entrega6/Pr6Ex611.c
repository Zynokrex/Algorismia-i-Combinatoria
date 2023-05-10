#include <stdio.h>
#include <stdlib.h>

typedef struct Persona{
    char nom[20];
    int nf;
    struct Persona *fills[10];
}Persona;

typedef struct Element{
    Persona * prsn;
    struct Element * seg;
}ElementCua;

typedef struct{
    ElementCua * inici, * final;
}UnaCua;

void posarencua(UnaCua *, Persona *);
void treuelprimer(UnaCua *);

int main()
{
    FILE * dades;
    int nfills=0,id,ll,npersones=0,i;
    int fill;
    Persona **llista;
    Persona * arrel;
    UnaCua Pendents = {NULL, NULL};
    
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
    }
    for(i=0;i<npersones;i++)
    {
        nfills=0;
        fscanf(dades,"%i;",&id);
        fscanf(dades,"%[a-zA-Z]",llista[i]->nom);
        while(fgetc(dades)!='\n')
        {
            fscanf(dades,"%i",&fill);
            llista[i]->fills[nfills]=llista[fill]; //es una adreça a memòria
            nfills++;
        }
        llista[i]->nf=nfills;
    }
    fclose(dades);
    arrel=llista[0];
    free(llista);//ja no podem seguir fent servir la llista

    posarencua(Pendents,arrel);
    while(Pendents.inici !=NULL){
        //Mostrar la info de Pendents.inici
        //Afegir els fills de Pendents.inici a la cua

    }
    /* s'ha de substituir per seguir l'arbre en format cua
    for(i=0;i<npersones;i++)
    {
        printf("(%d) %s\nNFills= %d\n",i,llista[i]->nom,llista[i]->nf);
        for(fill=0;fill<llista[i]->nf;fill++)
        {
            printf("Fill %d, %s. ",fill+1,llista[i]->fills[fill]->nom);
        }
        if(llista[i]->nf>0) printf("\n");
    }*/
    return 0;
}

void posarencua(UnaCua* Cua, Persona* prs){
	ElementCua* aux;
	aux=(ElementCua*)malloc(sizeof(ElementCua));
	if(aux==NULL) printf("No s'ha pogut fer la reserva de memòria\n");
	else {
		aux->prsn=prs;
		aux->seg=NULL;
		if(Cua->inici==NULL){
			Cua->inici=aux;
			Cua->final=aux;
		}else{
			Cua->final->seg=aux;
			Cua->final=aux;
		}
	}
}

void treuelprimer(UnaCua* Cua){
	if(Cua->inici==NULL) printf("La cua ja és buida\n");
	else{
		ElementCua* aux;
		aux=(ElementCua*)malloc(sizeof(ElementCua));
		if(aux==NULL) printf("No s'ha pogut fer la reserva de memòria\n");
		else {
			aux=Cua->inici;
			Cua->inici=aux->seg;
			free(aux);
		}
	}
}
