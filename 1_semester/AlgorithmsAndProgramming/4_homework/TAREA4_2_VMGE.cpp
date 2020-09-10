/* Fecha: 03 de Octubre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 2 de la Tarea 4 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    Codigo que realiza operaciones (suma resta multiplicacion y division) de numeros complejos.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

// define la estructura Complejo
typedef struct Complejo {
    double real; //real
    double imag; //imaginaria
}Num; // end struct Complejo


using namespace std;

void suma_c( Num n1, Num n2, Num *n3 ){//funcion que suma dos numeros complejos

    n3->real=n1.real+n2.real;// parte real
    n3->imag=n1.imag+n2.imag;// parte real


}//end suma_c

void resta_c( Num n1, Num n2, Num *n3 ){//funcion que resta dos numeros complejos

    n3->real=n1.real-n2.real;// parte real
    n3->imag=n1.imag-n2.imag;// parte real


}//end resta_c

void mult_c( Num n1, Num n2, Num *n3 ){//funcion que multiplica dos numeros complejos

    n3->real=n1.real*n2.real-n1.imag*n2.imag;// parte real
    if((n3->real)==-0){//cuando aparecen ceros negativos
        n3->real=0.0;
    }
    n3->imag=(n1.real*n2.imag)+(n1.imag*n2.real);// parte real
    if((n3->imag)==-0){//cuando aparecen ceros negativos
        n3->imag=0.0;
    }

}//end mul_c

int div_c( Num n1, Num n2, Num *n3 ){//funcion que divide dos numeros complejos
    int t=0; //1 si se puede hacer la division o no (0)
    if((pow(n2.real,2.0)+ pow(n2.imag,2.0))>0.0001){
        n3->real=((n1.real*n2.real)+(n1.imag*n2.imag))/(pow(n2.real,2.0)+ pow(n2.imag,2.0));// parte real
        if((n3->real)==-0){//cuando aparecen ceros negativos
        n3->real=0.0;
        }

        n3->imag=(-(n1.real*n2.imag)+(n1.imag*n2.real))/(pow(n2.real,2.0)+ pow(n2.imag,2.0));// parte real
        if((n3->imag)==-0){//cuando aparecen ceros negativos
        n3->imag=0.0;
        }
        t=1;
    }


return t;
}//end div_c


int main(){
    int t=0;//para la division
    Num n1; // numeros complejos de entrada
    Num n2;

    //donde se van a guardar los resultados
    Num n3;


    cin>> n1.real>>n1.imag>>n2.real>>n2.imag; //datos de entrada

    suma_c( n1, n2, &n3 );
    printf("(%3.3f%+3.3fi)+(%3.3f%+3.3fi)=%3.3f%+3.3fi\n",n1.real,n1.imag,n2.real,n2.imag,n3.real,n3.imag); //se imprimen los resultados
    resta_c( n1, n2, &n3 );
    printf("(%3.3f%+3.3fi)-(%3.3f%+3.3fi)=%3.3f%+3.3fi\n",n1.real,n1.imag,n2.real,n2.imag,n3.real,n3.imag); //se imprimen los resultados
    mult_c( n1, n2, &n3 );
    printf("(%3.3f%+3.3fi)*(%3.3f%+3.3fi)=%3.3f%+3.3fi\n",n1.real,n1.imag,n2.real,n2.imag,n3.real,n3.imag); //se imprimen los resultados
    t=div_c( n1, n2, &n3 );
    if(t==1){//si se puede realizar la division
        printf("(%3.3f%+3.3fi)/(%3.3f%+3.3fi)=%3.3f%+3.3fi",n1.real,n1.imag,n2.real,n2.imag,n3.real,n3.imag); //se imprimen los resultados
    }else{
        printf("No es posible realizar la division"); //se imprimen los resultados
    }//end if


return 0;
}//end main
