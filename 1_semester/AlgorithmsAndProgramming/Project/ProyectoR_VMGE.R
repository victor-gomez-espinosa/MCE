## Fecha: 10 de Diciembre de 2019
## Autor: VICTOR MANUEL GOMEZ ESPINOSA
## Contexto:
##    Proyecto final de la materia Programación y análisis de algoritmos de la Maestría en Computo Estadístico de CIMAT.
##    Programa que simula un sistema de cola de tamano finito y 1 servidor y repite el experimento una cantidad de veces.
##

#####################################################################################################################################
## 1.- Código
# se cargan las librerías necesarias, se conecta con el código en C++ y se escribe el mismo en R

#librerias
library(Rcpp)
library(microbenchmark)
library(ggplot2) #plots


#codigo en c++
sourceCpp("ProyectoC_VMGE.cpp")



#codigo en R
experimentoR<-function(ts, ta, m, s, tt, op){#funcion que simula el experimento de un sistema con un servidor (caja, mesa, etc.) y una cola
  #parametros de entrada: ts tiempo promedio por servicio [minutos], ta tiempo promedio de por llegada [minutos], m tamaño de la cola, s cantidad de servidores (siempre debe ser 1)
  #tt tiempo total de simulacion [horas], op opcion de resultado 1 ocurrio el evento que estuviera lleno al menos una vez, 2 clientes que se fueron, 3 clientes esperados
  tt<-tt*60 #convierte de horas a minutos
  
  #N tamaño del sistema<- ms elementos en la cola simulado<- ss elementos en servicio simulado<- Ns elementos en el sistema simulado
  N<-0
  ms<-0 
  ss<-0
  Ns<-0 
  t_llegada<-0
  t_simulacion<-0
  t_servicio<-0
  evento_llegadas<-0
  evento_sistema_lleno<-0
  clientes<-0
  t_llegada_anterior<-0
  N<-m+s
  
  t_llegada<-round(rexp(1,1/ta),0) #simula el primer tiempo de llegada
  
  for(t_simulacion in 0:tt){#tiempo de simulacion de 0 hasta el tiempo total<- en minutos
    
    if(t_simulacion==t_llegada){#llega cliente. entrada al sistema
      t_llegada_anterior<-t_llegada
      evento_llegadas<-evento_llegadas+1#clientes que llegan
      t_llegada<-t_simulacion+round(rexp(1,1/ta),0) #actualiza el tiempo de llegada
      while(t_llegada_anterior==t_llegada){
        t_llegada<-t_simulacion+round(rexp(1,1/ta),0) #actualiza el tiempo de llegada
      }
      
      if(Ns<N){#hay lugar en el sistema? entra
        clientes<-clientes+1
        if(ss==0){#si no hay alguien en servicio<- pasa directamente a servicio
          ss<-1 #actualiza el estado del servicio
          t_servicio<-t_simulacion+round(rexp(1,1/ts),0) #tiempo de finalizacion del servicio
          while(t_servicio==t_simulacion){
            t_servicio<-t_simulacion+round(rexp(1,1/ts),0) #tiempo de finalizacion del servicio
          }#end while
        }else{#si hay alguien en servicio. lo pone en la cola
          ms<-ms+1 #actualiza el estado de la cola
          
        }#end if
        
      }else{#no hay lugar se va
        evento_sistema_lleno<-evento_sistema_lleno+1
        
      }#end if
      
    }#end if
    
    
    if(t_simulacion==t_servicio){#se completo el servicio
      ss<-0 #se actualiza el estado del servicio
      
      if(ms!=0){#si hay alguien en cola<- se pasa a servicio
        ss<-1 #se actualiza el estado del servicio
        
        ms<-ms-1 #se actualiza el estado de la cola
        t_servicio<-t_simulacion+round(rexp(1,1/ts),0) #actualiza el tiempo de finalizacion del servicio
        while(t_servicio==t_simulacion){
          t_servicio<-t_simulacion+round(rexp(1,1/ts),0) #tiempo de finalizacion del servicio
        }#end while
        
      }#end if
      
    }#end if
    
    Ns<-ms+ss #actualiza los elementos en el sistema
    
    
    
  }#end for
  
  
  
  if(op==1){#ocurrio el evento sistema lleno
    
    res<-evento_sistema_lleno/evento_llegadas
    
    
  }else if(op==2){#cuantos clientes se fueron
    res<-evento_sistema_lleno
  }else if(op==3){#clientes esperados
    res<-clientes
    
  }#end if
  
  
  
  return(res)
}
cola_finitaR<-function(ts,ta,m, s,tt,op, repe){#funcion que simula el experimento un numero determinado de veces
  
  fx2<-replicate(repe, experimentoR(ts,ta,m, s,tt,op))
  fx2<-mean(fx2)
  return(fx2)
  
}

