//Biel González 1551813
//Èric Sánchez 1523259
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define UMAX 432444444
# define MAXARST 15

typedef struct{
	char carrer[12];
	unsigned numnode;	//posició del node al que arribem
}infoaresta;

typedef struct{
    long int id; 
    double latitud,longitud;
    int narst;
    infoaresta arestes[MAXARST];
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
    
    FILE *dadescarrer;
    dadescarrer=fopen("Carrers.csv","r");
    if(dadescarrer==NULL)
    {
        printf("\nNo s'ha accedit al fitxer de carrers del mapa\n");
        return 1;
    }
    char idcarrer[12];
    long int idnode,idnodeanterior;
    unsigned posnode,posnodeanterior, ncarrers=0;

    while((c=fgetc(dadescarrer))!=EOF)
    {
        if(c=='\n') ncarrers++;
    }
    rewind(dadescarrer);
    
    for(i=0; i<ncarrers; i++){
      fscanf(dadescarrer,"id=%[0-9];",idcarrer);
      fscanf(dadescarrer,"%ld",&(idnodeanterior));
      posnodeanterior=buscapunt(idnodeanterior,punts,nnodes);
      
      while(fgetc(dadescarrer)!='\n'){
          fscanf(dadescarrer,"%ld",&(idnode));
          posnode=buscapunt(idnode,punts,nnodes);
          
          if((posnodeanterior!=UMAX) && (posnode != UMAX)){
              punts[posnodeanterior].arestes[punts[posnodeanterior].narst].numnode=posnode;
              strcpy(punts[posnodeanterior].arestes[punts[posnodeanterior].narst].carrer,idcarrer);
              punts[posnodeanterior].narst++;
              
              punts[posnode].arestes[punts[posnode].narst].numnode=posnodeanterior;
              strcpy(punts[posnode].arestes[punts[posnode].narst].carrer,idcarrer);
              punts[posnode].narst++;
              
              posnodeanterior=posnode;
          }
      }
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
