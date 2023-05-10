//Biel González 1551813
//Èric Sánchez 1523259
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#define MAXARST 5

typedef struct{
    int numnode;
    double temps;
}infoaresta;

typedef struct{
    int narst;
    infoaresta arestes[MAXARST];
}Connode;

typedef struct{
    double temps;
    int pendent;
    unsigned anterior;
}EstatDij;

void Afegir(EstatDij **, infoaresta, int);


int main() {
    FILE *dades;
    int nvert = 0, c, i, j, l, node;
    EstatDij *LaCua;
    if ((dades = fopen("InfoXarxa.txt", "r")) == NULL) {
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    while ((c = fgetc(dades)) != EOF) {
        if (c == '\n') nvert++;
    }
    rewind(dades);
    printf("%d nodes\n", nvert);
    printf("---------------------------------------------\n");
    Connode infnodes[nvert];
    for (i = 0; i < nvert; i++) {
        fscanf(dades, "%i", &node);
        j = 0;
        while (fgetc(dades) != '\n') {
            fscanf(dades, "%i", &infnodes[node].arestes[j].numnode);
            fgetc(dades);
            fscanf(dades, "%lf", &infnodes[node].arestes[j].temps);
            j++;
        }
        infnodes[node].narst = j;
    }
    fclose(dades);

    LaCua = (EstatDij *) malloc(sizeof(EstatDij) * nvert);

    //pendent=0 expandit
    //pendent=1 no expandit
    //temps=DBL_MAX no visitat

    LaCua[0].pendent = 1;
    LaCua[0].temps = 0;
    LaCua[0].anterior = -1;
    for (i = 1; i < nvert; i++) {
        LaCua[i].pendent = 1;
        LaCua[i].temps = DBL_MAX;
    }

    int indmin = INT_MAX, numfill;
    double tmin = DBL_MAX, noutemps;
    
    for (i=0; i<nvert; i++){
		//Per cada vertex
		tmin = DBL_MAX;
		for (j=0; j<nvert; j++){
			//Busquem el que estigui pendent amb el temps mínim
			if (LaCua[j].pendent == 1 && LaCua[j].temps < tmin){
				indmin = j;
				tmin = LaCua[j].temps;
			}
		}
		if (tmin == DBL_MAX) continue;
		//Un cop trobat expandim i actualitzem paràmetres dels fills
		LaCua[indmin].pendent = 0;
		for (l=0; l<infnodes[indmin].narst; l++){
			numfill = infnodes[indmin].arestes[l].numnode;
			noutemps = LaCua[indmin].temps + infnodes[indmin].arestes[l].temps;
			if (noutemps > LaCua[numfill].temps) continue;
			LaCua[numfill].anterior = indmin;
			LaCua[numfill].temps = LaCua[indmin].temps + infnodes[indmin].arestes[l].temps;
		}
	}

        /*for (i=0; i<nvert; i++)
        {
            printf("Connexions del node %i:\n",i);
            for (j=0; j<infnodes[i].narst; j++)
            {
                printf("\tNode %2i\t\tTemps %6.3lf\n",infnodes[i].arestes[j].numnode,
                       infnodes[i].arestes[j].temps);
            }
            printf("---------------------------------------------\n");
        }
        printf("FI\n");*/

        //Sí, això es pel print, no preguntis, he hagut d'invertir merdes i comparar temps per endreçar
        //però no directament a LaCua, una fumada, si va, bien i si no seguiré chapuzeando

        EstatDij * CuaAux;
        CuaAux = (EstatDij *) malloc(sizeof(EstatDij) * nvert);
        unsigned LlOrdTemps[nvert], LlPrintInv[nvert];
        double tempsAux;
        unsigned idx2Append, NodeAnt, Count;


        for (i = 0; i < nvert; i++){
            CuaAux[i].temps=LaCua[i].temps;
        }
        //Bucle per comparar els temps
        for(i=0;i<nvert;i++){
            tempsAux=CuaAux[i].temps;
            for(j=0;j<nvert;j++){
                if ((tempsAux>CuaAux[j].temps)&&(CuaAux[j].temps!=DBL_MAX)){
                    tempsAux=CuaAux[j].temps;
                    idx2Append=j;
                }
            }

            if(fabs(tempsAux-CuaAux[i].temps)<DBL_EPSILON){
                idx2Append=i;
                CuaAux[i].temps=DBL_MAX;
            }
            else{
                CuaAux[idx2Append].temps=DBL_MAX;
            }
            LlOrdTemps[i]=idx2Append;
        }

        //Comença el print
        for(i=0;i<nvert;i++){
            Count=0;
            NodeAnt=LlOrdTemps[i];
            printf("Node %d Temps: %lf Camí optim: ",LlOrdTemps[i],LaCua[LlOrdTemps[i]].temps);
            while(NodeAnt!=-1){
                LlPrintInv[Count]=NodeAnt;
                NodeAnt=LaCua[LlPrintInv[Count]].anterior;
                Count++;
            }
            for(j=Count-1;j>=0;j--){
                printf("%d ", LlPrintInv[j]);
            }
            printf("\n");
        }
    return 0;
}

void Afegir(EstatDij ** LaCua, infoaresta Fill, int PareIdx){
  LaCua[Fill.numnode]->temps = LaCua[PareIdx]->temps + Fill.temps;
  LaCua[Fill.numnode]->anterior=PareIdx;
}


