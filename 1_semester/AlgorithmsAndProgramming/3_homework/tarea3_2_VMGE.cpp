/* Fecha: 30 de Septiembre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 2 de la Tarea 3 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    Codigo para simular las palabras que se forman dado un numero telefonico de 3 a 6 digitos.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//#include <math.h>
#include<string.h>

using namespace std;

string sel_letra(int digito, int orden){//funcion que regresa la letra seleccionada
    string seleccion; //letra seleccionada
    string M[9][4]; //filas: digito seleccionado, columnas: orden seleccionado

    M[2-2][0]="A", M[2-2][1]="B", M[2-2][2]="C";
    M[3-2][0]="D", M[3-2][1]="E", M[3-2][2]="F";
    M[4-2][0]="G", M[4-2][1]="H", M[4-2][2]="I";
    M[5-2][0]="J", M[5-2][1]="K", M[5-2][2]="L";
    M[6-2][0]="M", M[6-2][1]="N", M[6-2][2]="O";
    M[7-2][0]="P", M[7-2][1]="R", M[7-2][2]="S";
    M[8-2][0]="T", M[8-2][1]="U", M[8-2][2]="V";
    M[9-2][0]="W", M[9-2][1]="X", M[9-2][2]="Y";

    seleccion=M[digito][orden];

    return seleccion;
}//end sel_letra

//cada nivel del arbol esta sociado a un digito
// pal(ns-2)-ir(ns-1)/i0(ns)
//                   -i1(ns)
//                   \i2(ns)
int heap_t(string pal, int ir, int ns, int nt, int vdigitos[]){//funcion que simula un arbol con una raiz en el nivel ns-1 y 3 hojas en el ns y una palabra que viene de un nivel ns-2
    //pal palabra a un nodo anterior, 0<=ir<=2 nodo raiz, 1<=ns<=nt subnivel, 3<=nt<=6 niveles totales, vector con los digitos
    string palr, paln, ptem; //palabra que se forma en la raiz, palabra nueva
    int digito=0;
    int orden=0;
    orden=ir;
    digito=vdigitos[(6-nt)+(ns-1)-1]-2; //digito relacionado en la raiz (nivel ns-1)
    palr=pal+sel_letra(digito,orden); //selecciona y concatena


    if(ns==nt){//caso base, cuando esta en el ultimo nivel, se imprimen las combinaciones
        digito=vdigitos[(6-nt)+(ns-1)]-2; //digito del nivel actual
        for(int i=0; i<=2; i++){//concatena con la palabra formada en la raiz y cada una de las 3 posibles en las hojas e imprime una por una
            orden=i;
            paln=palr+sel_letra(digito,orden);

            cout <<paln << endl;
        }//end for
    }else if( (ns>=3) && (ns<=(nt-1)) ) {//si se encuentra en nodos intermedios ns>3 y ns<nt-1
        for(int i=0; i<=2; i++){//concatena con la palabra formada en la raiz y cada una de las 3 posibles en las hojas e imprime una por una
            heap_t( palr, i, ns+1, nt, vdigitos); //se llama asi misma, lo hace para las 3 opciones y aumenta el nivel y usa la palabra de la raiz (nodo anterior)
        }//end for
    }else if(ns==2){

        for(int i=0; i<=2; i++){//concatena con la palabra formada en la raiz y cada una de las 3 posibles en las hojas e imprime una por una

            heap_t( pal, i, ns+1, nt, vdigitos); //se llama asi misma, lo hace para las 3 opciones y aumenta el nivel y usa la palabra principal (nodo 1)
        }//end for
    }//end if


    //return seleccion;
  return 0;
}//end sel_letra


int main(){

    string pal1, pal2, pal3, paln;
    unsigned int N=0; //numero telefonico de tamaño 3<=N<=6 y condigitos de 2 a 9
    int n=0; //numero de digitos //n tambien va a indicar el nivel en el arbol
    int vdigitos[7]={0}; //vector donde se guardan los digitos
    int digito=0;

    cin>>N; //numero de entrada

    int n_camb=N, ex=1, residu=0; //variables necesarias para descomponer en digitos el numero
    int i=0; //posicion en arreglos

    i=6;//inicia en tamaño maximo de digitos
    while((N/ex)>0){//descompone el numero en digitos
        i-=1;
        n+=1; //cuenta el numero de digitos
        residu=(n_camb%10);
        vdigitos[i]=residu; //va guardando en el vector los digitos de derecha a izquierda
        n_camb/=10;
        ex*=10;

    }//end while

    digito=vdigitos[(6-n)+(1-1)]-2; //letras del primer digito
    pal1=sel_letra(digito,0);
    pal2=sel_letra(digito,1);
    pal3=sel_letra(digito,2);

    heap_t( pal1, 0, 2, n, vdigitos); //aplica la funcion para cada letra del primer digito (primer nivel)
    heap_t( pal2, 0, 2, n, vdigitos);
    heap_t( pal3, 0, 2, n, vdigitos);

    return 0;
}//end main
