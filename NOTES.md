LEPINE
MORDANT
OSMANOGLU

# Commentaire général
Classe DataHolder à repenser en profondeur. Beaucoup de fonctions ressemblent encore trop à du C. Mais le résultat reste tout de même très bon, bravo à vous. (Voir les détails dans NOTES.md)

## Programmation orientée objet
### Héritage $$4.5
Bien utilisé.
### Encapsulation $$3.5
Protected utilisé correctement. Attention à cette classe DataHolder (tout est public, mais dans l'état c'est necessaire)
### Fonctions virtuelles $$4.5
Bien utilisé.
### Utilisation de références et pas de copies inutiles $$4.5

## Clarté du code
### Niveau d'abstraction cohérent (updates en cascade) $$3
DataHolder fait un peu office de fourre tout !

Factorisez plus !
```c++
for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
    delete *i;
for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
    delete *i;
for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
    delete *i;
for (std::forward_list<Particle *>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
    delete *i;
in.lists.enemies.clear();
in.lists.towers.clear();
in.lists.missiles.clear();
in.lists.buffer.clear();
in.lists.particles.clear();
```
Ce bloc est répété à plusieurs endroits ! Faites-en une fonction.
### Clarté des nommages (fonctions/variables) $$4
Noms de fonctions correctes.
### Découpage des fichiers cohérent $$3.5
Bon découpage dans l'ensemble hormis DataHolder.

Vu le nombre d'états différent (15), il aurait été judicieux de passer par un fichier différent.
Aussi, au lieu d'un pointeur de fonction, en C++ il est plus courant de créer une classe de base.

Ce qui aurait donné :
```c++
class DataHolder
{

protected:
    std::vector<StateHandler*> handlers;
};

void DataHolder::handleGameState()
{
    inputs.handleInputs();
    //...
    if (gameState < EXIT)
    {
        handlers[gameState]->Update(*this);
    }
```
Chaque state aurait d'ailleurs pu contenir certaines données qui leur étaient spécifiques.

## Fonctionnalités
### Qualité du rendu $$4.5
Toutes les fonctionnalités sont là !
### Absence de warning à la compilation $$5
OK
### Memory leaks $$5
Aucun
### Crash $$5
Pas de potentiels crashs détectés

## Présentation
### Commentaires $$2.5
Très peu de commentaires.
### Readme $$4.5
Très bon README avec screenshots
### Norme de code $$4
OK

## Bonus $$5
### Sons $$5
### Format de donnée (niveau, score) $$5
### Editeur de niveau $$5

## Git
### Qualité des messages $$3.5
Messages parfois trop concis, mais bons dans l'ensemble.
### Régularité des commits $$4
Commits réguliers

## Gestion de projet
### Utilisation des tâches GitLab $$3
Très peu utilisées.
### Bonne répartition des tâches $$3.5
Pas visible sur le dashboard, mais d'après les commit, tout le monde a participé.

## Code review (divers)