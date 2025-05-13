#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May  5 18:13:53 2025

@author: felix
"""

import matplotlib.pyplot as plt
import numpy as np

f = open("results_db_C/results_criteria.txt","r")

l = f.read()
m = np.matrix(l)
f.close()

#print(m)

dimensions= m.shape
n,p = dimensions

diff_donnee = n*[42]
diff_calculee = n * [42]
nombre_indices = n * [42]
for i in range(n):
    diff_donnee[i] = m[i,0]/30
    diff_calculee[i] = m[i,1]
    nombre_indices[i] = m[i,3]




#trie les tableaux
t = []
for i in range(n):
    t.append((diff_donnee[i],diff_calculee[i], nombre_indices[i]))
t.sort()
for i in range(n):
    diff_donnee[i] = t[i][0]
    diff_calculee[i] = t[i][1]

    nombre_indices[i] = t[i][2]

diff_calculee = diff_calculee[16:]
diff_donnee = diff_donnee[16:]
nombre_indices = nombre_indices[16:]
n = n-16




print("n=",n)
identite = range(n)

#plt.semilogy()
#plt.scatter(identite,diff_calculee, label="Difficulté calculée")
plt.scatter(identite,diff_donnee,s=20, label="Difficulté donnée")
plt.scatter(identite,nombre_indices,s=20, label="nombre d'indices")
plt.xlabel("Sudokus")
plt.ylabel("Difficulté(entier arbitraire) / nombre d'indices")
#plt.title("Recuit simulé avec coeffs de première utilisation")
plt.legend()
plt.show()



######## Calcule la corrélation #######

ddmoy = np.average(diff_donnee)
dcmoy = np.average(diff_calculee)
nimoy = np.average(nombre_indices)
corr_01 = 0
corr_02 = 0
corr_12 = 0
for i in range(n) :
    corr_01 += (diff_calculee[i] - dcmoy)*(diff_donnee[i]-ddmoy) 
    corr_02 += (diff_donnee[i] - ddmoy)*(nombre_indices[i]-nimoy) 
    corr_12 += (nombre_indices[i] - nimoy)*(diff_calculee[i]-dcmoy) 

corr_01/= (np.std(diff_donnee) * np.std(diff_calculee) * n)
corr_02/= (np.std(diff_donnee) * np.std(nombre_indices) * n)
corr_12/= (np.std(nombre_indices) * np.std(diff_calculee) * n)

print("corr_01 =", corr_01)
print("corr_02 =", corr_02)
print("corr_12 =", corr_12)