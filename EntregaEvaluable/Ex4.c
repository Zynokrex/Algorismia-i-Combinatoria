//Biel González	1551813
//Èric Sánchez	1523259
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCONF 20

//La implementació actual encara fa servir NGERRES per definir el vector continguts, es a dir
//està tot agafat amb pinces, fa falta:
/* Transformar continguts en un array de mida no fixe (mallocs, bla, bla)
 * Aconseguir que els arguments s'adaptin al nombre de gerres (numgerr)
 * Arreglar tot el que te a veure que continguts sigui un array de mida no fixe
 * canviar tot el que te a veure amb estat_config
 */

typedef struct{
    unsigned capacitat,contingut;
}gerra;

typedef struct{
    unsigned * continguts;
    unsigned origen, desti;
    unsigned anterior;
}configuracio;

configuracio transvasament(unsigned, unsigned, configuracio, gerra*, unsigned);
void mostracami(unsigned, configuracio*, unsigned);
unsigned calcul_index(unsigned *, gerra *, int);

int main(int argc, char *argv[])
{
    unsigned i,j,k,l;
    unsigned numgerr, var1, maxlitr = 1;

    if (sscanf(argv[1], "%u", &numgerr)!=1
		|| argc<(numgerr*2+1)
		){
		fprintf(stderr,"%s numgerr cap1 cont1 cap2 cont2 ... capnumgerr contnumgerr\n", argv[0]);
		return -1;
    }
    
	gerra * gerres;
    gerres=(gerra *)malloc(sizeof(gerra)*numgerr);
    
    for(l=0; l<numgerr; l++){
		gerres[l].capacitat=atoi(argv[2*l+2]);
		gerres[l].contingut=atoi(argv[2*l+3]);
		if(gerres[l].contingut > gerres[l].capacitat){
			fprintf(stderr,"Configuració no possible a la gerra %d\n", l);
			return -1;
		}
	}

    //calcul del nombre de litres per estat_config
    for (i=0; i<numgerr; i++) maxlitr=maxlitr*(gerres[i].capacitat+1);

    //array estat config
    char * estat_config;
    estat_config=(char *)malloc(maxlitr*sizeof(char));
    memset(estat_config,0,maxlitr);

    configuracio configuracions[MAXCONF+1];
    for(i=0;i<MAXCONF+1;i++) configuracions[i].continguts=(unsigned *)malloc(numgerr*sizeof(unsigned));

    printf("Gerres amb capacitats |");
    for(l=0;l<numgerr;l++) printf("%u|",gerres[l].capacitat);
    printf("\n");

    for(l=0;l<numgerr;l++) configuracions[0].continguts[l]=gerres[l].contingut;
    printf("Configuració inicial  |");
    for(l=0;l<numgerr;l++) printf("%u|",configuracions[0].continguts[l]);
    printf("\n");
    configuracions[0].anterior = 0U; //L'anterior de l'inicial no existeix

    var1 = calcul_index(configuracions[0].continguts, gerres, numgerr);
    estat_config[var1]=1;

    int num_conf=1;
    for(i=0;i<num_conf && num_conf<MAXCONF;i++){
        for(j=0;j<numgerr && num_conf<MAXCONF;j++){
            for(k=0;k<numgerr && num_conf<MAXCONF;k++){
                if(j==k) continue;
                if(configuracions[i].continguts[j]==0) continue;
                if(configuracions[i].continguts[k]==gerres[k].capacitat) continue;
                configuracions[num_conf]=transvasament(j,k,configuracions[i],gerres,numgerr);	//Crida a transvasament
                configuracions[num_conf].anterior=i;
                var1 = calcul_index(configuracions[num_conf].continguts, gerres, numgerr);
                if(estat_config[var1]==1) continue;
                estat_config[var1]=1;
                num_conf++;
            }
        }
    }
	for(i=1;i<num_conf;i++) mostracami(i, configuracions, numgerr);

    if(num_conf==MAXCONF){
        printf("Hem arribat al màxim de configuracions i pot ser no s'han fet totes\n");
        return 1;
    }
    printf("S'han trobat %u configuracions possibles\n",num_conf);
    return 0;
}

configuracio transvasament(unsigned j, unsigned k, configuracio old_configuracions, gerra* gerres, unsigned numgerr){
    configuracio configuracions;
    configuracions.continguts=(unsigned *)malloc(numgerr*sizeof(unsigned));

    for(unsigned l=0;l<numgerr;l++) configuracions.continguts[l]=old_configuracions.continguts[l];
    configuracions.continguts[k]=configuracions.continguts[k]+configuracions.continguts[j];
    configuracions.continguts[j]=0;
    if(configuracions.continguts[k]>gerres[k].capacitat){
        configuracions.continguts[j]=configuracions.continguts[k]-gerres[k].capacitat;
        configuracions.continguts[k]=gerres[k].capacitat;
    }
    configuracions.origen=j;
    configuracions.desti=k;
    return configuracions;
}

void mostracami(unsigned index, configuracio* configuracions,unsigned numgerr) {
    unsigned *cami, i=index, total=1, total2, l;
    while(i!=0){	//Recorrem el camí per veure el nombre de transvasaments
        i=configuracions[i].anterior;
        total++;
    }
    cami=(unsigned *)malloc((total+1)*sizeof(unsigned));	//Inicialitzem un vector per guardar els índexs en ordre

    i=index; total2=total-1;
    cami[total2]=index;
    while(!(configuracions[i].anterior==0U)){	//Tornem a recorrer el camí per guardar els índexs al vector
        cami[total2-1]=configuracions[i].anterior;
        i=configuracions[i].anterior;
        total2--;
    }
	printf("|");
	for(l=0;l<numgerr;l++) printf("%u|",configuracions[cami[0]].continguts[l]);
	for(i=0; i<total-1; i++){
		printf("-(%u,%u)-|",configuracions[cami[i+1]].origen,configuracions[cami[i+1]].desti);
		for(l=0;l<numgerr;l++) printf("%u|",configuracions[cami[i+1]].continguts[l]);
	}
	printf("\n");

}

unsigned calcul_index(unsigned * indexos, gerra * gerres, int numgerr){
    unsigned i,index_f,aux;
    index_f=indexos[0];
    for(i=1;i<numgerr;i++){
        aux=index_f;
        index_f=indexos[i]+(aux*(gerres[i].capacitat+1));
    }
    return index_f;
}
