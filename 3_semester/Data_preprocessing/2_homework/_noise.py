"""
CIMAT UNIDAD MONTERREY
MAESTRIA EN COMPUTO ESTADISTICO
TERCER SEMESTRE, MATERIA TEMAS SELECTOS DE COMPUTO
VICTOR MANUEL GOMEZ ESPINOSA
"""

from numpy import zeros, sum as sumnp
import numpy as np
from scipy.stats import mode
from sklearn.base import BaseEstimator
from sklearn.utils import check_X_y, check_array
from sklearn.model_selection import StratifiedKFold
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import NearestNeighbors, KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import   RandomizedSearchCV
from sklearn.neural_network import MLPClassifier
from sklearn.pipeline import Pipeline

class NoiseHandling(BaseEstimator):
    def __init__(self, method = 'ENN', n_neighbors = 5, n_splits = 5, 
                 filter_type = 'majority', max_iter=300,tol=0.2,random_state = None):
        self.method = method
        self.n_neighbors = n_neighbors
        self.n_splits = n_splits
        self.filter_type = filter_type
        self.random_state = random_state
        self.max_iter=max_iter
        self.tol=tol
        
    def __filtering_rule(self, y_pred, y):
        if self.filter_type == 'majority':
            y_pred_mode = mode(y_pred, axis = 1)[0].ravel()
            return y_pred_mode == y
        elif self.filter_type == 'consensus':
            y_pred_bool = y_pred == y[:, None]
            return sumnp(y_pred_bool, axis = 1) > 0
        else:
            raise ValueError('Undefined rule')
        
    def __enn_fit(self, X, y):
        nn_search = NearestNeighbors(n_neighbors = self.n_neighbors + 1)
        nn_search.fit(X)
        neigh_ind = nn_search.kneighbors(X, return_distance = False)[:, 1:]
        labels = y[neigh_ind]
        y_pred = mode(labels, axis = 1)[0].ravel()
        self.filter_ = y == y_pred
        return self
    
    def __ef_fit(self, X, y):
        skf = StratifiedKFold(n_splits = self.n_splits, shuffle = True,
                              random_state = self.random_state)
        predictions = np.empty((X.shape[0], 3), dtype='object')
        for train_idx, test_idx in skf.split(X, y):
            X_train, y_train = X[train_idx], y[train_idx]
            X_test = X[test_idx]
            
            learning_algorithms = [DecisionTreeClassifier(), \
                                  KNeighborsClassifier(), \
                                  LogisticRegression()]
            for index, model in enumerate(learning_algorithms):
                model.fit(X_train, y_train)
                predictions[test_idx, index] = model.predict(X_test)
                
        self.filter_ = self.__filtering_rule(predictions, y)
        return self
    
    def __cmtnn_fit(self, X, y):
        yc=np.random.choice(y,y.shape[0])
        
        
        param_grid = [{"hidden_layer_sizes": [(25,25),(50,50),(25,25,25)],"alpha": [0.0001,0.001,0.01,0.1],"activation": ["relu"], 'solver': ['adam'], 'max_iter': [self.max_iter]}]
            
        pipeT = Pipeline([('scaler', StandardScaler()), ('rndsearch',RandomizedSearchCV(estimator=MLPClassifier(),param_distributions=param_grid,scoring='accuracy',cv=3,return_train_score=True,n_jobs=-1))]) #pipe regresion
        yht=pipeT.fit(X, y).predict(X) #clasif True
        
        pipeC = Pipeline([('scaler', StandardScaler()), ('rndsearch',RandomizedSearchCV(estimator=MLPClassifier(),param_distributions=param_grid,scoring='accuracy',cv=3,return_train_score=True,n_jobs=-1))]) #pipe regresion
        yhc=pipeC.fit(X, yc).predict(X) #clasif False
        
        filtr=(yht!=y) & (yhc!=y)
        self.filter_ = ~filtr
        return self
    
    def __iterativeedition_fit(self, X, y):
        relabel_remove=0
        selected=y==y
        Xc=X.copy()
        yc=y.copy()
        
        
        
        iteri=0
        while (iteri<self.max_iter) and (relabel_remove<yc.shape[0]):
            iteri=iteri+1
            
            Xc=Xc[selected,:]
            yc=yc[selected]
            ycold=yc.copy()
            clases=np.unique(yc)
            sizeClases=np.sum(yc.reshape(-1,1)==clases, axis=0)
            minC=min(sizeClases)
            maxC=max(sizeClases)
            t=minC+maxC
            rate=minC/t
            if(rate>=self.tol):
                
                nn_search = NearestNeighbors(n_neighbors = self.n_neighbors + 1)
                nn_search.fit(Xc)
                neigh_ind = nn_search.kneighbors(Xc, return_distance = False)[:, 1:]
                labels = yc[neigh_ind]
                mat=yc.reshape(-1,1)!=labels
                notMatch=np.sum(mat,axis=1)>0
                if(np.sum(notMatch)>0):
                    
                    MajorityClass = mode(labels, axis = 1)[0].ravel()
                    Relabels=np.sum(MajorityClass.reshape(-1,1)==labels,axis=1)>=self.n_neighbors-1
                    if(np.sum(Relabels)>0): #relabel
                        
                        ind_relabel=(notMatch) & (Relabels)
                        yc[ind_relabel]=MajorityClass[ind_relabel]
                    #remove
                        ind_remove=(notMatch) & (~Relabels)
                        selected=~ind_remove
                relabel_remove=np.sum(ycold==yc)
            else:
                relabel_remove=1e20
            
        self.yc_ = yc   
        self.Xc_ = Xc
        return self
    
    def __hybridrepairingfilter_fit(self, X, y):
        skf = StratifiedKFold(n_splits = self.n_splits, shuffle = True,
                              random_state = self.random_state)
        predictions = np.empty((X.shape[0], 3), dtype='object')
        for train_idx, test_idx in skf.split(X, y):
            X_train, y_train = X[train_idx], y[train_idx]
            X_test = X[test_idx]
            
            learning_algorithms = [DecisionTreeClassifier(), \
                                  KNeighborsClassifier(), \
                                  LogisticRegression()]
            for index, model in enumerate(learning_algorithms):
                model.fit(X_train, y_train)
                predictions[test_idx, index] = model.predict(X_test)
                
        self.filter_type == 'majority'
        filterM=self.__filtering_rule(predictions, y)
        self.filter_type == 'consensus'
        filterC=self.__filtering_rule(predictions, y)
        notNoise=filterM & filterC
        Noise=~notNoise
        
        Xc=X[Noise]
        yc=y[Noise]
        n_samples=Xc.shape[0]
        if(n_samples<self.n_neighbors + 1 and n_samples>0 ):
            self.n_neighbors=n_samples-1
        nn_search = NearestNeighbors(n_neighbors = self.n_neighbors + 1)
        nn_search.fit(Xc)
        neigh_ind = nn_search.kneighbors(Xc, return_distance = False)[:, 1:]
        labels = yc[neigh_ind]
        mat=yc.reshape(-1,1)!=labels
        notMatch=np.sum(mat,axis=1)>0
        if(np.sum(notMatch)>0):
            MajorityClass = mode(labels, axis = 1)[0].ravel()
            Relabels=np.sum(MajorityClass.reshape(-1,1)==labels,axis=1)>=self.n_neighbors-1
            if(np.sum(Relabels)>0): #relabel
                ind_relabel=(notMatch) & (Relabels)
                yc[ind_relabel]=MajorityClass[ind_relabel]
                y[Noise]=yc
                
                #remove
                ind_remove=(notMatch) & (~Relabels)
                
                tipoStr=type(y[0])==type('str')
                if tipoStr:
                    yc[ind_remove]='nan'
                    y[Noise]=yc
                    nas=y=='nan'
                else:
                    yc[ind_remove]=-0.9999999
                    y[Noise]=yc
                    nas=y==-0.9999999
                
                selected=~nas
                X=X[selected,:]
                y=y[selected]
            
        
        self.yc_ = y   
        self.Xc_ = X
        return self
    
    
    def __filter_resample(self, X, y):
        return X[self.filter_], y[self.filter_]
            
    def __resample(self, X, y):
        X = check_array(X)
        
        if (self.method == 'ENN') or (self.method == 'EF') or (self.method == 'CMTNN'):
            return self.__filter_resample(X, y)
        elif self.method == 'IterativeEdition':
            y=self.yc_
            X=self.Xc_
            return X,y
        elif self.method == 'HybridRepairingFilter':
            y=self.yc_
            X=self.Xc_
            return X,y
        else:
            raise ValueError('Undefined method')
    
    def fit(self, X, y):
        X, y = check_X_y(X, y)
        
        #'Noise Filtering'
        if self.method == 'ENN':
            return self.__enn_fit(X, y)
        elif self.method == 'EF':
            return self.__ef_fit(X, y)
        elif self.method == 'CMTNN':
            return self.__cmtnn_fit(X, y)
        
        #'Noise Polishing'
        elif self.method == 'IterativeEdition':
            return self.__iterativeedition_fit(X, y)
        elif self.method == 'HybridRepairingFilter':
            return self.__hybridrepairingfilter_fit(X, y)
        else:
            raise ValueError('Undefined method')
            
    def fit_resample(self, X, y): 
        return self.fit(X, y).__resample(X, y)


