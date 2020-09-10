/* Fecha: 03 de Octubre de 2019
 * Autor: VICTOR MANUEL GOMEZ ESPINOSA
 * Contexto:
 *    Parte 1 de la Tarea 4 de la materia Programación y analisis de algoritmos impartida en cimat mty
 *    Codigo para determinar el numero de dias entre dos fechas, considerando año bisiestos.
 */

//librerias
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
//#include <math.h>

// define la estructura Fecha
struct Fecha {
   unsigned int Dia; //dia
   unsigned int Mes; //mes
   unsigned int Anio; //año
}; // end struct Fecha

using namespace std;

int anio_bi(int anio){//funcion para determinar si es un año bisiesto
    int es=0; //0 si no es bisiesto, 1 si es bisiesto

    if((anio%4==0)&&((anio%100!=0)||(anio%400==0))){
        es=1;
    }//end if

return es;
}//end anio_bi

int dias_mes(int anio,int mes){//funcion que regresa el numero de dias que tiene cada mes
int ab=0; //año bisiesto
int dias=0;
    //[mes]
int meses[13];//dias que tiene cada mes

mes=mes-1;

meses[0]=31;
meses[1]=28;
meses[2]=31;
meses[3]=30;
meses[4]=31;
meses[5]=30;
meses[6]=31;
meses[7]=31;
meses[8]=30;
meses[9]=31;
meses[10]=30;
meses[11]=31;

dias=meses[mes];
ab=anio_bi(anio);

if(mes==1 && ab==1){//si es bisiesto
    dias+=1;
}//end if

return dias;
}//end dias_mes

string nombre_mes(int mes){//funcion que regresa el numero de dias que tiene cada mes
    //[mes]
string meses[13];//nombre que tiene cada mes

mes=mes-1;

meses[0]="Enero";
meses[1]="Febrero";
meses[2]="Marzo";
meses[3]="Abril";
meses[4]="Mayo";
meses[5]="Junio";
meses[6]="Julio";
meses[7]="Agosto";
meses[8]="Septiembre";
meses[9]="Octubre";
meses[10]="Noviembre";
meses[11]="Diciembre";

return meses[mes];
}//end dias_mes

//entradas: dia1, mes1, año1, dia2, mes2, año2
int c_dias(int d1, int m1, int a1, int d2, int m2, int a2){//funcion que devuelve el numero de dias entre fechas
    int dias=0;//dias que tiene un año
    int suma=0; //acumulador
    int d_anios=0;// dias acumulados entre años
    int d_anio2=0; //dias hasta la fecha 2 en ese año
    int d_anio1=0; //dias que restan para que termine ese año
    int d=0;//numero de dias

    if((a1==a2)&&(m1==m2)&&(d1==d2)){//mismo ano, mes y dia
        d=0;
    }else if((a1==a2)&&(m1==m2)){//mismo ano y mes
        d=d2-d1;
    }else if((a1==a2)){//mismo ano
        suma=0;
        for(int i=(m1+1);i<=(m2-1);i++){//obtiene el numero de dias entre meses
            suma+=dias_mes(a1,i);
        }//end for
        d=d2+(dias_mes(a1,m1)-d1)+suma;
    }else{//diferentes años

        d_anio1=c_dias(d1,m1,a1,31,12,a1); //dias que restan para que termine ese año
        d_anio2=c_dias(1,1,a2,d2,m2,a2); //dias hasta la fecha 2 en ese año


        suma=0;
        for(int i=(a1+1); i<=(a2-1); i++){//recorre los años intermedios
            if(anio_bi(i)==1){//checa si es bisiesto
                dias=366;
            }else{
                dias=365;
            }//end if
            suma+=dias;
        }//end for


        d_anios=suma;
        d=d_anio1+d_anios+d_anio2-1;
    }

return d+1;
}//end c_dias


int main(){

    // crea un registro con la estructura RegistroHerramienta en blanco
   struct Fecha fecha1 = { 0,0, 0 };
   struct Fecha fecha2 = { 0,0, 0 };

    int dias=0;
    cin>>fecha1.Dia>>fecha1.Mes>>fecha1.Anio>>fecha2.Dia>>fecha2.Mes>>fecha2.Anio; //fechas de entrada

    dias=c_dias(fecha1.Dia,fecha1.Mes,fecha1.Anio,fecha2.Dia,fecha2.Mes,fecha2.Anio);//se calculan los dias

    //se imprimen los resultados
    cout <<"La cantidad de dias entre el "<<fecha1.Dia<<" de "<<nombre_mes(fecha1.Mes)<<" de "<<fecha1.Anio<<" y"<<endl;
    cout <<"el "<<fecha2.Dia<<" de "<<nombre_mes(fecha2.Mes)<<" de "<<fecha2.Anio<<" es: "<<dias<<endl;


return 0;
}//end main
