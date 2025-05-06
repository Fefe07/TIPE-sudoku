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


dimensions= m.shape
results_size,n = dimensions

print(results_size)

coeffs = m[results_size-2]
print(coeffs)
c = n * [0]
for i in range(n) :
    c[i] = coeffs[0,i]
coeffs =c
print(coeffs)
coeffs_first_use = m[results_size-1]
c = n * [0]
for i in range(n) :
    c[i] = coeffs_first_use[0,i]
coeffs_first_use =c


diff_calculee = (results_size-2) * [42]
diff_donnee = (results_size-2) * [42]
for i in range(results_size-2) :
    diff = 0
    for j in range(n-1) :
        diff += m[i,j]*coeffs[j]
        if m[i,j] > 0.001 :
            diff += coeffs_first_use[j]
    diff_calculee[i] = diff 
    diff_donnee[i] = m[i,n-1]

identite = range(results_size-2)
plt.scatter(identite,diff_donnee)
plt.scatter(identite,diff_calculee)
plt.show()

