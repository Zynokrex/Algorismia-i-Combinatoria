/*
 Programa per a solucionar equacions polinomiques de segon grau.
*/
#include <stdio.h>
#include <math.h>
#define tol 0.000000001
int main(){
    double a,b,c,discr;
    printf("\nIntroduiu les dades a,b,c del polinomi a*x^2+b*x+c:\n");
    while(scanf("%lf %lf %lf",&a,&b,&c)<3){
        while (getchar()!='\n'){}
        printf("Les dades no han entrat be....\nTorneu-hi...\n");
    }
    if(fabs(a)<tol){
		if (fabs(b)<tol) {
			printf("S\'han introduït dades que generen una equació sense incògnita.\n");			
		} else {
        printf("L'equacio no es de segon grau si poseu a=0 .\n");
        printf("La solucio de\n (%.12lf) * x + (%.12lf) =0\nes:\n",b,c);
        printf("x= %.12lf\n",-c/b);
		}
    }
    else{
        discr= b*b -4*a*c;
        if(discr<0){
            printf("\nEquacio sense solucions reals\n");
            printf("La solucio de l'equacio\n");
            printf("(%.12lf)*x^2+(%.12lf)*x+(%.12lf)=0\n",a,b,c);
            printf("es\n");
            printf("x=%.12lf - i*%.12lf\n", b/(2*a), sqrt(4*a*c-(b*b))/(2*a));
            printf("x=%.12lf + i*%.12lf\n", b/(2*a), sqrt(4*a*c-(b*b))/(2*a));
        }
        else{
            if(discr<tol){
                printf("\nEquacio amb solucio doble:\n");
                printf("La solucio de l'equacio\n");
                printf("(%.12lf)*x^2+(%.12lf)*x+(%.12lf)=0\n",a,b,c);
                printf("es\n");
                printf("x=%.12lf\n",-b/(2*a));
            }
            else{
                discr=sqrt(discr);
                printf("\nEquacio amb dues solucions.\n");
                printf("Les solucions de l'equacio\n");
                printf("(%.12lf)*x^2+(%.12lf)*x+(%.12lf)=0\n",a,b,c);
                printf("son\n");
                printf("x=%.12lf, x=%.12lf\n\n",(-b+discr)/(2*a), (-b-discr)/(2*a));
            }
        }
    }
    return 0;
}
