# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 22:27:54 2020

@author: VICTOR MANUEL GOMEZ ESPINOSA
"""

#%% LIBRERIAS
import numpy as np
#%% tercer elemento de la distancia
def ted(K,c,k):
    vt=(c==k)
    Nc=np.sum(vt)
    ind=np.where(vt==True)[0]
    kc=0
    for i in ind:
        kc+=np.sum(K[i,vt])
    return(Nc,kc,vt)
#%% distancias a cada cluster
def dist_p_c(K,c,i,k):
    n,_=K.shape
    dic=np.zeros(k,)
    for j in range(k):
        Nc,kc,vt=ted(K,c,j)
        ki=np.sum(K[i,vt])
        d=K[i,i]-(2*ki/Nc)+(kc/(Nc**2))
        dic[j]=d
    return(dic)
#%% inicia  clusters de forma aleatoria
def initM(n,k):
    mat=np.zeros((n,k+1))
    for i in range(n):
        mat[i,k]=minin(mat[i,0:k]) #cluster
    return(mat)
#%% # seleciona cluster mas cercano
def minin(xx):
    maxi=xx==min(xx)
    maxs=np.sum(maxi)
    if maxs==1: a=xx.argmin()
    else: a=np.random.choice(np.where(xx==min(xx))[0])
    return(int(a))
#%% kernels
def kernels(x,y,kernel='Gauss',alfa=1,c=0,d=2,teta=0):
    if kernel=='Gauss':
        k=np.exp(-1*(np.linalg.norm(x-y)**2)/(2*(alfa**2)))
    elif kernel=='Polynomial':
        k=((np.dot(x,y))+c)**d
    else: #Sigmoid
        k=np.tanh(c*(np.dot(x,y))+teta)
    return(k)
#%% matrix K
def Kmat(X,kernel='Gauss',alfa=1,c=0,d=2,teta=0):
    n,p=X.shape
    K=np.zeros((n,n))
    Y=X
    
    for i in range(n): #X
        for j in range(n): #Y
            k=kernels(X[i,:],Y[j,:],kernel,alfa,c,d,teta)
            K[i,j]=k
    return(K)
#%% KERNEL_KM
def KERNEL_KM(X,k=2,kernel='Gauss',alfa=1,c=0,d=2,teta=0,max_iter=2000,eps=0.005/100):
    #m=0
    n,_=X.shape
    mat=initM(n,k) #inicializa la matriz de similaridades y cluster aleatoriamente
    
    K=Kmat(X,kernel,alfa,c,d,teta) #matriz de kernel

    #m+1
    llm=0
    llm1=eps+0.01
    dif=1
    itern=0
    while ( dif>=eps and itern<=max_iter):
        llm=llm1
        for i in range(n):
            d=dist_p_c(K,mat[:,k],i,k)
            mat[i,0:k]=d[:] # similaridades
            mat[i,k]=minin(mat[i,0:k]) #cluster (minima distancia)
  
        llm1=mat[i,k] #cluster
        
        dif=np.linalg.norm(llm1-llm)/np.linalg.norm(llm1)
        itern+=1
    return(mat)