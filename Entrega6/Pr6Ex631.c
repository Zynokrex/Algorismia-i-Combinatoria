#include <stdio.h>
#include <stdlib.h>
#define FILLS_MAX 25

typedef struct Persona{
    char nom[20];
    int nf;
    struct Persona **fills;
}Persona;

int main()
{
    FILE * dades;
    int nfills=0,id,ll,npersones=0,i,j;
    int fill;
    Persona **llista;
    
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
            nfills++;
        }
        llista[i]->nf=nfills;
	}
	rewind(dades);
	for(i=0;i<npersones;i++)
    {
        if((llista[i]->fills = (Persona **) malloc((llista[i]->nf)*sizeof(Persona*))) == NULL)
        {
            printf ("\nNo es possible assignar la memoria necessaria...\n\n");
            return 1;
        }
    }
    for(i=0;i<npersones;i++)
    {
        fscanf(dades,"%i;",&id);
        fscanf(dades,"%[a-zA-Z]",llista[i]->nom);
        j=0;
        while(fgetc(dades)!='\n')
        {
            fscanf(dades,"%i",&fill);
            llista[i]->fills[j] = llista[fill];
            j++;
        }
	}
    fclose(dades);
    for(i=0;i<npersones;i++)
    {
        printf("(%d) %s\nNFills= %d\n",i,llista[i]->nom,llista[i]->nf);
        for(fill=0;fill<llista[i]->nf;fill++)
        {
            printf("Fill %d, %s. ",fill+1,llista[i]->fills[fill]->nom);
        }
        if(llista[i]->nf>0) printf("\n");
    }
    return 0;
}
