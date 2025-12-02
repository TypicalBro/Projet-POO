code mermaid.live diagramme de classe 

```
 
 
 
classDiagram
    class Jeu {
        - bool mode_graphique
        - int nb_iterations
        + void charger_fichier_entree()
        + demarrer_simulation()
        + creation_fichier_sortie()
    }

    class Grille {
        - int largeur
        - int hauteur
        - map cellules
        + void initialiser(hauteur, largeur)
        + int[2]obtenir_voisins(Coordonnee)
        + void mise_a_jour()
    }

    class Cellule {
        # bool ProchainEtat
        # bool EtatCellule
        # int x
        # int y
        + est_vivante() : bool
        + void calcul_etat(bool Regle)
    }

    class EtatVivante {
        + est_vivante() : bool
    }

    class EtatMorte {
        + est_vivante() : bool
    }

    class Regle_Jeu {
        + bool Regle_1(int x,int y)
        + bool Regle_2(int x,int y)
    }

    class HUD{
        +void affichage_graphique()
        +void affichage console()
    }

    %% Relations
    Jeu --> Grille
    Jeu --> Cellule
    Cellule ..> Regle_Jeu : dépendance
    Cellule --> EtatVivante
    Cellule --> EtatMorte





```

code mermaid.live diagramme de sequence

```
sequenceDiagram
    autonumber

    participant J as Jeu
    participant G as Grille
    participant C as Cellule
    participant R as Regle_Jeu
    participant F as Fichier_Sortie

    Note over J: démarrer_simulation()

    J->>J: charger_fichier_entree()
    J->>G: initialiser(matrice_bool)

        
        loop Pour chaque cellule
            G->>C: obtenir_voisins()
            C->>R: calculer_Etat()
            R-->>C: retourne état suivant
        end
    loop Pour chaque itération
        J->>G: mise_a_jour()
        alt mode console
            J->>G: afficher_console()
        else mode graphique
            J->>G: afficher_graphique()
        end

        J->>F: creation_fichier_sortie()
        J->>F: ecrire_fichier()
    end

    J->>J: fin de simulation

```

