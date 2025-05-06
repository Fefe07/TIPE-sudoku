import numpy as np
import matplotlib.pyplot as plt

np.set_printoptions(threshold=1000000)

f = open("resultats.txt","r")

texte = f.read()
print(texte)

m = np.matrix(texte)
f.close()


y = np.delete(m,[0,1,2,3,4,5,6,7,8,9,10,11,12],1)
m = np.delete(m,13,1)


print(m)
j = 0
for k in range(13) :
    b = True
    for i in range(344) :
        if abs(m[i,j])>0.001 :
            b = False
            break
    if b :
        m=np.delete(m,j,1)
    else :
        j+=1
print(m)
print(y)
mt = np.linalg.matrix_transpose(m)
mtm = mt*m
print(mtm)
print(mt*y)
x = np.linalg.solve(mt*m,mt*y)
print(x)

cout = 0
d = 30 * [0]
for i in range(30) :
    diff = 0
    for j in range(12) :
        diff += m[i,j] * x[j,0]
    d[i] = diff
    cout += (diff - y[i])**2
cout /= 344
print(cout)

y2 = 30*[42]
for i in range(30):
    y2[i] = y[i,0]
identite = range(30)
plt.scatter(identite,d)
plt.scatter(identite,y2)
plt.show()
