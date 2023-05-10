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
unsigned valencia(aresta*, unsigned);

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
	if((cami.nodes = (unsigned *) malloc (NAR+1 * sizeof(unsigned))) == NULL){
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
    unsigned i,j,l,QJ,npos=0,seguir=0, MAXARNO = valencia(larestes, NAR), arestespos[MAXARNO];
    int arrcorr[NAR];    
    cami.naresvisit=0;
    do{
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
	}while(QJ==1);
	
    npos=arestesdelnode(cami.nodes[0], arestespos, NAR);
    seguir=1;
    do{
        if(npos > 0){
            QJ=1;
            printf("Teniu %d arestes per triar: \n",npos);
            for(i=0;i<npos;i++){
                arrcorr[i]=arestespos[i];

                printf("%d -> [%d,%d]\n",arestespos[i],larestes[arestespos[i]].n1,
                       larestes[arestespos[i]].n2);
            }
            printf("Trieu: ");
            scanf("%u",(cami.arvis)+(cami.naresvisit));
            while(QJ){
                for(l=0;l<npos;l++){
                    if(*((cami.arvis)+(cami.naresvisit))==arrcorr[l]){
                        QJ=0;
                        break;
                    }
                }
                if(QJ) {
                    printf("Aresta incorrecta\n");
                    printf("Teniu %d arestes per triar: \n",npos);
                    for(i=0;i<npos;i++){
                        printf("%d -> [%d,%d]\n",arestespos[i],larestes[arestespos[i]].n1,
                               larestes[arestespos[i]].n2);
                    }
                    printf("Trieu: ");
                    scanf("%u", (cami.arvis) + (cami.naresvisit));
                }
            }

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
            for(i=0; i<cami.naresvisit; i++){
                printf("%d [%d,%d] ",cami.nodes[i],
                       larestes[cami.arvis[i]].n1,larestes[cami.arvis[i]].n2);
            }
            printf("%d\n",cami.nodes[cami.naresvisit]);
            npos=arestesdelnode(cami.nodes[cami.naresvisit],arestespos, NAR);
        }
        else{
            printf("No queden arestes disponibles.\n");
            printf("Arestes visitades (%d):\n",cami.naresvisit);
            for(i=0;i<cami.naresvisit;i++){
                printf("%d ",cami.arvis[i]);
            }
            seguir=0;
        }
    }while(seguir);
    printf("\n");
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

unsigned valencia(aresta *larestes, unsigned NAR) {
	unsigned maxari = 0;
	unsigned maxar = 0;
	for (unsigned i=0; i<NAR; i++) {
		for (unsigned j=0; j<NAR; j++) {
			if (larestes ->n1 == j) maxari++;
			if (larestes ->n2 == j) maxari++;
		}
		if (maxari > maxar) maxar = maxari;
	}
	return maxar;
}
