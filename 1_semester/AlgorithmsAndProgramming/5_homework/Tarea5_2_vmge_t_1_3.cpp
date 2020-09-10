/* Fecha: 18 de Octubre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 2 de la Tarea 5 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    programa que simula una fila de supermercado durante 12 horas.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>

using namespace std;
long long int semilla=10;
//simula LLegadas

long long int genera(long long int ant, long long int a, long long int c, long long int m){
    return (ant*a+c)%m;
}

int simulaLlegada(){
    long long int temp;
    temp=genera(semilla,16807,0,2147483647);
    semilla=temp;
    return(temp%3)+1;
}

//simula servicio
int simulaServicio(){
    long long int temp;
    temp=genera(semilla,16807,0,2147483647);
    semilla=temp;
    return(temp%4)+1;
}



// estructura autoreferencial
struct colaNodo {
    int cliente; //numero de cliente
   int llego; // tiempo de llegada
   struct colaNodo *sigPtr; // colaNodo puntero
}; //

typedef struct colaNodo ColaNodo;
typedef ColaNodo *ColaNodoPtr;

// prototipos funciones para cola
void impCola( ColaNodoPtr currentPtr );
int esVacio( ColaNodoPtr headPtr );
int quitarCola( ColaNodoPtr *headPtr, ColaNodoPtr *tailPtr );
void ponerCola( ColaNodoPtr *headPtr, ColaNodoPtr *tailPtr,
   int valor, int t );


int main(){
    int t_llegada_i=0, t_esp=0,t_esp_temp=0,t_esp_max=0,en_cola=0, en_cola_temp=0, en_cola_max=0,t_llegada=0,t_servicio=0, t=0, i=0;


   ColaNodoPtr headPtr = NULL; // inicializar headPtr
   ColaNodoPtr tailPtr = NULL; // inicializar tailPtr
   int iteme=0, items=0; // tiempo de llegada

    //primer cliente
    t_llegada=simulaLlegada();
    t_servicio=t_llegada;



    for(t=0;t<=720; t++){//tiempo de 0 a 720 minutos


        if(en_cola_temp>en_cola_max){//maximo de elementos en la cola para cualquier tiempo
            en_cola_max=en_cola_temp;
        }

        if(t_esp_temp>t_esp_max){//maximo tiempo de espera de un cliente
            t_esp_max=t_esp_temp;
        }

       if(t==t_llegada){//llega cliente?

        iteme+=1;//cliente que entra a la fila
        ponerCola( &headPtr, &tailPtr, iteme, t ); //pone en la cola el cliente y cuando llego
        en_cola+=1;//cuenta los elementos en la cola
        impCola( headPtr ); //imprime la cola
        t_llegada+=simulaLlegada();//actualiza el tiempo de llegada
        cout<<"cliente: "<<iteme<<"  llego en min: "<<t<<"\n";
            if((en_cola==1)){//la cola esta vacia?
            t_servicio=t+simulaServicio();//actualiza el tiempo de servicio


        }
       }//end if



        if(t == t_servicio){//se completo el servicio para el cliente que se està atendiendo?
            if ( !esVacio( headPtr ) ) {//si la cola tiene algo

                items+=1;//cliente que sale de la caja
               t_llegada_i = quitarCola( &headPtr, &tailPtr ); //saca al siguiente cliente de la fila y obtiene el tiempo de llegada a la fila
                en_cola-=1;//cuenta los elementos en la cola
                t_esp=t-t_llegada_i; //obtiene el tiempo de espera total del cliente
                cout<<"cliente: "<<items<<" llego en min: "<<t_llegada_i<<" sale de caja en min: "<<t<<" espero: "<<t_esp <<"\n";
                t_servicio=t+simulaServicio();

            } // end if

            impCola( headPtr ); //imprime elemento

        }//end if


    t_esp_temp=t_esp; //actualiza el valor del tiempo de espera en el ciclo
    en_cola_temp=en_cola; //actualiza el valor  de los elementos en cola por ciclo
    }//end for


    //resultados
    cout<<"a) Numero maximo de clientes en la cola en cualquier momento: "<<en_cola_max<<"\n";
    cout<<"b) La espera mas larga que un cliente experimento (min): "<<t_esp_max<<"\n";

    return 0;
}//end main




// insertar un nodo al final de la cola
void ponerCola( ColaNodoPtr *headPtr, ColaNodoPtr *tailPtr,
   int valor, int t )
{
   ColaNodoPtr nuevoPtr; // puntero a un nuevo nodo

   nuevoPtr = (colaNodo*)malloc( sizeof( ColaNodo ) );

   if ( nuevoPtr != NULL ) { // hay espacio disponible
      nuevoPtr->cliente = valor;
      nuevoPtr->llego = t;
      nuevoPtr->sigPtr = NULL;

      // si es vacio, inserta nodo al inicio/head
      if ( esVacio( *headPtr ) ) {
         *headPtr = nuevoPtr;
      }
      else {
         ( *tailPtr )->sigPtr = nuevoPtr;

      }

      *tailPtr = nuevoPtr;
   }
   else {
      printf( "%c no insertado. No hay espacio disponible.\n", valor );
   }
} // end funcion ponerCola

// quitar nodo del principio/head de la cola
int quitarCola( ColaNodoPtr *headPtr, ColaNodoPtr *tailPtr )
{
   int valor; // valor del nodo
   ColaNodoPtr tempPtr; // apuntador temporal

   valor = ( *headPtr )->llego;
   tempPtr = *headPtr;
   *headPtr = ( *headPtr )->sigPtr;

   // si la cola esta vacia
   if ( *headPtr == NULL ) {
      *tailPtr = NULL;
   }

   free( tempPtr );
   return valor;
} // end function quitarCola

// regrea 1 si la cola esta vacia, 0 de otra manera
int esVacio( ColaNodoPtr headPtr )
{
   return headPtr == NULL;
} // end function esVacio

// imprimir la cola
void impCola( ColaNodoPtr currentPtr )
{
   // si la cola esta vacia
   if ( currentPtr == NULL ) {
      puts( "La cola esta vacia.\n" );
   }
   else {
      puts( "La cola es:" );

      // mientras no se termine la estructura
      while ( currentPtr != NULL ) {

         printf( "%d --> ", currentPtr->cliente );
         currentPtr = currentPtr->sigPtr;
      }

      puts( "NULL\n" );
   }
} // end function impCola


