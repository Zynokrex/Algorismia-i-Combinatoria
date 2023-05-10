// Èric Sánchez NIU 1523259
// Biel González NIU 1551813

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned n1,n2,estat;
}aresta;
typedef struct
{
    unsigned *nodes;
    unsigned *arvis;
    int naresvisit;
}estructuracami;

unsigned arestesdelnode(unsigned ,unsigned [], unsigned);
unsigned valencia(aresta*, unsigned, unsigned);

aresta *larestes;

int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("fileName\n");
		return -1;
	}
	//Obre el document entrat per argument
    FILE * file;
    char *fileName = argv[1];
	if ((file=fopen(fileName,"r"))==NULL){
        printf("No es pot obrir el fitxer\n");
        return 1;
    }
    //Declara i inicialitza les variables característiques del graf
	int NAR, NVE;
	unsigned a0, a1;
	estructuracami cami;

	fscanf(file, "%i\n", &NVE);
	fscanf(file, "%i\n", &NAR);
	if((cami.nodes = (unsigned *) malloc (NAR+10 * sizeof(unsigned))) == NULL){
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    } 
    if((cami.arvis = (unsigned *) malloc (NAR * sizeof(unsigned))) == NULL){
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }
	if((larestes = (aresta *) malloc(NAR * sizeof(aresta))) == NULL){
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }
	for (unsigned j=0; j<NAR; j++) {
		fscanf(file, "%u %u\n", &a0, &a1);
		larestes[j].n1 = a0;
		larestes[j].n2 = a1;
		larestes[j].estat = 0;
	}
	//Comença l'estructura del programa
    unsigned i,j,npos=0,seguir=0, MAXARNO = valencia(larestes, NAR, NVE), arestespos[MAXARNO], node;   
    cami.naresvisit=0;
    /*do{
		for(i=0;i<NAR;i++){
			printf("Aresta %d -> [%d,%d]\n",i,larestes[i].n1,larestes[i].n2);
		}
		printf("Node Inici: ");
		scanf("%u",cami.nodes);
		QJ = 1;
		i=0;
		while(i<=NVE && QJ==1){
			if(cami.nodes[0] == i) QJ=0;
			i++;
		}
		if (QJ) printf("Node incorrecte, torna a intentar\n");
	}while(QJ==1);*/
	
	//Camins maximals	
    unsigned camind=0, k=0, canvi=1;
    for (node=0;node<NVE;node++){
		npos=arestesdelnode(cami.nodes[0], arestespos, NAR);
		seguir=1;
		k=0;
		canvi=1;
		cami.nodes[0] = node;
		do{
			if(npos > 0){
				
				cami.arvis[cami.naresvisit] = arestespos[k];          
				k=0;
				larestes[cami.arvis[(cami.naresvisit)]].estat=1;
				(cami.naresvisit)++;
				if(larestes[cami.arvis[(cami.naresvisit)-1]].n1==cami.nodes[(cami.naresvisit)-1]){
					cami.nodes[cami.naresvisit]=larestes[cami.arvis[(cami.naresvisit)-1]].n2;
					j++;
				}
				else{
					cami.nodes[cami.naresvisit]=larestes[cami.arvis[(cami.naresvisit)-1]].n1;
					j++;
				}
				npos=arestesdelnode(cami.nodes[cami.naresvisit],arestespos, NAR);
			}
			else{
				camind++;
				printf("Camí maximal %u del node %u:\n",camind, node);
				for(i=0;i<cami.naresvisit;i++){
					printf("%d ",cami.arvis[i]);
				}
				printf("\n\n");
				j=1;
				canvi=1;
				while(canvi && (cami.naresvisit+1 > j)){
					npos=arestesdelnode(cami.nodes[cami.naresvisit-j],arestespos, NAR);
					larestes[cami.arvis[cami.naresvisit-j]].estat=0;
					for (i=0;i<npos;i++){
						if(arestespos[i]>cami.arvis[cami.naresvisit-j]) {
							k=i;
							cami.naresvisit = cami.naresvisit-j;
							canvi=0;
							break;
						}
					}
					j++;
				}
				if(canvi) seguir=0;
			}
			
		}while(seguir);
		printf("Finalitza el node %u\n\n", node);
		cami.naresvisit = 0;
		for(i=0;i<NAR;i++) larestes[i].estat=0;
		camind = 0;
	}
    return 0;
}

unsigned arestesdelnode(unsigned nn,unsigned llistap[], unsigned NAR){
    unsigned i,nombre=0;
    for(i=0;i<NAR;i++){
        if(larestes[i].estat==0 && (larestes[i].n1==nn||larestes[i].n2==nn)){
            llistap[nombre]=i;
            nombre++;
        }
    }
    return nombre;
}

unsigned valencia(aresta *larestes, unsigned NAR, unsigned NVE) {
	unsigned maxari = 0;
	unsigned maxar = 0;
	for (unsigned i=0; i<NVE; i++) {
		maxari=0;
		for (unsigned j=0; j<NAR; j++) {
			if (larestes[j].n1 == i) maxari++;
			if (larestes[j].n2 == i) maxari++;
		}
		if (maxari > maxar) maxar = maxari;
	}
	return maxar;
}
