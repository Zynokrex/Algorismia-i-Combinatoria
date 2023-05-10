# include <stdio.h>
# include <stdlib.h>

typedef struct Dada{
    int niu;
    float notes[5];
    struct Dada * seg;
} Alu;

float mitjana(float [],int );
void imprimirllista(Alu *,int);
void inserir(Alu **, Alu **);
void imprimirenordre(Alu **);
int comparaciomitjana (const void *a, const void *b)
{if((*(Alu **)a)->notes[4]>(*(Alu **)b)->notes[4]) return 1; else return -1;}

int main(){
    FILE *dades;
    int n,i,lrg=0;
    Alu **adrecesordremitjana;
    
    Alu *inicill=NULL, *actual = NULL;// Eliminar anterior (unused)
    
    dades=fopen("Llista.txt","r");
    if(dades==NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    
    while(!(fscanf(dades,"%i;",&n)==EOF)){
        if((actual=(Alu *)malloc(sizeof(Alu)))==NULL)
        {
            printf("Problema assignant espai de memoria\n");
            return 2;
        }
        lrg++;
        actual->niu=n;
        for(i=0;i<4;i++){
            fscanf(dades,"%f",&actual->notes[i]);
            fgetc(dades);//llegeix i descarta els ; i el \n
        }
        actual->notes[4]=mitjana(actual->notes,4);
                
        inserir(&inicill, &actual);	//Inserir elements
        
    }
    adrecesordremitjana=(Alu**)malloc(lrg*sizeof(Alu *));	//Reserva memòria índex
    actual=inicill;
    for (unsigned i=0; i<lrg; i++){
		adrecesordremitjana[i]=actual;
		actual=actual->seg;
	}
	imprimirenordre(adrecesordremitjana);	//Ordre NIU
	
	qsort(adrecesordremitjana,lrg,sizeof(Alu *),comparaciomitjana);	//Ordenar segons nota mitjana
	
	imprimirenordre(adrecesordremitjana);	//Ordre Nota

    /*
    printf("Voldria inserir un nou element? Sí - 1, No - 0\n");	//Nou element
    int tria;
    scanf("%d", &tria);
    if (tria){
        if((actual=(Alu *)malloc(sizeof(Alu)))==NULL){
            printf("Problema assignant espai de memoria\n");
            return 2;
        }
        printf("Introdueix el niu:\n");
        scanf("%d", &actual->niu);
        
        printf("Introdueix les 4 notes: \n");
        for(i=0;i<4;i++){
            scanf("%f",&actual->notes[i]);
        }
        actual->notes[4]=mitjana(actual->notes,4);
                
        inserir(&inicill, &actual);	//Inserir elements
	}
    fclose(dades);
    imprimirllista(inicill,lrg);	//Imprimir llista
    */
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

void imprimirllista(Alu *actual, int lrg){
    while(!(actual==NULL)){
        printf("%d | ",actual->niu);
        for(int i=0;i<4;i++){
            printf("%5.1f",actual->notes[i]);
        }
        printf(" |%6.2f",actual->notes[4]);
        printf("\n");
        actual=actual->seg;
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",lrg);
}

void inserir(Alu **inicill, Alu **actual){
	Alu *anterior;
	if(*inicill==NULL){
		(*actual)->seg=NULL;
		*inicill=*actual;
	}
	else{
		if ((*actual)->niu<(*inicill)->niu){
			(*actual)->seg=*inicill;
			*inicill=*actual;
		}
		else{
			anterior=*inicill;
			while(anterior->seg!=NULL&&(anterior->seg)->niu<(*actual)->niu ){
				anterior=anterior->seg;
			}
			(*actual)->seg=anterior->seg;
			anterior->seg=*actual;
		}
	}
} 

void imprimirenordre(Alu **index){
    int i,j=0;
    while(!(index[j]==NULL)){
        printf("%d | ",index[j]->niu);
        for(i=0;i<4;i++){
            printf("%5.1f",index[j]->notes[i]);
        }
        printf(" |%6.2f",index[j]->notes[4]);
        printf("\n");
        j++;
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",j);
}
