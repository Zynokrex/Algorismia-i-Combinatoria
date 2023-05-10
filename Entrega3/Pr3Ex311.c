// Èric Sánchez NIU 1523259
// Biel González Garriga NIU: 1551813

#include <stdio.h>
#define NAR 7
#define MAXARNO 5

typedef struct{
    unsigned n1,n2,estat;
}aresta;
typedef struct
{
    unsigned nodes[NAR+1];
    unsigned arvis[NAR];
    int naresvisit;
}estructuracami;

unsigned arestesdelnode(unsigned ,unsigned []);

aresta larestes[NAR]={{0,1,0},{0,2,0},{0,2,0},{0,3,0},{0,3,0},
    {1,2,0},{1,3,0}};

int main(){
	//Comença l'estructura del programa
    unsigned i,j,l,QJ,arestespos[MAXARNO],npos=0,seguir=0, NNO=0;
    int arrcorr[NAR];
    estructuracami cami;
    
    for (i=0;i<NAR;i++) {
		if (larestes[i].n1 > NNO) NNO = larestes[i].n1;
		if (larestes[i].n2 > NNO) NNO = larestes[i].n2;
	}
    
    cami.naresvisit=0;
    do{
		for(i=0;i<NAR;i++){
			printf("Aresta %d -> [%d,%d]\n",i,larestes[i].n1,larestes[i].n2);
		}
		printf("Node Inici: ");
		scanf("%u",cami.nodes);
		QJ = 1;
		i=0;
		while(i<=NNO && QJ==1){
			if(cami.nodes[0] == i) QJ=0;
			i++;
		}
		if (QJ) printf("Node incorrecte, torna a intentar\n");
	}while(QJ==1);
    
    npos=arestesdelnode(cami.nodes[0], arestespos);
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
            npos=arestesdelnode(cami.nodes[cami.naresvisit],arestespos);
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

unsigned arestesdelnode(unsigned nn,unsigned llistap[]){
    unsigned i,nombre=0;
    for(i=0;i<NAR;i++){
        if(larestes[i].estat==0 && (larestes[i].n1==nn||larestes[i].n2==nn)){
            llistap[nombre]=i;
            nombre++;
        }
    }
    return nombre;
}
