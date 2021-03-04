# Mot Le Plus Long

par Aymeric Laissus

#### Compréhension de l'algorithme

Pour commencer, j'ai trouvé que le fonctionnement du code de Clément GUILBERT est assez compréhensible, grâce aux nombreux commentaires.

Pour autant j'ai trouvé qu'il aurait pu être intéressant d'aller jusqu'au bout des choses en donnant notamment les résultats possibles pour les fonctions du fichier  *genmot.c* . 

Pour le reste il a bien détaillé l'objectif de chaque fonction et à quoi correspondent ses différents arguments.

#### Valgrind

J'ai directement passé le code sous Valgrind afin de repérer les fuites mémoire et autre erreurs, voici le résultat:

![valgrind](C:\Users\33604\Documents\ISIMA\AAD\MotLePlusLong\valgrind.PNG)

Voici le détail des erreurs qui sont ressorties:

- **error calling PR_SET_PTRACER, vgdb might block** : Après avoir fait des recherches sur la signification de cette erreur, j'en suis venu à la conclusion que cette erreur ne vient pas du code mais de valgrind en lui-même (et de son installation dans le système), et qu'elle n'a aucun incident sur la suite de l'éxécution de valgrind.
- **Conditionnal jump or move depends on uninitialised value(s)** : En effet, comme on peut voir ci-dessous:

![valgrind2](C:\Users\33604\Documents\ISIMA\AAD\MotLePlusLong\valgrind2.PNG)

l'appel de strcpy est effectué sur une variable *temp* qui n'est jamais initialisée.

- **LEAK SUMMARY : definitively lost : 36 bytes in 3 blocks** : Des blocs mémoire ne sont pas libérés à la fin de exécution. En demandant plus de détails avec l'attribut *--leak-check=full*, nous obtenons ceci :

  ![valgrind3](C:\Users\33604\Documents\ISIMA\AAD\MotLePlusLong\valgrind3.PNG)



#### Tests unitaires

Après avoir passé le code sous Valgrind, j'ai décidé d'effectuer quelques tests unitaires.

Pour cela j'ai utilisé la librairie Catch2, librairie de test notamment utilisée par M. YON pour les tp de C++.

Cette librairie est facile à prendre en main car elle ne consiste qu'en un fichier catch.hpp qu'il faut inclure là où on veut faire les tests.

J'ai dû reprendre le code de **genmot.c** et l'intégrer dans un fichier .cpp, mais également adapté le main du code pour en faire une fonction me permettant de le tester avec Catch2:

```c++
char * maintest(char * lettres){
    int p =0,i=0,params = strlen(lettres);
    char * termeini = lettres;
  char * mot = (char *) malloc(MAX_LEN * sizeof(char));
  ssize_t read;
  solution motLePlusLong;
  motLePlusLong.mot = (char*) "";
  motLePlusLong.longueur = 0;

  /**
    Ouverture du fichier de mots
  */
  FILE *file  = fopen("liste_francais.txt", "r");
  if (file == NULL ) 
    exit(-1);
  
  /**
    Boucle de lecture de la liste et remplissage de la solution avec le mot trouvé le plus long
  */
  while ((read = fscanf(file,"%s",mot)) != -1) {
    if(!utiliseLettre(mot, termeini, params, p, &motLePlusLong))
    {
      motLePlusLong.mot = (char *) malloc(params * sizeof(char));
      strcpy(motLePlusLong.mot, mot);
      motLePlusLong.longueur = strlen(mot);
    }
    i++;
  }
  /**
    Affichage de la solution
  */
  return(motLePlusLong.mot);
	
  /**
   * Fermeture du fichier et libération des allocations mémoires
  */
  fclose(file);
  free(mot);
  free(motLePlusLong.mot);
}
```



Et voici les différents tests :

```c++
TEST_CASE("Tests Main"){
    std::string res = maintest((char *) "azertyuiop");
    std::string val = "poireau";
    std::string res2 = maintest((char *) "a r yui p");
    std::string val2 = "pair";
    REQUIRE(res == val);
    REQUIRE(res2 == val2);
}

TEST_CASE("Tests utiliseLettres"){
    solution sol;
    sol.mot = (char *)"";
    sol.longueur = 0;
    int prof = 0;
    char * lettres = (char *) "azertyuiop";
    REQUIRE(utiliseLettre((char *) "partie", lettres, strlen(lettres), prof, &sol) == 0);
    sol.mot = (char *)"partie";
    sol.longueur = 6;
    REQUIRE(utiliseLettre((char *) "paye", lettres, strlen(lettres), prof, &sol) == 1);
    REQUIRE(utiliseLettre((char *) "poireau", lettres, strlen(lettres), prof, &sol) == 0);
}
```

Et voici le résultat de l'exécution des tests:

![tests](C:\Users\33604\Documents\ISIMA\AAD\MotLePlusLong\tests.PNG)



