#include<stdio.h>

#define NGERRES 3
#define MAXLITRES 10
#define MAXCONF 20

typedef struct{
    unsigned capacitat,contingut;
}gerra;

typedef struct{
    unsigned continguts[NGERRES];
}configuracio;

configuracio transvasament(unsigned, unsigned, configuracio, gerra*);

int main(int argc, char *argv[])
{
    unsigned i,j,k,l;
    int falla=-1;
    char estat_config[MAXLITRES+1][MAXLITRES+1][MAXLITRES+1];
    unsigned cap1, cap2, cap3, cont1, cont2, cont3;	//Valors auxiliars per comprovar que tot estigui bé
    if (argc<7
         || sscanf(argv[1], "%u", &cap1)!=1
         || sscanf(argv[2], "%u", &cont1)!=1
         || sscanf(argv[3], "%u", &cap2)!=1
         || sscanf(argv[4], "%u", &cont2)!=1
         || sscanf(argv[5], "%u", &cap3)!=1
         || sscanf(argv[6], "%u", &cont3)!=1
      ) {
      fprintf(stderr,"%s cap1 cont1 cap2 cont2 cap3 cont3\n", argv[0]);
      return -1;
    } else { //Llegeix bé els arguments, mirem si algun és incorrecte
		if((cap1 > MAXLITRES) || (cont1 > cap1)) falla = 0;
		else if((cap2 > MAXLITRES) || (cont2 > cap2)) falla = 1;
		else if((cap3 > MAXLITRES) || (cont3 > cap3)) falla = 2;
		
		if (falla>=0){
			printf("Configuració no possible a la gerra %d\n", falla);
			return -1;
		}
	}
    gerra gerres[NGERRES] = {{cap1, cont1},{cap2, cont2},{cap3, cont3}};
    
    configuracio configuracions[MAXCONF+1];
    printf("Gerres amb capacitats |");
    for(l=0;l<NGERRES;l++) printf("%u|",gerres[l].capacitat);
    printf("\n");
    for(i=0;i<gerres[0].capacitat+1;i++){
        for(j=0;j<gerres[1].capacitat+1;j++){
            for(k=0;k<gerres[2].capacitat+1;k++){
                estat_config[i][j][k]=0;
            }
        }
    }
    for(l=0;l<NGERRES;l++) configuracions[0].continguts[l]=gerres[l].contingut;
    printf("Configuració inicial  |");
    for(l=0;l<NGERRES;l++) printf("%u|",configuracions[0].continguts[l]); 
    printf("\n");
    estat_config[configuracions[0].continguts[0]][configuracions[0].continguts[1]][configuracions[0].continguts[2]]=1;
    int num_conf=1;
    for(i=0;i<num_conf && num_conf<MAXCONF;i++){
        for(j=0;j<NGERRES && num_conf<MAXCONF;j++){
            for(k=0;k<NGERRES && num_conf<MAXCONF;k++){
                if(j==k) continue;
                if(configuracions[i].continguts[j]==0) continue;
                if(configuracions[i].continguts[k]==gerres[k].capacitat) continue;
                configuracions[num_conf]=transvasament(j,k,configuracions[i],gerres);	//Crida a transvasament
                if(estat_config[configuracions[num_conf].continguts[0]][configuracions[num_conf].continguts[1]][configuracions[num_conf].continguts[2]]==1) continue;
                estat_config[configuracions[num_conf].continguts[0]][configuracions[num_conf].continguts[1]][configuracions[num_conf].continguts[2]]=1;
                printf("De configuració %u a %u: |",i,num_conf);
                for(l=0;l<NGERRES;l++) printf("%u|",configuracions[i].continguts[l]);
                printf("-(%u,%u)-|",j,k);
                for(l=0;l<NGERRES;l++) printf("%u|",configuracions[num_conf].continguts[l]);
                printf("\n");
                num_conf++;
            }
        }
    }
    
    if(num_conf==MAXCONF){
        printf("Hem arribat al màxim de configuracions i pot ser no s'han fet totes\n");
        return 1;
    }
    printf("S'han trobat %u configuracions possibles\n",num_conf);
    return 0;
}

configuracio transvasament(unsigned j, unsigned k, configuracio old_configuracions, gerra* gerres){
	configuracio configuracions;
	for(unsigned l=0;l<NGERRES;l++) configuracions.continguts[l]=old_configuracions.continguts[l];
	configuracions.continguts[k]=configuracions.continguts[k]+configuracions.continguts[j];
	configuracions.continguts[j]=0;
	if(configuracions.continguts[k]>gerres[k].capacitat){
		configuracions.continguts[j]=configuracions.continguts[k]-gerres[k].capacitat;
		configuracions.continguts[k]=gerres[k].capacitat;
	}
	return configuracions;
}
