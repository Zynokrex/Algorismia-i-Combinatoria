//Biel González	1551813
//Èric Sánchez	1523259
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define NARESTMAX 4

typedef struct {
      int narst, arestes[NARESTMAX];
}Connode;

typedef struct ElementDeCua{
    unsigned int index_node;
    struct ElementDeCua * seg;
}ElementCua;

typedef struct{
    ElementCua * inici, * final;
}UnaCua;

void posarencua(UnaCua *, unsigned int);
unsigned int treuelprimer(UnaCua *);
int IsEmpty( UnaCua Q ){ return ( Q.inici == NULL ); }
void mostracami(unsigned int, unsigned short*, unsigned);

int main(int argc, char *argv[]) {
    //només surten els fills al arxiu
    //Lectura del arxiu
	if (argc < 2) {
		printf("fileName\n");
		return -1;
	}
    unsigned nnodes=0, aux, i;
    Connode *infnodes;
    int j;
    FILE *docu;
    char *fileName = argv[1];

	if ((docu=fopen(fileName,"r"))==NULL){
        printf("No es pot obrir el fitxer\n");
        return 1;
    }
    //Llegim l'arxiu per primer cop i comptem el nombre de nodes
    while((aux=fgetc(docu)) != EOF) if(aux=='\n') nnodes++;
    rewind(docu);
    if((infnodes=(Connode*)malloc(nnodes*sizeof(Connode))) == NULL)
    {
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }
    //El llegim per segon cop i guardem els fills a cada estructura
    for (i=0; i<nnodes; i++){
       for (j=0; j<NARESTMAX; j++){
           fscanf(docu,"%i",&infnodes[i].arestes[j]);
           if(fgetc(docu)=='\n') break;
       }
       infnodes[i].narst=j+1;
    }
    fclose(docu);
        
    //Cos del programa BFS
    UnaCua Q = { NULL, NULL };
    unsigned short depth[nnodes], parent[nnodes];
    memset(depth, USHRT_MAX, nnodes*sizeof(unsigned short));
    posarencua(&Q, 0); 
    depth[0]=0U; 
    parent[0] = USHRT_MAX;
    
    printf("Les arestes en ordre d'entrada a la cua:\n0");
    while( !IsEmpty(Q) ){ 
		register unsigned short i;
		unsigned int v, s;
		v = treuelprimer(&Q); 
		for(i=0; i < infnodes[v].narst; i++) {
			s = infnodes[v].arestes[i];
			if(depth[s] == USHRT_MAX){
				printf(", %u", s); 
				posarencua(&Q, s); 
				depth[s] = depth[v] + 1; 
				parent[s] = v; 
			}
		}
	}
	
	printf("\nExisteix un camí fins el final (55), així que l'imprimim:\n");
	
	mostracami(nnodes-1, parent, nnodes);

    return 0;
}

void posarencua(UnaCua* Cua, unsigned int v){
    ElementCua* aux;
    aux=(ElementCua*)malloc(sizeof(ElementCua));
    if(aux==NULL) printf("No s'ha pogut fer la reserva de memòria\n");
    else {
        aux->index_node=v;
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

unsigned int treuelprimer( UnaCua *Q ){ 
	if( IsEmpty(*Q) ) return UINT_MAX;
	
	ElementCua *node_inicial = Q->inici;
	unsigned int v = node_inicial->index_node;
	
	Q->inici = Q->inici->seg;
	free(node_inicial);
	return v;
}

void mostracami(unsigned int index, unsigned short *parent, unsigned nnodes){
	unsigned i=index, total=0, total2;
	unsigned short *ordenat;
	while(i!=USHRT_MAX){
		i=parent[i];
		total++;
	}
	ordenat=(unsigned short*)malloc(total*sizeof(unsigned short));
	i=index;
	total2=total;
	char decorate[56]={'-','-','-','-','-','-'};
	while(i!=USHRT_MAX){
		ordenat[total2-1]=i;
		i=parent[i];
		total2--;
	}

	for(i=0; i<total; i++){
        decorate[i+5]='-';
        if(i == total-1){
            printf("%s>Final:%d\n",decorate,ordenat[i]);
        }
        else if(i == 0){
            printf("Inici:%d\n", ordenat[i]);
        }
        else printf("%s%d\n",decorate,ordenat[i]);
	}
}
