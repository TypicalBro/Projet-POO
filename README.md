# Notice d'utilisation : 
## Lancement mode Graphique
### Commandes pour lancer
```
make sfml
./game_sfml data/grid.txt 200
```

### Explications

```
./game_sfml data/grid.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/grid.txt 200
            ^^^^^^^^^^^^^
chemin du fichier de la grille
```


```
./game_sfml data/grid.txt 200
                          ^^^
nombre d'iterations
```

## Lancement mode Console
### Commandes pour lancer
```
make console
./game_console data/grid.txt 200
```

### Explications

```
./game_sfml data/grid.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/grid.txt 200
            ^^^^^^^^^^^^^
chemin du fichier de la grille
```


```
./game_sfml data/grid.txt 200
                          ^^^
nombre d'iterations
```


## Lancement mode Test
### Commandes pour lancer
```
make game_test
./game_test data/seed_grid.txt data/seed_grid.txt 200
```

### Explications

```
./game_sfml data/grid.txt data/seed_grid.txt 200
  ^^^^^^^^^
Pour lancer le programme
```


```
./game_sfml data/grid.txt  data/image_grid.txt200
            ^^^^^^^^^^^^^
chemin du fichier de la grille initiale
```

```
./game_sfml data/seed_grid.txt  data/image_grid.txt 200
                                ^^^^^^^^^^^^^^^^^^^
chemin du fichier de la grille du résultat
```


```
./game_sfml data/seed_grid.txt data/image_grid.txt 200
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



