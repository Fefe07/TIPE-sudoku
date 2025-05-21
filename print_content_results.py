#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May  5 18:13:53 2025

@author: felix
"""

import matplotlib.pyplot as plt
import numpy as np

f = open("resultats.txt","r")

l = f.read()
m = np.matrix(l)
f.close()

#print(m)

dimensions= m.shape
n,p = dimensions

print(n)

coeffs = m[n-2]
print(coeffs)
c = p * [0]
for i in range(p) :
    c[i] = coeffs[0,i]
coeffs =c
print(coeffs)
coeffs_first_use = m[n-1]
c = p * [0]
for i in range(p) :
    c[i] = coeffs_first_use[0,i]
coeffs_first_use =c


n = n-1

diff_calculee = (n-2) * [42]
diff_donnee = (n-2) * [42]
for i in range(n-2) :
    diff = 0
    for j in range(p-1) :
        diff += m[i,j]*coeffs[j]
        if m[i,j] > 0.001 :
            diff += coeffs_first_use[j]
    diff_calculee[i] = diff 
    diff_donnee[i] = m[i,p-1]

identite = range(n-2)

#trie les tableaux
t = []
for i in range(n-2):
    t.append((diff_donnee[i],diff_calculee[i]))
t.sort()
for i in range(n-2):
    diff_calculee[i] = t[i][1]
    diff_donnee[i] = t[i][0]




#plt.semilogy()
#plt.scatter(identite,diff_calculee,s=40, label="Difficulté calculée")
#plt.scatter(identite,diff_donnee,s=40, label="Difficulté donnée")
plt.xlabel("Difficulté donnée par la base")
plt.ylabel("Difficulté calculée")
plt.scatter(diff_donnee, diff_calculee)
#plt.errorbar(dc_per_dd, means, std)
plt.ylabel("Difficulté calculée")
plt.title("Recuit simulé avec coeffs de première utilisation")
#plt.legend()
plt.show()



######## Calcule la corrélation #######

dcmoy = np.average(diff_calculee)
ddmoy = np.average(diff_donnee)
corr = 0
for i in range(n-2) :
    corr += (diff_calculee[i] - dcmoy)*(diff_donnee[i]-ddmoy) 

corr/= (np.std(diff_donnee) * np.std(diff_calculee) * (n-2))

print(corr)