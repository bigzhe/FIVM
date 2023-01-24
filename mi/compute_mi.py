import numpy as np
from sklearn.feature_selection import mutual_info_classif, mutual_info_regression
from numpy import genfromtxt
import pandas as pd


df = pd.read_csv("/Users/haozhezhang/Documents/dast/experiments/FIVM/examples/mi/result_toy_mi.csv") # join result computed using Postgres

mi_matrix = np.zeros(shape=[len(df.columns), len(df.columns)])

C_count = df.shape[0]

# for i in range(X.shape[1]):
for i, col in enumerate(df.columns):
  
    print(f"Computing MI for {col}...")
    
    for j, col2 in enumerate(df.columns):
        if i > j:
            continue

 
        # compute mi for each pair of columns
        for x in df[col].unique():
            C_x = df[df[col] == x].shape[0]          
            if (i == j):
                mi = 1.0 * C_x / C_count * np.log2(C_count / C_x)
                mi_matrix[i][j] += mi
                continue
            
            for y in df[col2].unique():
              # print(f"Computing MI for {col} and {col2} with values {x} and {y}...")
                C_y = df[df[col2] == y].shape[0]
                C_xy = df[(df[col] == x) & (df[col2] == y)].shape[0]

                if C_xy == 0:
                    continue
                mi_matrix[i][j] += 1.0 * C_xy / C_count * np.log2(C_count * C_xy / (C_x * C_y))
                
        mi_matrix[j][i] = mi_matrix[i][j]



np.savetxt('mi_py.csv', mi_matrix, delimiter=' ', fmt='%1.3f')
