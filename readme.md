# TIPE : évaluation de la difficulté d'un sudoku
Ce dossier contient un évaluateur de grilles de sudokus.  
Il exploite séparément deux approches :
- d'une part, il évalue les techniques de résolution qu'un humain devra utiliser
- d'autre part, il calcule plusieurs critères d'évaluation pré-résolution : cette partie sert à évaluer ces critères plus que le sudoku lui-même

Ce projet a été réalisé dans le cadre des TIPE (travaux d'initiative personnelle encadrés), une initiation à la démarche de chercheur ou d'ingénieur en classes préparatoires aux grandes écoles.  

Une présentation associée à ce projet sera disponible fin mai 2025.


## Calcul des techniques humaines nécéssaires

De nombreuses fonctions implémentent des raisonnements humains pour résoudre un sudoku. Des explications de ces techniques peuvent être trouvées par exemple sur [SudokuWiki](https://www.sudokuwiki.org/).  
Elles sont coordonnées dans les fonctions solve\_notes et solve\_simple\_notes\_backtrack.  
Le solveur applique successivement les techniques humaines dans l'ordre de difficulté et revient à la première à chaque succès, de telle sorte qu'il utilise les techniques de difficulté minimale pour résoudre une grille (si tant est que les techniques lui sont données dans le bon ordre de difficulté).


## Obtention d'une difficulté

Pour obtenir une échelle de difficulté à partir de ces techniques, il faut calculer un score, souvent en coefficientant l'usage de chque technique.  
J'ai fait le choix de :  
difficulté = somme sur les techniques ( nombre d'utilisations*coeff de la techniques + coeff de première utilisation si on utilise la technique )  
Le coefficient de première utilisation est facultatif.

Pour obtenir ces coefficients, je m'appuie sur des bases de données (appelées bases_de_données_évaluées.csv et db_B.csv, lues et filtrées par lecture\_db\_diffs/B).  
J'implémente deux méthodes : 
- Une méthode analytique (dans moindres_carrés.py),
- Une méthode approchée par recuit simulé (dans calcule_coeffs.c).


## Calcul des critères visuels

L'idée est d'obtenir des critères similaires au nombre d'indices pour évaluer la difficulté, mais plus fiables.  

Lex critères envisagés sont :  
- Le nombre total de candidats (les candidats d'une case sont les chiffres qui peuvent y être placés selon les règles)
- La répartition géographique des chiffres donnés (évaluée par un écart-type)
- La répartition des valeurs des chiffres donnés (évaluée par un écart-type)

Les résultats montrent clairement que, à l'instar du nombre de chiffres donnés, ces critères ne sont pas corrélés assez fortement avec la difficulté réelle pour servir de base d'évaluation (corrélations de l'ordre de 0,2).  

Fonctions associées : assess_\*.c, main.c, print\_results\_criteria.py

## Évaluation par le problème SAT

Cette méthode repose sur la conversion préalable d'une grille de sudoku en instance du problème 9-SAT, effectué par sudoku\_to\_cnf.c.  
La formule obtenue est ensuite résolue par un algorithme de Quine.
