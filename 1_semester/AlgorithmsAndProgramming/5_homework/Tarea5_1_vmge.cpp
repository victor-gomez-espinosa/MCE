/* Fecha: 18 de Octubre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 1 de la Tarea 5 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    programa que evalua una expresion postfija y devuelve el resultado de realizar la operacion.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>

using namespace std;

// estructura del nodo
struct stackNodo {
   int data; // valor del nodo
   struct stackNodo *sigPtr; // puntero al elemento que sigue en la pila
}; //

typedef struct stackNodo StackNodo; // sinonimo para la estructura stackNodo
typedef StackNodo *NodoPilaPtr; // sinonimo para StackNodo


// prototipos

//calc
int evaluarExpresionPostfija( string expr);//evaluar la expresion postfija
int calcular(int op1, int op2, string operador);//evaluar la expresion op1 operador op2

//pila
void push( NodoPilaPtr *topPtr, int valor );//introduzca un valor en la pila
int pop( NodoPilaPtr *topPtr );//saque un valor de la pila
int esVacio( NodoPilaPtr topPtr );//determinar si la pila esta vacia
void imprStack( NodoPilaPtr topPtr );//imprime la pila



int main(){
    string exppost;


    //1.-lee la expresion postfija
    cin>>exppost;

    //2.-calcula el valor
    evaluarExpresionPostfija( exppost);



    return 0;
}//end main


int evaluarExpresionPostfija( string expr)//evaluar la expresion postfija
{int n=0,x=0,y=0,resultado=0;
string operador;

   NodoPilaPtr stackPtr = NULL; // apunta al primer nodo
   int valor; // entero introducido por el usuario

    n=expr.size(); //tamano del arreglo
    for(int i=0;i<=n;i++){//recorre cada elemento del arreglo
        if(i<n){//si es menor al tamaño realiza los calculos


            if(isdigit(expr[i])==1){//si es un digito lo guarda en la pila
                valor=expr[i]-48; //onvierte de caracter a digito
                push( &stackPtr, valor ); //guarda el digito en la pila
            }else{// si es un operador
                operador=expr[i]; //guarda el operador
                if ( !esVacio( stackPtr ) ) {//si la pila no esta vacia saca el ultimo elemento y lo guarda en x
                   x=pop( &stackPtr );

                }//end if
                if ( !esVacio( stackPtr ) ) {//si la pila no esta vacia saca el ultimo elemento y lo guarda en y
                   y=pop( &stackPtr );
                }//end if
                resultado=calcular(y,x,operador); //realiza la operacion
                push( &stackPtr, resultado ); //guarda el resultado en la pila


            }//end if
        }else{//si es mayor imprime el resultado
            imprStack( stackPtr );
        }//end if

    }//end for





    return 0;
}//end evaluarExpresionPostfija

int calcular(int op1, int op2, string operador)//evaluar la expresion op1 operador op2
{int resultado=0;

    //realiza la operacion segun el operador
    if( operador =="+"){//suma
        resultado=op1+op2;
    }else if(operador =="-"){//resta
        resultado=op1-op2;
    }else if(operador =="*"){//multiplicacion
        resultado=op1*op2;
    }else if(operador =="/"){//division
        resultado=op1/op2;
    }else if(operador =="^"){//potencia
        resultado=pow(op1,op2);
    }else{
        resultado=0;
        puts( "Operador no valido\n" );
    }//end if

return resultado;
}//end calcular

// insertar un nodo al principio de la pila/stack
void push( NodoPilaPtr *topPtr, int info )
{
   NodoPilaPtr nuevoPtr; // pointer to new node

   nuevoPtr = (stackNodo*)malloc( sizeof( StackNodo ) );

   // insertar el nodo al principio del stack
   if ( nuevoPtr != NULL ) {
      nuevoPtr->data = info; //valor en el nodo
      nuevoPtr->sigPtr = *topPtr; //apunta al nodo que esta en la cima
      *topPtr = nuevoPtr; //actualiza la cima
   }
   else { // no espacio disponible
      printf( "%d no insertado. No hay memoria disponible.\n", info );
   }//end if
}//end push

// remover un nodo del principio del stack
int pop( NodoPilaPtr *topPtr )

{
   NodoPilaPtr tempPtr; // puntero temporal del nodo
   int popValue; // valor del nodo

   tempPtr = *topPtr; //guarda temporalmente el nodo de la cima
   popValue = ( *topPtr )->data; //guarda el valor del nodo
   *topPtr = ( *topPtr )->sigPtr; //actualiza el apuntador a la cima
   free( tempPtr ); //libera el nodo temporal
   return popValue; //regresa el valor del nodo
}

// imprime el stack/pila
void imprStack( NodoPilaPtr actualPtr )
{
   // si el stack esta vacio
   if ( actualPtr == NULL ) {
      puts( "La pila esta vacia.\n" );
   } //
   else {
      puts( "El resultado es:" );

      // while  no sea el final del stack
      while ( actualPtr != NULL ) {
         printf( "%d", actualPtr->data );
         actualPtr = actualPtr->sigPtr;
      } // end while


   }//end if
}// imprStack

// regresa 1 si el stack esta vacio, 0 de otra manera
int esVacio( NodoPilaPtr topPtr )
{
   return topPtr == NULL;
}//esVacio
