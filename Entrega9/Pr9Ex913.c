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
double distancia(node, node);


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
    
	long int ident, ident2;
	unsigned index, index2;

    printf("Intodueix els identificadors dels dos nodes:\n");
    scanf("%ld %ld", &ident, &ident2);
    index = buscapunt(ident, punts, nnodes);
    index2 = buscapunt(ident2, punts, nnodes);
    if(index == UMAX || index2 == UMAX) printf("Identificador incorrecte\n");
    else{
		printf("Dist=%lf\n",distancia(punts[index], punts[index2]));
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

double distancia(node ini, node fin){
  double dist, xini, yini, zini, xfin, yfin, zfin;
  double R=6371;
  //(long, lat)=(theta, phi)

  xini=R*cos(ini.longitud)*cos(ini.latitud);  xfin=R*cos(fin.longitud)*cos(fin.latitud);
  yini=R*sin(ini.longitud)*cos(ini.latitud);  yfin=R*sin(fin.longitud)*cos(fin.latitud);
  zini=R*sin(ini.latitud);                    zfin=R*sin(fin.latitud);

  dist=sqrt(pow(xfin-xini,2)+pow(yfin-yini,2)+pow(zfin-zini,2));

  return dist;
}
