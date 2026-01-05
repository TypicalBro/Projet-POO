# Notice d'utilisation : 
## Lancement mode Graphique
### Commandes pour lancer
```
make sfml
./game_sfml data/glider.txt 200
```

### Explications

```
./game_sfml data/glider.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/glider.txt 200
            ^^^^^^^^^^^^^
chemin du fichier de la grille
```


```
./game_sfml data/glider.txt 200
                          ^^^
nombre d'iterations
```

## Lancement mode Console
### Commandes pour lancer
```
make console
./game_console data/glider.txt 200
```

### Explications

```
./game_sfml data/glider.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/glider.txt 200
            ^^^^^^^^^^^^^
chemin du fichier de la grille
```


```
./game_sfml data/glider.txt 200
                          ^^^
nombre d'iterations
```


## Lancement mode Test
### Commandes pour lancer
```
make game_test
./game_test data/seed_glider.txt data/seed_glider.txt 200
```

### Explications

```
./game_sfml data/glider.txt data/seed_glider.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/glider.txt  data/image_glider.txt200
            ^^^^^^^^^^^^^
chemin du fichier de la grille initiale
```

```
./game_sfml data/seed_glider.txt  data/image_glider.txt 200
                                ^^^^^^^^^^^^^^^^^^^
chemin du fichier de la grille du résultat
```


```
./game_sfml data/seed_glider.txt data/image_glider.txt 200
                                                   ^^^
nombre d'iterations
```

## Commandes d'utilisation :
#### + --> zoom +

#### - --> zoom -

#### P --> vitesse +

#### M --> vitesse -

#### ESPACE --> Pause/Reprise

#### N --> +1 Iteration



