# include <stdio.h>
# include <stdlib.h>

#define MAX_DADES 400

typedef struct Dada{
    int niu;
    float notes[5];
} Alu;

float mitjana(float [],int );
void imprimirtaula(Alu*, int);
int ordenataula(Alu*, Alu*, int);

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
    
    Alu *alumnesNou;
    
    alumnesNou = (Alu *)realloc(alumnes, (nalum+1)*sizeof(Alu));
    
    if (alumnesNou == NULL) {
		printf("No s'ha pogut reservar la memòria per les dades\n");
	}
    else {
		alumnes = alumnesNou;
		alumnes[nalum].niu = 1234567;
		alumnes[nalum].notes[0] = 5.6;
		alumnes[nalum].notes[1] = 6.2;
		alumnes[nalum].notes[2] = 4.3;
		alumnes[nalum].notes[3] = 8.6;
		alumnes[nalum].notes[4] = mitjana(alumnes[nalum].notes, 4);
		nalum++;
		lrg++;
	}
    
    /* for(j=0;j<=lrg;j++){
        printf("%d | ",alumnes[j].niu);
        for(i=0;i<4;i++){
            printf("%5.1f",alumnes[j].notes[i]);
        }
        printf(" |%6.2f",alumnes[j].notes[4]);
        printf("\n");
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",lrg+1);
    */
    
    imprimirtaula(alumnes, nalum);
    
    Alu* alumnesord;
    alumnesord = (Alu *) malloc (nalum * sizeof(Alu));
    if (alumnesord == NULL) {
		printf("No s'ha pogut reservar la memòria per les dades\n");
	}
    
    ordenataula(alumnes, alumnesord, nalum);
    
    imprimirtaula(alumnesord, nalum);
    
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

void imprimirtaula(Alu* alumnes, int numal) {
	
	for(unsigned int j=0;j<numal;j++){
        printf("%d | ",alumnes[j].niu);
        for(unsigned int i=0;i<4;i++){
            printf("%5.1f",alumnes[j].notes[i]);
        }
        printf(" |%6.2f",alumnes[j].notes[4]);
        printf("\n");
    }
    printf("\nS'ha llegit informacio de %d linies.\n\n",numal);
}

int ordenataula(Alu* alumnes, Alu* alumnesord, int nalum) {
	
	Alu* aux;
	aux = (Alu *)malloc(sizeof(Alu));
	
	if (aux == NULL) {
		printf("No s'ha pogut reservar la memòria per les dades\n");
		return 1;
	}
	
	for (unsigned int i=0; i<nalum; i++) {
		alumnesord[i]=alumnes[i];
	} 
	
	for (unsigned int i=0; i<nalum; i++) {
		for (unsigned int j=0; j<nalum; j++) {
			if (alumnesord[i].niu > alumnesord[j].niu && i < j) {
				aux[0] = alumnesord[i];
				alumnesord[i] = alumnesord[j];
				alumnesord[j] = aux[0];
			}
		}
	}
	return 0;
}
