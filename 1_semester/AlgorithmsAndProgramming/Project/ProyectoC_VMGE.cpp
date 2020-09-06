/* Fecha: 10 de Diciembre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Proyecto final de la materia Programación y análisis de algoritmos de la Maestría en Computo Estadístico de CIMAT.
 *    Programa que simula un sistema de cola de tamano finito y 1 servidor y repite el experimento una cantidad de veces.
 */


/* Headers necesarios para el funcionamiento*/
#include <Rcpp.h>
using namespace Rcpp;

#include<bits/stdc++.h>
using namespace std;

//funciones necesarias
inline int simula_tiempos(int mu) { //simula tiempos exponenciales con parametro mu
    double v1;
    v1 = (rand() % 100)+1;
    v1=v1/100; //numero aleatorio entre 0-1

    if(v1>=1.0){
            v1=0.99;
    }else if(v1<=0.0){
        v1=0.01;
    }

  return -mu*(log(1-v1)); //numero aleatorio exponencial
}


inline double experimento(int ts, int ta, int m, int s, int tt, int op){ //funcion que simula el experimento de un sistema con un servidor (caja, mesa, etc.) y una cola
    //parametros de entrada: ts tiempo promedio por servicio [minutos], ta tiempo promedio de por llegada [minutos], m tamaño de la cola, s cantidad de servidores (siempre debe ser 1)
    //tt tiempo total de simulacion [horas], op opcion de resultado 1 ocurrio el evento que estuviera lleno al menos una vez, 2 clientes que se fueron, 3 clientes esperados
    double res=0;

    tt=tt*60; //convierte de horas a minutos
    queue<int> q; //cola

    int N=0, ms=0, ss=0, Ns=0; //N tamaño del sistema, ms elementos en la cola simulado, ss elementos en servicio simulado, Ns elementos en el sistema simulado
    int t_llegada=0, t_simulacion=0, t_servicio=0;
    double evento_llegadas=0, evento_sistema_lleno=0;
    int clientes=0;
    int t_llegada_anterior=0;
    N=m+s;

    t_llegada=simula_tiempos(ta); //simula el primer tiempo de llegada

    for(t_simulacion=0;t_simulacion<=tt; t_simulacion++){//tiempo de simulacion de 0 hasta el tiempo total, en minutos

        if(t_simulacion==t_llegada){//llega cliente. entrada al sistema
            t_llegada_anterior=t_llegada;
            evento_llegadas+=1;//clientes que llegan
            t_llegada=t_simulacion+simula_tiempos(ta); //actualiza el tiempo de llegada
            while(t_llegada_anterior==t_llegada){
                t_llegada=t_simulacion+simula_tiempos(ta); //actualiza el tiempo de llegada
            }

            if(Ns<N){//hay lugar en el sistema? entra
                    clientes+=1;
                    if(ss==0){//si no hay alguien en servicio, pasa directamente a servicio
                            ss=1; //actualiza el estado del servicio
                            t_servicio=t_simulacion+simula_tiempos(ts); //tiempo de finalizacion del servicio
                            while(t_servicio==t_simulacion){
                                t_servicio=t_simulacion+simula_tiempos(ts); //tiempo de finalizacion del servicio
                            }//end while
                    }else{//si hay alguien en servicio. lo pone en la cola
                        ms+=1; //actualiza el estado de la cola
                        q.push(t_simulacion);




                    }//end if

            }else{//no hay lugar se va
                evento_sistema_lleno+=1;

            }//end if

        }//end if


        if(t_simulacion==t_servicio){//se completo el servicio
                ss=0; //se actualiza el estado del servicio

                if(ms!=0){//si hay alguien en cola, se pasa a servicio
                    ss=1; //se actualiza el estado del servicio
                    q.pop();
                    ms-=1; //se actualiza el estado de la cola
                    t_servicio=t_simulacion+simula_tiempos(ts); //actualiza el tiempo de finalizacion del servicio
                    while(t_servicio==t_simulacion){
                                t_servicio=t_simulacion+simula_tiempos(ts); //tiempo de finalizacion del servicio
                    }//end while

                }//end if

        }//end if

        Ns=ms+ss; //actualiza los elementos en el sistema



    }//end for



    if(op==1){//ocurrio el evento sistema lleno

        res=evento_sistema_lleno/evento_llegadas;


    }else if(op==2){//cuantos clientes se fueron
        res=evento_sistema_lleno;
    }else if(op==3){//clientes esperados
        res=clientes;

    }//end if


return res;
}



/* Header para la exportacion */
// [[Rcpp::export]]
double cola_finitaC(int ts, int ta, int m, int s, int tt, int op, int rep){//funcion que simula el experimento un numero determinado de veces
    //parametros de entrada: ts tiempo promedio por servicio [minutos], ta tiempo promedio de por llegada [minutos], m tamaño de la cola, s cantidad de servidores (siempre debe ser 1)
    //tt tiempo total de simulacion [horas], op opcion de resultado 1 ocurrio el evento que estuviera lleno al menos una vez, 2 clientes que se fueron, 3 clientes esperados
    //rep numero de repeticiones

double param=0; //resultado del parametro seleccionado en una simulacion
double acumulador=0;
double res=0; //resultado
int i=0;

 for(i=1;i<=rep; i++){//repeticion del experimento

    param=experimento(ts, ta, m,  s,  tt,  op);
    acumulador+=param;

 }


    res=acumulador/rep; //calcula el promedio o la frecuencia del evento





return res;
}






