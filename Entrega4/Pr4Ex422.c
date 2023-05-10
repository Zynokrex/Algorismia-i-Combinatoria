# include <stdio.h>
# include <stdlib.h>

#define MAX_DADES 400

typedef struct Dada{
    int niu;
    float notes[5];
} Alu;

int comparaciomitjana (const void * a, const void * b)
{if(((Alu *)a)->notes[4]>((Alu *)b)->notes[4]) return 1;else return -1;}

int comparacioniu (const void * a, const void * b)
{if(((Alu *)a)->niu>((Alu *)b)->niu) return 1;else return -1;}

int comparaciomitjanesindex (const void * a, const void *b)
{if((*(Alu **)a)->notes[4]>(*(Alu **)b)->notes[4]) return 1; else return -1;}

int comparacioniuindex (const void * a, const void *b)
{if((*(Alu **)a)->niu>(*(Alu **)b)->niu) return 1; else return -1;}

int cercabinarianiu(int, Alu**, int);

float mitjana(float [],int );

void imprimirdesdindex(Alu **index, int nalumnes);


int main(){
    FILE *dades;
    int n,i,j,lrg=-1;

    Alu alumnes[MAX_DADES];

    dades=fopen("Llista.txt","r");
    if(dades==NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }

    while(!(fscanf(dades,"%i;",&n)==EOF)){
        lrg++;
        if(lrg==MAX_DADES){
            printf("No hi ha prou espai reservat per guardar totes les dades\n");
            return 2;
        }
        alumnes[lrg].niu=n;
        for(i=0;i<4;i++){
            fscanf(dades,"%f",&alumnes[lrg].notes[i]);
            fgetc(dades);//llegeix i descarta els ; i el \n
        }
        alumnes[lrg].notes[4]=mitjana(alumnes[lrg].notes,4);
    }
    fclose(dades);

    int nalumnes=lrg+1;

    Alu **indexmitjanes;

    indexmitjanes=(Alu**)malloc(nalumnes*sizeof(Alu *));
    for(j=0;j<nalumnes;j++){
        indexmitjanes[j]=&alumnes[j];
    }

    qsort(indexmitjanes,nalumnes,sizeof (Alu *), comparaciomitjanesindex);

    //imprimirdesdindex(indexmitjanes, nalumnes);
    
    Alu **indexniu;

    indexniu=(Alu**)malloc(nalumnes*sizeof(Alu *));
    for(j=0;j<nalumnes;j++){
        indexniu[j]=&alumnes[j];
    }
    
    qsort(indexniu, nalumnes, sizeof(Alu*), comparacioniuindex);
    
    int NIU=0, indNIU;
    printf("Introdueix el NIU a cercar:\n");
    scanf("%d", &NIU);
    indNIU = cercabinarianiu(NIU, indexniu, nalumnes);
    if(indNIU == -1) printf("Aquest NIU no està a la base de dades\n");
    else {
		printf("%d | ",NIU);
		for(i=0;i<4;i++){
			printf("%5.1f",indexniu[indNIU]->notes[i]);
		}
		printf(" |%6.2f",indexniu[indNIU]->notes[4]);
		printf("\n");
	}
    
    
    return 0;
}

float mitjana(float dades[],int n){
    int i;
    float m=0.;
    for(i=0;i<n;i++)
    {
        m+=dades[i];
    }
    return m/n;
}

void imprimirdesdindex(Alu **index, int nalumnes){
    int i,j;
    for(j=0;j<nalumnes;j++){
        printf("%d | ",index[j]->niu);
        for(i=0;i<4;i++){
            printf("%5.1f",index[j]->notes[i]);
        }
        printf(" |%6.2f",index[j]->notes[4]);
        printf("\n");
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",nalumnes);
}

int cercabinarianiu(int NIU, Alu** indexalumnes, int nalum) {
	unsigned P=0,U=nalum-1,M=U/2;
	while(U-P>1){
		if(indexalumnes[M]->niu==NIU) return M;
		else if(indexalumnes[M]->niu < NIU) {
			P=M;
			M=P+((U-P)/2);
		}else {
			U=M;
			M=P+((U-P)/2);
		}
	}
	return -1;
}
