//Biel González 1551813
//Èric Sánchez 1523259
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>


typedef struct{
    long int id; 
    double latitud,longitud;
}node;


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
    
    // Mostrem el resultat
    for(i=0;i<nnodes;i++){
        printf("Id=%li Lat=%lf Long=%lf \n",punts[i].id,punts[i].latitud,punts[i].longitud);
    }

    return 0;
}
