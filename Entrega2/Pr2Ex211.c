# include <stdio.h>
# include <stdlib.h>

#define MAX_DADES 400

typedef struct Dada{
    int niu;
    float notes[5];
} Alu;

float mitjana(float [],int );

int main(){
	
    FILE *dades;
    int n,i,j,lrg=-1, nalum=0;
    
    Alu *alumnes;
    
    dades=fopen("Llista.txt","r");
    if(dades==NULL){
        printf("\nNo s'ha accedit al fitxer de dades\n");
        return 1;
    }
    
    char ll;
	
	while ((ll=fgetc(dades)) != EOF) {
		if (ll == '\n') { nalum++; }
	}
      
	rewind(dades);
	printf("Hi ha %d alumnes\n", nalum);
    alumnes = (Alu *) malloc (nalum * sizeof(Alu));
    
    if (alumnes == NULL) {
		printf("No s'ha pogut reservar la memòria per guardar les dades\n");
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
    for(j=0;j<=lrg;j++){
        printf("%d | ",alumnes[j].niu);
        for(i=0;i<4;i++){
            printf("%5.1f",alumnes[j].notes[i]);
        }
        printf(" |%6.2f",alumnes[j].notes[4]);
        printf("\n");
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",lrg+1);
    
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
