#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon May  5 18:13:53 2025

@author: felix
"""

import matplotlib.pyplot as plt
import numpy as np

f = open("results_db_B/results_criteria.txt","r")

l = f.read()
m = np.matrix(l)
f.close()

#print(m)

dimensions= m.shape
n,p = dimensions




#n = n - 1300

#trie les tableaux
t = []
for i in range(n):
    t.append((m[i,0],m[i,1],m[i,2],m[i,3],m[i,4],m[i,5], m[i,6]))
t.sort()

# t = t[:n-200] 
# n = n-200



diff_donnee = n*[42]
diff_calculee = n * [42]
density = n*[42]
nombre_indices = n * [42]
nb_notes = n*[42]
repartition = n*[42]
repartition_valeurs = n*[42]
mix = n * [42]

for i in range(n):
    diff_donnee[i] = t[i][0]
    diff_calculee[i] = t[i][1]
    density[i] = t[i][2]
    nombre_indices[i] = t[i][3] 
    nb_notes[i] = t[i][4] /25
    repartition[i] = t[i][5] 
    repartition_valeurs[i] = t[i][6]
    mix[i] = 1.4*repartition_valeurs[i] - 1*repartition[i]  - nombre_indices[i]/14 + 6  # + nb_notes[i] /75






print("n=",n)
identite = range(n)

#plt.semilogy()
#plt.scatter(identite,diff_calculee, label="Difficulté calculée")
plt.scatter(identite, diff_donnee, s=20, label="Difficulté donnée")
#plt.scatter(identite, density,s=40, label="Densité")
#plt.scatter(identite, nombre_indices, s=40, label="Nombre d'indices")
#plt.scatter(identite, nb_notes, s=20, label="Nombre de notes/25")
#plt.scatter(identite, repartition, s=20, label="Répartition géographique")
#plt.scatter(identite, repartition_valeurs, s=20, label="Répartition des valeurs")
plt.scatter(identite, mix, s=20, label ="Mix")
plt.xlabel("Sudokus")
plt.ylabel("Difficulté(entier arbitraire) / mix(réel)")
#plt.title("Recuit simulé avec coeffs de première utilisation")
plt.legend()
plt.show()



######## Calcule la corrélation #######

ddmoy = np.average(diff_donnee)
dcmoy = np.average(diff_calculee)
densitymoy = np.average(density)
nimoy = np.average(nombre_indices)
nbnotesmoy = np.average(nb_notes)
rmoy = np.average(repartition)
rvmoy = np.average(repartition_valeurs)
mmoy = np.average(mix)

corr_01 = 0
corr_02 = 0
corr_12 = 0
corr_03 = 0
corr_04 = 0
corr_05 = 0
corr_35 = 0
corr_06 = 0
corr_07 = 0
for i in range(n) :
    corr_01 += (diff_calculee[i] - dcmoy)*(diff_donnee[i]-ddmoy) 
    corr_02 += (density[i] - densitymoy)*(diff_donnee[i]-ddmoy) 
    corr_03 += (diff_donnee[i] - ddmoy)*(nombre_indices[i]-nimoy) 
    corr_04 += (nb_notes[i] - nbnotesmoy)*(diff_donnee[i]-ddmoy) 
    corr_12 += (nombre_indices[i] - nimoy)*(diff_calculee[i]-dcmoy) 
    corr_05 += (repartition[i] - rmoy)*(diff_donnee[i]-ddmoy)
    corr_35 += (nombre_indices[i]-nimoy)*(repartition[i]-rmoy)
    corr_06 += (diff_donnee[i]-ddmoy)*(repartition_valeurs[i]-rvmoy)
    corr_07 += (diff_donnee[i]-ddmoy)*(mix[i]-mmoy)

corr_01/= (np.std(diff_donnee) * np.std(diff_calculee) * n)
corr_02/= (np.std(diff_donnee) * np.std(density) * n)
corr_03/= (np.std(diff_donnee) * np.std(nombre_indices) * n)
corr_04/= (np.std(diff_donnee) * np.std(nb_notes) * n)
corr_05/= (np.std(diff_donnee) * np.std(repartition) * n)
corr_12/= (np.std(nombre_indices) * np.std(diff_calculee) * n)
corr_35/= (np.std(repartition)*np.std(nombre_indices)*n)
corr_06/= (np.std(repartition_valeurs)*np.std(diff_donnee)*n)
corr_07/= (np.std(mix)*np.std(diff_donnee)*n)

print("corr_01 =", corr_01)
print("corr_02 =", corr_02)
print("corr_03 =", corr_03)
print("corr_04 =", corr_04)
print("corr_05 =", corr_05)
print("corr_12 =", corr_12)
print("corr_35 = ",corr_35)
print("corr_06 = ", corr_06)
print("corr_07 = ", corr_07)