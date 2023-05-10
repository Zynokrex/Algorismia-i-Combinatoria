# include <stdio.h>
# include <stdlib.h>

typedef struct Dada{
    int niu;
    float notes[5];
    struct Dada * seg;
} Alu;

float mitjana(float [],int );
void imprimirllista(Alu *,int);
void esborrar(Alu **);
int main(){
    FILE *dades;
    int n,i,lrg=0;
    
    Alu *inicill=NULL, *actual = NULL, *anterior;
    
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
        if(inicill==NULL){
            actual->seg=NULL;
            inicill=actual;
        }
        else{
            if (actual->niu<inicill->niu){
                actual->seg=inicill;
                inicill=actual;
            }
            else{
                anterior=inicill;
                while(anterior->seg!=NULL&&(anterior->seg)->niu<actual->niu ){
                    anterior=anterior->seg;
                }
                actual->seg=anterior->seg;
                anterior->seg=actual;
            }
        }
        
    }
    fclose(dades);
    printf("Quants nius vols esborrar de la base de dades? ");
    int iter;
    scanf("%d",&iter);
    for(int i=0; i<iter;i++){
        esborrar(&inicill);
    }
    //while(!(actual==NULL)){
        //printf("%d | ",actual->niu);
        //for(i=0;i<4;i++){
            //printf("%5.1f",actual->notes[i]);
            //}
        //printf(" |%6.2f",actual->notes[4]);
        //printf("\n");
        //actual=actual->seg;
        //}
    //printf("\nS'ha llegit informacio de %d linies.\n\n",lrg);
    imprimirllista(inicill,lrg);
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

void imprimirllista(Alu *actual,int lrg){
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

void esborrar(Alu **inicill){
    Alu *auxiliar=*inicill;
    Alu *actual=*inicill;
    int niu,trobat=0;
    printf("Quin NIU vols eliminar? ");
    scanf("%d",&niu);
    printf("Buscant...\n");
    while(!(auxiliar->seg==NULL)){
        actual=actual->seg;
        if ((auxiliar->niu==niu)||(actual->niu==niu)){
            if(auxiliar->niu==(*inicill)->niu){
                (*inicill)=(*inicill)->seg;
                free(auxiliar);
                auxiliar=actual;
                trobat=1;
            }
            else{
                if(actual->seg!=NULL) {
                    auxiliar->seg = actual->seg;
                    auxiliar=auxiliar->seg;
                }
                else auxiliar->seg=NULL;

                free(actual);
                actual=auxiliar;
                trobat=1;
            }
        }
        else{
            auxiliar=auxiliar->seg;
        }
    }
    if(!trobat){
        printf("No s'ha trobat l'identificador: %d\n", niu);
    }
    else{
        printf("La informació s'ha esborrat correctament\n");
    }
}