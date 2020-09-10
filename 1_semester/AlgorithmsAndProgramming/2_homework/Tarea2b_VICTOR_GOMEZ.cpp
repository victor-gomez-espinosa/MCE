/* Fecha: 11 de Septiembre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 2 de la Tarea 2 de la materia Programacion y analisis de algoritmos impartida en cimat mty
 *    Codigo para simular el juego de craps N veces
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//#include <math.h>

//simula dado
using namespace std;
long long int genera(long long int ant, long long int a, long long int c, long long int m){
    return (ant*a+c)%m;
}
long long int semilla;
int simulaDado(){
    long long int temp;
    temp=genera(semilla,16807,0,2147483647);
    semilla=temp;
    return(temp%6)+1;
}

//simula craps, recibe de argumentos las direcciones de dos punteros de tipo entero
int craps(int *p, int *q){ //p-tiros q-gana
    //declara variables
    int  meta=0, fin=0,  suma=0; //meta, fin del juego (0-false), suma de los dados
    int tiros, gana;

    tiros=0;
    gana=0;

    //primer tiro
    tiros+=1;
    suma=simulaDado()+simulaDado();

    if(suma==7 || suma==11){//gana
        gana=1;
        fin=1;
    }else if((suma==2 || suma==3) || suma==12){//pierde
        gana=0;
        fin=1;
    }else{ //se actualiza la meta
        meta=suma;
    }

    while(fin!=1){//si el juego continua
        tiros+=1;
        suma=simulaDado()+simulaDado();

        if(suma==meta){//gana
            gana=1;
            fin=1;
        }else if(suma==7){//pierde
            gana=0;
            fin=1;
        }
    }

    //cambia el valor de los punteros
    *p=tiros;

    *q=gana;

    return 0;

}
//
int main(){
    //declara e inicializa variables y arreglo
    int n; //numero de repeticiones
    int  **arr; //*arr es un puntero de dos dimensiones de enteros que guardan las frecuencias de los dados
    int gana=0, tiros=0, tirosT=0, pgt=0; // gana (0-False), Tiros, tiros totales, juegos ganados totales

    float tirosTp=0.0, p=0.0; //tiempo promedio, probabilidad de ganar el juego

    arr = (int**)calloc(22,sizeof(int*));//filas  //Asigna memoria al arreglo


    for(int i=0;i<=21;i++){
        arr[i] = (int*)calloc(2,sizeof(int));//columnas //Asigna memoria al arreglo
    }


    cin>>semilla>>n; //valores de entrada

    //hace las n repeticiones del lanzamiento del dado
    for(int i=1; i<=n; i++){
        craps(&tiros,&gana); //simula el juego de craps

        tirosT+=tiros; //cuenta los tiros
        if(tiros>20){//si es mayor a 20 cambia el indice para guardarlo en la matriz
            tiros=21;
        }

        if(gana==1){//cuenta los juegos ganados
            pgt+=1;
        }

        //guarda las frecuencias
        arr[tiros-1][gana]+=1;

    }

    p= (float) pgt/n; //prob. de ganar
    tirosTp= (float) tirosT/n; // calcula el tiempo promedio del juego


    //imprime resultados
    printf("Juegos Ganados\n");
    printf("Tiros\tJuegos\n");
    printf("     \tGanados\n");

    for(int i=1; i<=20; i++){ //imprime la tabla
        printf( "%3d\t\%6d\n", i,arr[i-1][2-1]);
    }
    printf("20+\t\%6d\n",arr[21-1][2-1]);

    printf("Juegos Perdidos\n");
    printf("Tiros\tJuegos\n");
    printf("     \tPerdidos\n");

    for(int i=1; i<=20; i++){ //imprime la tabla
        printf( "%3d\t\%6d\n", i,arr[i-1][1-1]);
    }
    printf("20+\t\%6d\n",arr[21-1][1-1]);

    printf("La posibilidad de ganar el juego es: %.4f\n",p);
    printf("La duracion promedio del juego es: %.4f\n",tirosTp);


    free(arr);  //Libera la memoria del arreglo
    return 0;
}
