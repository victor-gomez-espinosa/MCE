/* Fecha: 04 de Octubre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 3 de la Tarea 4 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    Codigo que realiza operaciones (suma resta multiplicacion y division) de numeros racionales y los reporta como fraccion simplificada.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

// define la estructura Racional
typedef struct Racional {
    double numer; //numerador
    double denom; //denominador
}Num; // end struct Racional


using namespace std;


double mcdf(double num, double denom){
    double r=1;

    int i=0;
    while(ri!=0){
        rim=fmod(rime,ri);

    }



return r;

}
void simp_r( double a, double b,  Num *n3 ){//funcion que simplifica un numeros racional
    double maxcd=mcdf(a,b);
    a/=maxcd;
    a/=maxcd;
    n3->numer=a;
    n3->denom=b;


}//end simp_r


void suma_r( double a, double b, double c, double d, Num *n3 ){//funcion que suma dos numeros racionales

    n3->numer=a*d+b*c;// numerador
    if((n3->numer)==-0){//cuando aparecen ceros negativos
        n3->numer=0;
    }

    n3->denom=b*d;// denominador



    if((n3->numer/n3->denom)<0){//pone el simbolo en el numerador
        n3->denom=fabs(n3->denom);
        if((n3->numer)>0){
            n3->numer=-1*(n3->numer);
        }//end if

    }else{
        if((n3->numer)<0 && (n3->numer)<0 ){//si ambos son negativos los vuelve positivos
            n3->denom=fabs(n3->denom);
            n3->numer=fabs(n3->numer);
        }//end if
    }//end if


    if((n3->numer)==0){//cuando aparecen ceros
        n3->denom=1;
    }//end if

    simp_r(n3->numer,n3->denom, n3); //simplifica



}//end suma_r

void resta_r( double a, double b, double c, double d, Num *n3 ){//funcion que resta dos numeros racionales

    c*=(-1);
    suma_r(a,b,c,d, n3);


}//end resta_r

void mult_r( double a, double b, double c, double d, Num *n3 ){//funcion que multiplica dos numeros racionales

    n3->numer=a*c;// numerador
    if((n3->numer)==-0){//cuando aparecen ceros negativos
        n3->numer=0;
    }

    n3->denom=b*d;// denominador

    if((n3->numer/n3->denom)<0){//pone el simbolo en el numerador
        n3->denom=fabs(n3->denom);
        if((n3->numer)>0){
            n3->numer=-1*(n3->numer);
        }

    }else{
        if((n3->numer)<0 && (n3->numer)<0 ){//si ambos son negativos los vuelve positivos
            n3->denom=fabs(n3->denom);
            n3->numer=fabs(n3->numer);
        }
    }//end if

    if((n3->numer)==0){//cuando aparecen ceros
        n3->denom=1;
    }//end if

    simp_r(n3->numer,n3->denom, n3); //simplifica

}//end mul_r

int div_r( double a, double b, double c, double d, Num *n3 ){//funcion que divide dos numeros racionales
    int t=0; //1 si se puede hacer la division o no (0)
    if((b*c)!=0){
        mult_r(a,b,d,c,n3);
        t=1;
    }//end if


return t;
}//end div_r


int main(){
    int t=0;//para la division
    Num n1; // numeros racionales de entrada
    Num n2;

    //donde se van a guardar los resultados
    Num n3;

    Num t1;
    Num t2;


    cin>> n1.numer>>n1.denom>>n2.numer>>n2.denom; //datos de entrada

    t1.numer=n1.numer;
    t1.denom=n1.denom;
    t2.numer=n2.numer;
    t2.denom=n2.denom;

    simp_r(t1.numer,t1.denom, &t1);
    simp_r(t2.numer,t2.numer, &t2);

    if((n1.denom<0) && (n2.denom<0)){//si ambos denominadores son negativos
        suma_r( t1.numer, t1.denom, t2.numer, t2.denom, &n3 );
        printf("(%0.0f/(%0.0f))+(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        resta_r( t1.numer, t1.denom, t2.numer, t2.denom, &n3  );
        printf("(%0.0f/(%0.0f))-(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        mult_r( t1.numer, t1.denom, t2.numer, t2.denom, &n3  );
        printf("(%0.0f/(%0.0f))*(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        t=div_r( t1.numer, t1.denom, t2.numer, t2.denom, &n3  );
        if(t==1){//si se puede realizar la division
            printf("(%0.0f/(%0.0f))/(%0.0f/(%0.0f))=%0.0f/%0.0f",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        }else{
            printf("No es posible realizar la division"); //se imprimen los resultados
        }//end if

    }else if((n1.denom<0) && (n2.denom>0)){//si solo el primer denominador es negativo
        suma_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3 );
        printf("(%0.0f/(%0.0f))+(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        resta_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/(%0.0f))-(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        mult_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/(%0.0f))*(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        t=div_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        if(t==1){//si se puede realizar la division
            printf("(%0.0f/(%0.0f))/(%0.0f/%0.0f)=%0.0f/%0.0f",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        }else{
            printf("No es posible realizar la division"); //se imprimen los resultados
        }//end if

    }else if((n1.denom>0) && (n2.denom<0)){//si solo el segundo denominador es negativo

        suma_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3 );
        printf("(%0.0f/%0.0f)+(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        resta_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/%0.0f)-(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        mult_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/%0.0f)*(%0.0f/(%0.0f))=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        t=div_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        if(t==1){//si se puede realizar la division
            printf("(%0.0f/%0.0f)/(%0.0f/(%0.0f))=%0.0f/%0.0f",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        }else{
            printf("No es posible realizar la division"); //se imprimen los resultados
        }//end if

    }else{//si ambos son positivos
        suma_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3 );
        printf("(%0.0f/%0.0f)+(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        resta_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/%0.0f)-(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        mult_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        printf("(%0.0f/%0.0f)*(%0.0f/%0.0f)=%0.0f/%0.0f\n",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        t=div_r( n1.numer, n1.denom, n2.numer, n2.denom, &n3  );
        if(t==1){//si se puede realizar la division
            printf("(%0.0f/%0.0f)/(%0.0f/%0.0f)=%0.0f/%0.0f",n1.numer,n1.denom,n2.numer,n2.denom,n3.numer,n3.denom); //se imprimen los resultados
        }else{
            printf("No es posible realizar la division"); //se imprimen los resultados
        }//end if



    }//end if





return 0;
}//end main
