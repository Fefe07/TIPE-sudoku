import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(threshold=1000000)

### Lit resultats.txt
f = open("db_B.txt","r")
texte = f.read()
m = np.matrix(texte)
f.close()


n,p = m.shape




######## Sélectionne les données utiles
y = np.delete(m,range(p-1),1)
m = np.delete(m,p-1,1)

n,p = m.shape



#### Résout le système
mt = np.linalg.matrix_transpose(m)
mtm = mt*m
#print(mtm)
#print(mt*y)
x = np.linalg.lstsq(mt*m,mt*y)[0]
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


cap = 5

dc_per_dd = [] 
for i in range(cap) :
    dc_per_dd.append([])
means = cap * [42]
std = cap * [42]
for i in range(n):
    dc_per_dd[int(y2[i])].append( d[i])

for i in range(cap) :
    means[i] = np.average(dc_per_dd[i])
    std[i] = np.std(dc_per_dd[i])


### Affichage

#plt.scatter(identite,d, label = "Difficulté calculée")
#plt.scatter(identite,y2, label = "Difficulté donnée")
plt.scatter(y2,d, label ="corrélation = %f" %corr[0])
plt.errorbar(range(cap), means, std, color="orange", marker = "s")
plt.xlabel("Difficulté donnée")
plt.ylabel("Difficulté calculée")
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


## Cette procéudre fait le même travail que les lignes suivantes, je l'ai découverte après
m2t =np.linalg.matrix_transpose(m2)
x2 = np.linalg.lstsq(m2t*m2,m2t*y)[0]
print("x2 = ",x2)

n,p2 = m2.shape


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



cap = 5

dc_per_dd = [] 
for i in range(cap) :
    dc_per_dd.append([])
means = cap * [42]
std = cap * [42]
for i in range(n):
    dc_per_dd[int(y2[i])].append( d[i])

for i in range(cap) :
    means[i] = np.average(dc_per_dd[i])
    std[i] = np.std(dc_per_dd[i])


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
plt.scatter(y2,d, label ="corrélation = %f" %corr[0])
plt.errorbar(range(cap), means, std, color="orange", marker = "s")
plt.xlabel("Difficulté donnée")
plt.ylabel("Difficulté calculée")
plt.title("Méthode analytique avec coeffs de première utilisation")
plt.legend(loc=2)
plt.show()



