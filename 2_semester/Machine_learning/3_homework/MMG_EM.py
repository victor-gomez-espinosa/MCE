# -*- coding: utf-8 -*-
"""
Created on Wed Mar 18 22:27:54 2020

@author: VICTOR MANUEL GOMEZ ESPINOSA
"""

#%% LIBRERIAS
import numpy as np
from scipy import stats
#%% #cluster
def maxin(xx):
    maxi=xx==max(xx)
    maxs=np.sum(maxi)
    if maxs==1: a=xx.argmax()
    else: a=np.random.choice(np.where(xx==max(xx))[0])
    return(int(a))
#%%  mean and cov for cluster k
def parameters(X,mat,k,m):
    lxb=[]
    ls=[]
    c=0
    n,_=X.shape
    if m>=1:
        for i in range(k):
            var=i
            zer=mat[:,k]==var
            xb=np.mean(X[zer,:],0)
            s=np.cov(X[zer,:].T,bias=True)
            snans=np.sum(np.isnan(s))
            sinfs=np.sum(np.isinf(s))
            xbnans=np.sum(np.isnan(xb))
            xbinfs=np.sum(np.isinf(xb))
            u, ss, vh = np.linalg.svd(s)
            if (min(ss)<=1.0e-5) or (snans!=0 or sinfs!=0) or (xbnans!=0 or xbinfs!=0):
                c+=1
            lxb.append(xb)
            ls.append(s)
            
    else:
        for i in range(k):
            ks=np.arange(0,n)
            cc=np.random.choice(ks,1)
            xb=X[cc,:][0]
            s=np.cov(X.T,bias=True)
            snans=np.sum(np.isnan(s))
            sinfs=np.sum(np.isinf(s))
            xbnans=np.sum(np.isnan(xb))
            xbinfs=np.sum(np.isinf(xb))
            u, ss, vh = np.linalg.svd(s)
            if (min(ss)<=1.0e-5) or (snans!=0 or sinfs!=0) or (xbnans!=0 or xbinfs!=0):
                c+=1
            lxb.append(xb)
            ls.append(s)
    return(lxb,ls,c)
#%% Multivariate normal 
def gauM(x,xb,s):
    p=stats.multivariate_normal.pdf(x,mean=xb,cov=s)
    if (p<=0):
        p=0.001
    if (p>=1):
        p=0.999
    return(p)
#%% log-likelihood (ec 12.54)
def loglikel(mat_w,pim,l_xb,l_s,X_ob,k):
    n,_=X_ob.shape
    tl=0
    for i in range(n):
        lk=0
        for j in range(k):
            lk+=mat_w[i,j]*np.log(pim[j]*gauM(X_ob[i,:],l_xb[j],l_s[j]))
        tl+=lk    
    return(tl)
#%% #responsabilidades (ec 12.56)
def xik_mism(pim,l_xb,l_s,X_ob,i,k):
    l=[]
    tc=0
    for j in range(k):
        c=pim[j]*gauM(X_ob[i,:],l_xb[j],l_s[j])
        l.append(c)
        tc+=c
    vxik=np.array(l)
    vxik=vxik/tc
    return(vxik)
#%% checa que los pesos esten entre 0-1
def chekpim(pim):
    for i in range(len(pim)):
        v=pim[i]
        if(v<=0):
            v=0.001
        if(v>=1):
            v=0.999
        pim[i]=v
    return(pim)
#%% MMG
def MMG(X,k,max_iter=2000,eps=0.005/100):
    #m=0
    n,_=X.shape
    mat=np.zeros((n,k+1))
    pim=np.ones(k+1,)
    
    v=(n/k)/n
    pim=pim*v
    pim=pim[0:k] 
    pim=chekpim(pim) #pesos
    l_xb,l_s,sin=parameters(X,mat,k,0) #mu,sigma, singularidad u otro problema
    
    #m+1
    llm=0
    llm1=eps+0.01
    dif=1
    itern=0
    while ( dif>=eps and itern<=max_iter):
        llm=llm1
        #E-step
        if sin==0: #si no hay matrices singulares o nan o inf
            for i in range(n): 
                xik=xik_mism(pim,l_xb,l_s,X,i,k)
                mat[i,0:k]=xik[:] #responsabilidades
                mat[i,k]=maxin(xik) #cluster
            
            #M-step
            pim=np.mean(mat,0)[0:k]
            pim=chekpim(pim) #pesos
            l_xb,l_s,sin=parameters(X,mat,k,1) #parameters
        
            llm1=loglikel(mat,pim,l_xb,l_s,X,k) #log-likelihood
            dif=abs((llm1-llm)/llm1)
        else: #si  hay matrices singulares o nan o inf
            v=(n/k)/n
            pim=pim*v
            pim=pim[0:k]
            pim=chekpim(pim) #pesos
            l_xb,l_s,sin=parameters(X,mat,k,0) #parameters
        itern+=1
        
    centers=np.array(l_xb)
    return(mat,centers)