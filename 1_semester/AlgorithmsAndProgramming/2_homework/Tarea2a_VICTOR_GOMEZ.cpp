/* Fecha: 10 de Septiembre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 1 de la Tarea 2 de la materia Programacion y analisis de algoritmos impartida en cimat mty
 *    Codigo para simular lanzamiento de la suma de dos dados, 36000 veces. y determina si el total de veces que se rola el elemento 7 es razonable (1/6)
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

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

//
int main(){
    //declara e inicializa variables y arreglo
    int n; //numero de repeticiones
    int  **arr; //*arr es un puntero de dos dimensiones de enteros que guardan las frecuencias de los dados
    int vDado1, vDado2, suma=0,sietes=0; // guarda el valor del dado1, 2 la suma de estos y la frecuencia de sietes

    float epsilon, te, prp, fll; //parametro epsilon para comparar, valor teorico, proporcion
    char prpl[3]; //si es que se cumple la condicion

    te=1.0/6.0; //valor teorico

    arr = (int**)calloc(6,sizeof(int*));//filas  //Asigna memoria al arreglo

    for(int i=0;i<=5;i++){
        arr[i] = (int*)calloc(6,sizeof(int));//columnas //asigna memoria a las columnas
    }

    cin>>semilla>>n>>epsilon; //valores de entrada

    //hace las n repeticiones del lanzamiento del dado
    for(int i=1; i<=n; i++){
        vDado1=simulaDado();
        vDado2=simulaDado();

        suma=vDado1+vDado2; //suma los valores

        if(suma==7){ //cuanta las repeticiones cuando la suma es 7
            sietes+=1;
        }
        //guarda las frecuencias
        arr[vDado1-1][vDado2-1]+=1;
    }

    prp= (float) sietes/n; // calcula la proporcion de sietes (utiliza el casteo para convertir de int a float)

    printf( "%4s\t%4d\t%4d\t%4d\t%4d\t%4d\t%4d\n", "Dado",1,2,3,4,5,6); //encabezado

    for(int i=1; i<=6; i++){ //imprime la tabla
        printf( "%4d\t%4d\t%4d\t%4d\t%4d\t%4d\t%4d\n", i,arr[i-1][1-1],arr[i-1][2-1],arr[i-1][3-1],arr[i-1][4-1],arr[i-1][5-1],arr[i-1][6-1]);
    }

    fll=prp-te; //diferencia del valor obtenido con el teorico

    if((fabs(fll)<epsilon)){ //imprime la ultima parte
        printf("%25s\%.4f\%17s\%2s\n","La proporcion de sietes (",prp,") es razonable : ","Si");

    }else{

        printf("%25s\%.4f\%17s\%2s\n","La proporcion de sietes (",prp,") es razonable : ","No");
    }

    free(arr);  //Libera la memoria del arreglo
    return 0;
}
