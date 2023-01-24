from sklearn.preprocessing import KBinsDiscretizer

from numpy import genfromtxt, loadtxt
import numpy as np
import pandas as pd



tables = ["Census", "Inventory", "Item", "Location", "Weather"]
# these are the indexes of the attributes that are to be discretized
cont_attr_indexes = {
  "Census": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
  "Inventory": [3],
  "Item": [4],
  "Location": [2,3,4,5,6,7,8,9,10,11,12,13,14],
  "Weather": [4,5,6,7]
}

for table in tables:
    X = pd.read_csv(f'../data/retailer/{table}.tbl', delimiter = "|", header=None)
    X = X.to_numpy()
    
    X_cated = np.array(X, copy=True) # categorized data
    
    for i in cont_attr_indexes[table]:
        print(f"Discretizing {table} attribute {i}...")
        discretizer = KBinsDiscretizer(n_bins=100, encode='ordinal', strategy='uniform')
        
        X_cated[:,i] = discretizer.fit_transform(X[:,i].reshape(-1, 1)).T 

 
    np.savetxt(f'../data/retailer-mi/{table}.tbl', X_cated, delimiter='|', fmt='%d')
    print(f"Discretized {table}.")

    
    

    



