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
m = np.delete(m,[n-2,n-1],0)
y = np.delete(m,range(p-1),1)
m = np.delete(m,p-1,1)

n,p = m.shape


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
print("ecart-type = ",np.sqrt(variance))

######## Calcule la corrélation #######

dcmoy = np.average(d)
ddmoy = np.average(y)
corr = 0
for i in range(n-2) :
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




### Affichage

plt.scatter(identite,d, label = "Difficulté calculée")
plt.scatter(identite,y2, label = "Difficulté donnée")
plt.xlabel("Sudokus")
plt.ylabel("Difficulté(réel arbitraire)")
plt.title("Méthode analytique sans coeffs de première utilisation")
plt.legend()
plt.show()



########## m2 prend en compte les coeffs constants ###########
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




# Supprime les colonnes liés, de telle sorte que m soit de rang maximal
j = 0
n,p2 = m2.shape

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

plt.scatter(identite,d, label = "Difficulté calculée")
plt.scatter(identite,y2, label = "Difficulté donnée")
plt.xlabel("Sudokus")
plt.ylabel("Difficulté(réel arbitraire)")
plt.title("Méthode analytique avec coeffs de première utilisation")
plt.legend()
plt.show()


######## Calcule la corrélation #######

dcmoy = np.average(d)
ddmoy = np.average(y2)
corr = 0
for i in range(n) :
    corr += (d[i] - dcmoy)*(y2[i]-ddmoy) 

corr/= (np.std(y2) * np.std(d) * n)

print("correlation = ",corr)