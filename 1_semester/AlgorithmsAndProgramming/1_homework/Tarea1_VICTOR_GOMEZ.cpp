/* Fecha: 28 de Agosto de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Codigo para simular lanzamiento de dados, frecuencia de cada lado del dado, repeticion mas larga consecutiva de un lado,
      y repeticion de la secuencia 123456
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

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
    int  *arr; //*arr es un puntero de enteros guardan las frecuencias y la repeticion continua
    int vDado, temp=0; // guarda el valor del dado actual y el anterior
    int cont=1, contemp=0, valRep=0, valReptemp=0; //contador repeticion de numero actual, contador de repeticion pasado,
                                                    //valor repetido, valor repetido anterior
    int seqc=1, repseq=0; //contador para checar secuencia completa 123456, contador de las repeticiones de la secuencia 123456

    arr = (int*)malloc(5*sizeof(int));    //Asigna memoria al arreglo

    for(int i=0; i<=5; i++){ //inicializa el vector de frecuencias en 0
    arr[i]=0;

    }

    cin>>semilla>>n; //valores de entrada

    //hace las n repeticiones del lanzamiento del dado
    for(int i=1; i<=n; i++){
        vDado=simulaDado();

        //guarda las frecuencias
        arr[vDado-1]+=1;


        //if(n>1){
        //b) repeticion continua mas larga del mismo numero
            if(vDado==temp){//verifica repeticion con el anterior y guarda el numero y cuenta las repeticiones
                cont+=1;
                valRep=vDado;

                if(cont>=contemp){//si la frecuencia de repeticion es mayor a la anteior la cambia
                    contemp=cont;
                    valReptemp=valRep;
                }

            }else{//si se deja de repetir reinicia el contador
                cont=1;
                valRep=0;

            }

        //seq 123456

            if(vDado>temp){//verifica que el resultado actual sea mayor al anterior y va contando
                seqc+=1;
                if(seqc==6){//si se comleta la secuencia aumenta en 1 la repeticion
                    repseq+=1;
                }
            }else{//sino reinicia el contador
                seqc=1;


            }








    temp=vDado; //guarda temporalmente el valor
    }

    //imprime resultados
    cout<<"Apariciones del numero  1: "<<arr[0]<<"\n";
    cout<<"Apariciones del numero  2: "<<arr[1]<<"\n";
    cout<<"Apariciones del numero  3: "<<arr[2]<<"\n";
    cout<<"Apariciones del numero  4: "<<arr[3]<<"\n";
    cout<<"Apariciones del numero  5: "<<arr[4]<<"\n";
    cout<<"Apariciones del numero  6: "<<arr[5]<<"\n";
    cout<<"El numero con repeticion continua mas larga es "<<valReptemp<<" y la cantidad de repeticiones es: "<<contemp<<"\n";
    cout<<"La cantidad de veces que la secuencia 123456 aparece es: "<<repseq<<"\n";

}
