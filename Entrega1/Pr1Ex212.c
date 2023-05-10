#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *nom;
    char *estacio;
    int alt;
    float tmtj,tmxm,tmnm,tmx,tmn,pluja,hr,vv;
    char ddv[3];
}MetCom;

float mitjana(float[], int);
void maxmin(MetCom llista[],int nelem,int *pmx, int *pmn);


int main(){
    FILE * meteo;
    MetCom *comarca;
    unsigned i=0,numcom=0,ll;
    char aux[35];
    int pmx, pmn;

    if ((meteo=fopen("MeteoCat2018.txt","r"))==NULL){
        printf("No es pot obrir el fitxer\n");
        return 1;
    }

    while((ll=fgetc(meteo)) != EOF){
        if (ll=='\n'){numcom++;}
    }
    printf("\nDades de %d comarques\n",numcom);

    rewind(meteo);

    if((comarca = (MetCom *) malloc(numcom * sizeof(MetCom))) == NULL){
        printf ("\nNo es possible assignar la memoria necessaria...\n\n");
        return 1;
    }

    for(i=0;i<numcom;i++){
        fscanf(meteo, "%[a-zA-Z'. -];", aux);
        comarca[i].nom = (char *) malloc (strlen(aux)*sizeof(char));
        strcpy(comarca[i].nom, aux);
        fscanf(meteo, "%[a-zA-Z'. -];", aux);
        comarca[i].estacio = (char *) malloc (strlen(aux)*sizeof(char));
        strcpy(comarca[i].estacio, aux);
        fscanf(meteo, "%i;", &comarca[i].alt);
        fscanf(meteo, "%f;", &(comarca[i].tmtj));
        fscanf(meteo, "%f;", &(comarca[i].tmxm));
        fscanf(meteo, "%f;", &(comarca[i].tmnm));
        fscanf(meteo, "%f;", &(comarca[i].tmx));
        fscanf(meteo, "%f;", &(comarca[i].tmn));
        fscanf(meteo, "%f;", &(comarca[i].pluja));
        fscanf(meteo, "%f;", &(comarca[i].hr));
        fscanf(meteo, "%f;", &(comarca[i].vv));
        fscanf(meteo, "%s\n", comarca[i].ddv);
    }
    printf("Fi de la lectura.....\n\n");

    fclose(meteo);

    printf("   Comarca              Estacio                             Max\n");
    printf("================================================================\n");
    for(i=0;i<numcom;i++){
        printf("%2u ",i+1);
        printf("%-20s ",comarca[i].nom);
        printf("%-35s ",comarca[i].estacio);
        printf("%-.1f",comarca[i].tmx);
        printf("\n");
    }
    
    float tempmax[numcom], tempmin[numcom], plujes[numcom];
    for (i=0;i<numcom;i++){
		tempmax[i] = comarca[i].tmx;
		tempmin[i] = comarca[i].tmn;
		plujes[i] = comarca[i].pluja;
	}
	printf("\n   Mitjana de les temperatures màximes registrades\n");
	printf("================================================================\n");
	printf("   %.4f\n", mitjana(tempmax, numcom));
	printf("\n   Mitjana de les temperatures mínimes registrades\n");
	printf("================================================================\n");
	printf("   %.4f\n", mitjana(tempmin, numcom));
	printf("\n   Mitjana de la pluviositat total de les comarques\n");
	printf("================================================================\n");
	printf("   %.4f\n", mitjana(plujes, numcom));

    maxmin(comarca, numcom, &pmx, &pmn);
    printf("\n   Comarca              Record Mínima\n");
    printf("================================================================\n");
    printf("%2u ", pmn+1);
    printf("%-20s ",comarca[pmn].nom);
    printf("%-.1f\n",comarca[pmn].tmn);
    printf("\n   Comarca              Record Màxima\n");
    printf("================================================================\n");
    printf("%2u ", pmx+1);
    printf("%-20s ",comarca[pmx].nom);
    printf("%-.1f\n",comarca[pmx].tmx);
    return 0;
}

float mitjana(float llista[], int nelem) {
	float suma = 0;
	for (unsigned int i = 0; i < nelem; i++) {
		suma += llista[i];
	}
	float mitjana = suma / nelem;
	return mitjana;
}

void maxmin(MetCom llista[], int nelem, int *pmx, int *pmn){
    float vmin=0,vmx=0;
    for (int i=0; i<=nelem;i++){
        if (llista[i].tmn < vmin)
        {
            vmin=llista[i].tmn;
            *pmn=i;
        }
        if (llista[i].tmx > vmx)
        {
            vmx=llista[i].tmx;
            *pmx=i;
        }
    }
}
