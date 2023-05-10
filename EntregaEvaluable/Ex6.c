//Biel González	1551813
//Èric Sánchez	1523259
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct{
    unsigned capacitat,contingut;
}gerra;

typedef struct configu{
    unsigned * continguts;
    unsigned origen, desti;
    struct configu *anterior;
}configuracio;

typedef struct ElementDeCua{
    configuracio *config;
    struct ElementDeCua *seg;
}ElementCua;

typedef struct{
    ElementCua *inici;
    ElementCua *final;
}UnaCua;


configuracio transvasament(unsigned, unsigned, configuracio, gerra*, unsigned);
void mostracami(configuracio*, unsigned);
unsigned calcul_index(unsigned *, gerra *, int);
void encua(UnaCua *, configuracio*);
void desencua(UnaCua *);
int IsEmpty( UnaCua Q ){ return ( Q.inici == NULL ); }

int main(int argc, char *argv[])
{
    unsigned i,j,k,l,t,v, *condicions;
    int  * buscaux, * busccond;
    unsigned numgerr, var1, maxlitr=1, numcond;
    UnaCua Q = {NULL, NULL};

    if (sscanf(argv[1], "%u", &numgerr)!=1
        || argc<(numgerr*2+1)
            ){
        fprintf(stderr,"%s numgerr cap1 cont1 cap2 cont2 ... capnumgerr contnumgerr cond1 cond2 ... condnumgerr\n", argv[0]);
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
    numcond = argc-(2*numgerr+2);

    if(numcond!=0){
      unsigned suma=0, total=0;
      condicions = (unsigned *)malloc(numcond*sizeof(unsigned));
      for(l=0; l<numcond; l++) {
        condicions[l]=atoi(argv[2*numgerr+1 + (l+1)]);
        suma = condicions[l] + suma;
      }

      for(l=0; l<numgerr; l++) total = gerres[l].contingut + total;   //Comprovació per si és possible la suma de les condicions
      if(suma>total){
          fprintf(stderr, "Error: contingut total de les condicions (%u) superior al contingut de les gerres (%u)\n", suma, total);
          return 0;
      }
    }

    for (i=0; i<numgerr; i++) maxlitr=maxlitr*(gerres[i].capacitat+1);

    char * estat_config;
    estat_config=(char *)malloc(maxlitr*sizeof(char));
    memset(estat_config,0,maxlitr);

    configuracio * actual;
    //fer reserva de memoria del configuracio * actual
    actual=(configuracio *)malloc(sizeof(configuracio ));
    actual->continguts=(unsigned *)malloc(numgerr*sizeof(unsigned)); //actual.continguts
    actual->anterior = NULL; //L'anterior de l'inicial no existeix
    encua(&Q, actual); //encuem actual

    buscaux=(int *)malloc(numgerr*sizeof(int));//per buscar
    busccond = (int *)malloc(numcond*sizeof(int));

    printf("Gerres amb capacitats |");
    for(l=0;l<numgerr;l++) printf("%u|",gerres[l].capacitat);
    printf("\n");

    for(l=0;l<numgerr;l++) actual->continguts[l]=gerres[l].contingut;
    printf("Configuració inicial  |");
    for(l=0;l<numgerr;l++) printf("%u|",actual->continguts[l]);
    printf("\n");


    var1 = calcul_index(actual->continguts, gerres, numgerr);
    estat_config[var1]=1;

    int num_conf=1;
    actual=(configuracio *)malloc(sizeof(configuracio ));
    actual->continguts=(unsigned *)malloc(numgerr*sizeof(unsigned));


    while(!IsEmpty(Q)){ //Fem trasvassaments al primer de la cua i si n'obtenim una config nova, reservem i encuem

        for(j=0;j<numgerr;j++){

            for(k=0;k<numgerr;k++){

                if(j==k) continue;
                if(Q.inici->config->continguts[j]==0) continue;
                if(Q.inici->config->continguts[k]==gerres[k].capacitat) continue;

                *actual = transvasament(j,k,*Q.inici->config,gerres,numgerr);
                actual->anterior = Q.inici->config;

                var1 = calcul_index(actual->continguts, gerres, numgerr);
                if(estat_config[var1]==1) continue;
                estat_config[var1]=1;

                if(numcond!=0){
                  unsigned coincid;
                  for(t = 0; t < numcond; t++){
                      busccond[t]=condicions[t];
                  }
                  for(v = 0; v < numgerr; v++){
                      buscaux[v] = actual->continguts[v];
                  }

                  for(t = 0; t < numcond; t++){
                      for(v = 0; v < numgerr; v++){
                        if(buscaux[v]==busccond[t]){
                            buscaux[v]=INT_MAX;
                            busccond[t]=-1;
                            break;
                        }
                      }
                  }
                  coincid=0;
                  for(unsigned u = 0; u < numcond; u++){
                      if(busccond[u]==-1) coincid++;
                  }
                  if(coincid==numcond){
                      mostracami(actual, numgerr);
                      return 0;
                  }

                } else mostracami(actual, numgerr);
                encua(&Q, actual); //s'encua un cop s'ha vist que es una nova

                actual=(configuracio *)malloc(sizeof(configuracio ));
                actual->continguts=(unsigned *)malloc(numgerr*sizeof(unsigned));

                num_conf++; //aquí seria quan tocaria fer la reserva de memòria pel següent
            }
        }
        //quan ja hem fet tots els trasvassaments desencuem el primer element de la cua
        desencua(&Q);
    }
    printf("S'han trobat %u configuracions possibles\n",num_conf);
    if(numcond!=0){
      printf("Pero cap te |");
      for(i=0; i<numcond; i++){
        printf("%d|",condicions[i]);
      }
      printf(" litres\n");
    }
    return 0;
}

configuracio transvasament(unsigned j, unsigned k, configuracio old_actual, gerra* gerres, unsigned numgerr){
    configuracio actual;
    actual.continguts=(unsigned *)malloc(numgerr*sizeof(unsigned));

    for(unsigned l=0;l<numgerr;l++) actual.continguts[l]=old_actual.continguts[l];
    actual.continguts[k]=actual.continguts[k]+actual.continguts[j];
    actual.continguts[j]=0;

    if(actual.continguts[k]>gerres[k].capacitat){
        actual.continguts[j]=actual.continguts[k]-gerres[k].capacitat;
        actual.continguts[k]=gerres[k].capacitat;
    }

    actual.origen=j;
    actual.desti=k;
    return actual;
}

void mostracami(configuracio *actual,unsigned numgerr) {
    unsigned total=1, total2, l, i;
    configuracio **cami, *inici=actual;

    while(!(actual->anterior==NULL)){	//Recorrem el camí per veure el nombre de transvasaments
        if(actual==actual->anterior){ //Per evitar els bucles infinits
            printf("Bucle infinit\n");
            return;
        } else {
            actual=actual->anterior;
        }
        total++;
    }
    cami=(configuracio**)malloc((total+1)*sizeof(configuracio*));	//Inicialitzem un vector per guardar els índexs en ordre

    actual=inici;
    cami[total-1]=inici;
    for(total2=total-1; total2>0; total2--){	//Tornem a recorrer el camí per guardar els índexs al vector
        cami[total2-1]=actual->anterior;
        actual=actual->anterior;
    }
    printf("|");
    for(l=0;l<numgerr;l++) printf("%u|",cami[0]->continguts[l]);
    for(i=0; i<total-1; i++){
        printf("-(%u,%u)-|",cami[i+1]->origen,cami[i+1]->desti);
        for(l=0;l<numgerr;l++) printf("%u|",cami[i+1]->continguts[l]);
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

void encua(UnaCua* Cua, configuracio* v){
    ElementCua* aux;
    aux=(ElementCua*)malloc(sizeof(ElementCua));
    if(aux==NULL) printf("No s'ha pogut fer la reserva de memòria\n");
    else {
        aux->config=v;
        aux->seg=NULL;
        if(Cua->inici==NULL){
            Cua->inici=aux;
        }
        else{
            Cua->final->seg=aux;
        }
        Cua->final=aux;
    }
}

void desencua( UnaCua *Q ){
    ElementCua *node_inicial = Q->inici;

    Q->inici = Q->inici->seg;
    free(node_inicial);
}
