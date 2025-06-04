import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(threshold=1000000)

### Lit resultats.txt
f = open("resultats.txt","r")
texte = f.read()
m = np.matrix(texte)
f.close()


n,p = m.shape




######## Sélectionne les données utiles
m = np.delete(m,range(n-2,n),0)
y = np.delete(m,range(p-1),1)
#m = np.delete(m,p-1,1)



n,p = m.shape

# autorise un coeff constant
for i in range(n) :
    m[i,p-1] = 1



print("n =", n) 





""" Ancienne version
# Supprime les colonnes liés, de telle sorte que m soit de rang maximal
#print(m)
j = 0
for k in range(p) :
    if np.linalg.matrix_rank(np.delete(m, range(j+1,p),1)) == j+1 :
        j+=1
    else :
        print("colonne ",k," supprimée")

        m = np.delete(m,j,1)
    n,p = m.shape
#print("m = ",m)
#print("y = ",y)

n,p = m.shape



#### Résout le système
mt = np.linalg.matrix_transpose(m)
mtm = mt*m
#print(mtm)
#print(mt*y)
x = np.linalg.solve(mt*m,mt*y)
print("x=",x)
"""
mt = np.linalg.matrix_transpose(m)
x = np.linalg.lstsq(mt*m,mt*y)[0]
print("x = ", np.linalg.matrix_transpose(x))


# Calcule l'écart-type
variance = 0
d = n * [0]
for i in range(n) :
    diff = 0
    for j in range(p) :
        diff += m[i,j] * x[j,0]
    d[i] = diff
    variance += (diff - y[i])**2
variance /= n
print("variance = ",variance)
#print("ecart-type = ",np.sqrt(variance))

######## Calcule la corrélation #######

dcmoy = np.average(d)
ddmoy = np.average(y)
corr = 0
for i in range(n) :
    corr += (d[i] - dcmoy)*(y[i]-ddmoy) 

corr/= (np.std(y) * np.std(d) * n)

print("correlation = ",corr)

y2 = n*[42]
for i in range(n):
    y2[i] = y[i,0]
identite = range(n)



### Tri
t = []
for i in range(n):
    t.append((y2[i],d[i]))
t.sort()
for i in range(n):
    d[i] = t[i][1]
    y2[i] = t[i][0]

# dc_per_dd = [] 
# for i in range(10) :
#     dc_per_dd.append([])
# means = 10 * [42]
# std = 10 * [42]
# for i in range(n):
#     dc_per_dd[int(y2[i])].append( d[i])

# for i in range(10) :
#     means[i] = np.average(dc_per_dd[i])
#     std[i] = np.std(dc_per_dd[i])
    


### Affichage

# plt.scatter(identite,d, label = "Difficulté calculée")
# plt.scatter(identite,y2, label = "Difficulté donnée")
# plt.xlabel("Sudokus")
# plt.ylabel("Difficulté(réel arbitraire)")
plt.scatter(y2,d, s = 20, label = "Corrélation = %f" %(np.array(corr)[0][0]))
#plt.errorbar(range(10), means, std,  marker = "s",  color = "orange", label = "Moyennes et écarts-types")
plt.xlabel("difficulté donnée par la base")
plt.ylabel("Difficulté calculée")
plt.title("Méthode analytique")

plt.legend()

plt.show()



########## m2 prend en compte les coeffs constants ###########

m = np.delete(m,p-1,1)
n,p = np.shape(m)

#n = n+10
m2 = []
#print(m)
for i in range(n) :
    m2.append((2*p)*[0])
    for j in range(p) :
        m2[i][j] = m[i,j]
        if m[i,j] > 0.01 :
            m2[i][j+p] = 1
# transforme le tableau de tableaux en matrice (c'est pas la mme chose uurg)            
m2 = np.matrix(m2)
#n= n-10

## Cette procéudre fait le même travail que les lignes suivantes, je l'ai découverte après
m2t =np.linalg.matrix_transpose(m2)
x2 = np.linalg.lstsq(m2t*m2,m2t*y)[0]
print("x2 = ",np.linalg.matrix_transpose(x2))

n,p2 = m2.shape
""" ancienne version : 
# Supprime les colonnes liés, de telle sorte que m soit de rang maximal
j = 0


for k in range(p2) :
    if np.linalg.matrix_rank(np.delete(m2, range(j+1,p2),1)) == j+1 :
        j+=1
    else :
        print("colonne ",k," supprimée")

        m2 = np.delete(m2,j,1)
    n,p2 = m2.shape

#print(m2)
m2t = np.linalg.matrix_transpose(m2)
#print(m2t*m2)
#print(m2t*y)

#### m2^Tm2 est inversible grace au code précédent
x2 = np.linalg.solve(m2t*m2,m2t*y)
print("x2 = ",x2)

"""


cout = 0
d = n * [0]
for i in range(n) :
    diff = 0
    for j in range(p2) :
        if j < p :
            diff += m2[i,j]*x2[j]
        elif m2[i,j]>0.01 :
            diff += x2[j]
    d[i] = diff
    cout += (diff - y[i])**2
cout /= n
print("variance = ",cout)






### Tri et affichage
y2 = n*[42]
for i in range(n):
    y2[i] = y[i,0]
identite = range(n)

t = []
for i in range(n):
    t.append((y2[i],d[i]))
t.sort()
for i in range(n):
    d[i] = t[i][1]
    y2[i] = t[i][0]
    
# dc_per_dd = [] 
# for i in range(10) :
#     dc_per_dd.append([])
# means = 10 * [42]
# std = 10 * [42]
# for i in range(n-2):
#     dc_per_dd[int(y2[i])].append( d[i])

# for i in range(10) :
#     means[i] = np.average(dc_per_dd[i])
#     std[i] = np.std(dc_per_dd[i])

######## Calcule la corrélation #######

dcmoy = np.average(d)
ddmoy = np.average(y2)
corr = 0
for i in range(n) :
    corr += (d[i] - dcmoy)*(y2[i]-ddmoy) 

corr/= (np.std(y2) * np.std(d) * n)

print("correlation = ",corr)

#plt.scatter(identite,d, label = "Difficulté calculée")
#plt.scatter(identite,y2, label = "Difficulté donnée")

plt.scatter(y2,d, s = 20,  label = "Corrélation = %f" %(np.array(corr)[0][0]))
#plt.errorbar(range(10), means, std,  marker = "s",  color = "orange", label = "Moyennes et écarts-types")
plt.xlabel("Difficulté donnée par la base")
plt.ylabel("Difficulté calculée")
plt.title("Méthode analytique - coefficients de première utilisation")
plt.legend()
plt.show()