#####################################################################################################################################
## 2.- Comparación de rendimientos de R contra C


#compara el rendimiento del codigo en C++ contra R
microbenchmark(
  cola_finitaR(12,15,2,1,40,1,1e3),
  cola_finitaC(12,15,2,1,40,1,1e3)
)

#####################################################################################################################################
## 3.- Simulación de ejemplos de libro

## 3.1.- Ejemplo 1
#simulacion del ejemplo 4.2 del libro: Fundamentals of Queuing Systems. De Nick T. Thomopoulus, pag. 32 
#barberia con s=1 barbero y m=2 lugares disponibles de espera.
#tiempo pomedio de 1 servicio [min] ts=12, tiempo promedio de llegada de 1 cliente [min] ta=15
#tiempo total abierto simulado (8 hrs/dia*5dias) tt=40
#numero de repeticiones repe=1e4

costo<-12 #costo por corte
p_cperdidos<-cola_finitaC(12,15,2,1,40,1,1e4) #probabilidad de perder clientes
c_perdidos<-cola_finitaC(12,15,2,1,40,2,1e4) #clientes perdidos esperados por semana
c_esperados<-cola_finitaC(12,15,2,1,40,3,1e4) #clientes esperados por semana
ganancias<-costo*c_esperados #ganancias esperadas por semana
perdidas<-costo*c_perdidos #perdidas esperadas por semana

## Resultados
cat("Probabilidad de perder clientes :",round(p_cperdidos,2),"\n" )
cat("Clientes perdidos esperados por semana :",round(c_perdidos,0),"\n" )
cat("Clientes esperados por semana :",round(c_esperados,0),"\n" )
cat("Ganancias esperadas por semana :",round(ganancias,0),"\n" )
cat("Perdidas esperadas por semana :",round(perdidas,0),"\n" )

## 3.2.- Ejemplo 2
#simulacion del ejemplo 4.3 del libro: Fundamentals of Queuing Systems. De Nick T. Thomopoulus, pag. 33 
#con s=1 servidor (barbero, caja, etc.) 
#tiempo promedio de llegada de 1 cliente [min] ta=15
#tiempo total abierto simulado (8 hrs/dia*5dias) tt=40
#numero de repeticiones repe=1e4
#varia el tiempo promedio de 1 servicio ts [min] 1.5-13.5
#y los lugares disponibles de espera, tamaño de la fila (mesas disponibles, asientos de espera, etc.) m 0-9
#ts=ro*ta

simula_col<-function(n){#funcion para cada columna de la tabla, segun un tamaño de la fila, varia la tasa de servicio
  ro<-seq(from=0.1, to=0.9, by=0.1) #relacion de la tasa de servicio con la de llegadas
  ta<-15 #tasa de llegadas 
  vts<-ta*ro #vector de las tasas de servicio
  f0<-sapply(vts,cola_finitaC,ta=15,m=n, s=1,tt=40,op=1, rep=1e4) #se obtiene toda la columna
  round(f0,2) #redondedo
  
}

#crea la tabla en un dataframe
N<-0:9 #varia el tamaño de la fila
f1<-sapply(N,simula_col) #obtiene todas las columnas de la tabla variando el tamaño de fila
ro<-seq(from=0.1, to=0.9, by=0.1) #relacion de la tasa de servicio con la de llegadas
df<-data.frame(ro,f1) #crea un data frame con los resultados
names(df)=c("ro/N",N)


## Resultados
df
#guarda los resultados en un csv
write.csv(df,file = "Resultados.csv")

#genera un grafico
ggplot(data=df,aes(y=`0`, x=`ro/N`))+
  geom_point(data=df,aes(y=`1`, x=`ro/N`), color=2)+
  geom_point(data=df,aes(y=`2`, x=`ro/N`), color=3)+
  geom_point(data=df,aes(y=`3`, x=`ro/N`), color=4)+
  geom_point(data=df,aes(y=`4`, x=`ro/N`), color=5)+
  geom_point(data=df,aes(y=`5`, x=`ro/N`), color=6)+
  geom_point(data=df,aes(y=`6`, x=`ro/N`), color=7)+
  geom_point(data=df,aes(y=`7`, x=`ro/N`), color=8)+
  geom_point(data=df,aes(y=`8`, x=`ro/N`), color=9)+
  geom_point(data=df,aes(y=`9`, x=`ro/N`), color=10)+
  geom_point()+ #tipo de grafico
  ggtitle("Ploss - Tamaño del sistema (N)")+ #title
  xlab("Relacion tiempo promedio de servicio/llegadas (ro)") +# for the x axis label
  ylab("Probabilidad de perder clientes (ploss)") # for the y axis label

#guarda el grafico
ggsave("plot.png",width = 5, height = 5)