# -*- coding: utf-8 -*-
"""
CIMAT UNIDAD MONTERREY
MAESTRIA EN COMPUTO ESTADISTICO
TERCER SEMESTRE, MATERIA COMPUTO ESTADISTICO
VICTOR MANUEL GOMEZ ESPINOSA
"""
import numpy as np
from sklearn.utils import check_X_y
from scipy import stats
import pandas as pd


#Clase que realiza el ajuste de un modelo lineal generalizado GLM
class glm():
    
    def __init__(self, y=None, X=None, family = 'Poisson', tolm=1e-6, iterm=1000, alpha=0.05):
        self.family = family #familia
        self.y=y #variable respuesta
        self.X=X #covariables
        self.tolm=tolm #tolerancia
        self.iterm=iterm #numero maximo de iteraciones
        self.alpha=alpha
        

    
    def __Poisson_model(self,X,y): #modelo Poisson
        #inicializa variables
        y=y.reshape(-1,1)
        n,m=X.shape 
        b=np.random.randn(m, 1) *0.01 #valores iniciales de parametros
        tolera=1 #inicializa tolera
        itera=0 #inicializa itera
        
        
        
        while((tolera>self.tolm)and(itera<self.iterm)): #ajusta los parametros
            eta=X@b
            lamb=np.exp(eta) #liga canonica
            Hbk=X.T@(y-lamb)
            L=np.diag(lamb.reshape(n,))
            dhbk=-X.T@L@X
            dhbki=np.linalg.inv(dhbk)
            aa=b-dhbki@Hbk
            
    
            delta=aa-b
            b=aa
            tolera=np.linalg.norm(delta)
       
            itera+=1
        

        eta=X@b
        lamb=np.exp(eta)
        

        L=np.diag(lamb.reshape(n,))
        MF=X.T@L@X
        V=np.linalg.inv(MF)
        errstd=np.sqrt(np.diag(V)).reshape(-1,1)
        
        
        df=n-m
        upper=b+errstd*stats.t.ppf(1-self.alpha/2, df)
        lower=b-errstd*stats.t.ppf(1-self.alpha/2, df)
        conf_int=np.column_stack((lower,upper))
        
        
        self.params=np.round(b,4) #parametros del modelo
        self.bse=np.round(errstd,3) #errores estandar
        self.df_resid=df #grados de libertad residuales
        self.conf_int=np.round(conf_int,3) #intervalos de confianza
        
        
            
        
        return self
    
    def summary(self): #imprime los resultados del modelo ajustado
        
        
        d={'coef':self.params[:,0].tolist(),
           'std err':self.bse[:,0].tolist(),
           '0.025':self.conf_int[:,0].tolist(),
           '0.975':self.conf_int[:,1].tolist()}
        
        df=pd.DataFrame(d)
        return df
    
    def fit(self): #ajusta el modelo seleccionado
        X, y = check_X_y(self.X, self.y)
        if self.family == 'Poisson':
            self.__Poisson_model(X, y)
        else:
            raise ValueError('Unrecognized model')
        
        return self




#%%
