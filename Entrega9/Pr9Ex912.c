//Biel González 1551813
//Èric Sánchez 1523259
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define UMAX 432444444

typedef struct{
    long int id; 
    double latitud,longitud;
}node;

unsigned buscapunt(long int, node*, int);


int main(){
    FILE *dades;
    node *punts;
    int c,nnodes=0,i;

    dades=fopen("Nodes.csv","r");
    if(dades==NULL)
    {
        printf("\nNo s'ha accedit al fitxer de dades del mapa\n");
        return 1;
    }
    while((c=fgetc(dades))!=EOF)
    {
        if(c=='\n') nnodes++;
    }
    rewind(dades);

    if((punts=(node *)malloc(nnodes*sizeof(node)))==NULL)
    {
        printf("Problema assignant espai de memoria\n");
        return 2;
    }
    for(i=0;i<nnodes;i++){
        fscanf(dades,"%ld;",&(punts[i].id));
        fscanf(dades,"%lf;",&(punts[i].latitud));
        fscanf(dades,"%lf\n",&(punts[i].longitud));
    }
    fclose(dades);
    
    // Busquem un node
    
	long int ident;
	unsigned index;

    printf("Intodueix l'identificador del node a buscar:\n");
    scanf("%ld", &ident);
    index = buscapunt(ident, punts, nnodes);
    if(index == UMAX) printf("Identificador incorrecte\n");
    else{
		printf("Id=%li Lat=%lf Long=%lf \n",punts[index].id,
			punts[index].latitud,punts[index].longitud);
	}
    return 0;
}

unsigned buscapunt(long int ident, node l[], int n){
    unsigned U=n-1, M=U/2, P=0;
    while(U > M && M > P){
		if(l[M].id > ident){
			U = M;
			M = (U-P)/2 + P;
		}
		else if(l[M].id < ident) {
			P = M;
			M = (U-P)/2 + P;
		}
		else return M;	//trobat
	}
	if(l[P].id == ident) return P;	//a un extrem
	else if(l[U].id == ident) return U;	//o a l'altre
	
    return UMAX;	//no trobat
}
