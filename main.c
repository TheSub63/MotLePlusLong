#include "genmot.h"

/**
  Enlever les accents                                                                 FONCTION NE MARCHE PAS
  Pouvoir trouver des mots de longueur < params                                       OK
  Nettoyer l'usage de dico                                                            WTF
  Proposer un menu permettant de saisir consonnes/voyelles jusqu'à input              OK              --> Retour en direct?
*/

int menuConsonnesVoyelles(char * lettres)
{
  int c = 0, v = 0;
  char input;
  printf("Tapez c pour une consonne, v pour une voyelle et q pour lancer l'algorithme.");
  while(scanf("%c",&input)==1)
  {
    if(input == 'c') c++;
    else if(input == 'v') v++;
    else if(input == 'q') break;
  }
  lettres = genLettresMenu(c, v);
  printf("%s", lettres);
  return c + v;
}

typedef struct
{
  char * mot;
  int longueur;
} solution;

int utiliseLettre(char * mot, char * lettres, int params, int profondeur, solution * s)
{
  int i=0, j, res = 1;
  char * temp = (char *) malloc((params-1) * sizeof(char));
  strcpy(temp, lettres);
  //printf("%s \n",lettres);
  //printf("Verif mot %s contient les lettres %s nb de lettres %d \n", mot, lettres, params);
  while(i < params && res == 1)
  {
    //printf("Lettre %c == lettre %c ?\n", mot[0], lettres[i]);
    if(mot[0] == '\0')
    {
      if(profondeur>s->longueur) 
      {
        res = 0;
        params = 0;
      } 
    }
    if(mot[0] == temp[i]) 
    {
      res = 0;
      //printf("Le mot %s contient la lettre %c \n", mot, temp[i]);
    }
    //printf("i: %d params : %d res : %d", i, params, res);
    i++;
  }
  //printf("fin boucle");
  if(res == 0)
  {
    //printf("%s \n",lettres);
    for(i=i-1; i<params-1; i++)
      temp[i] = temp[i + 1];
    //printf("%s \n",lettres);

    if(params>1)
    {
      //printf("params !=0");
      //printf("%s %s %d\n", mot+1, temp, params -1);
      res = utiliseLettre(mot + 1, temp, params - 1, profondeur + 1, s);
    }
  }
  //printf("fin récu");
  //printf("res : %d", res);
  return res; 
}

int main(int argc, char *argv[])
{
  int i;
  int params = 6, p = 0;
  char * termeini = (char *) malloc((100) * sizeof(char));
  char * mot = (char *) malloc((params) * sizeof(char));
  char ** dico = (char **) malloc (100 * sizeof(char *));
  ssize_t read;
  termeini=genLettres(params);
  //termeini = "beteab";
  //params = menuConsonnesVoyelles(termeini);
  //printf("main");
  //printf("%s\n",termeini);
  //printf("Liste de lettres : \n");
  for(i=0;i<params;i++)  
    printf("%c\n", termeini[i]);

  FILE *file  = fopen("liste_francais.txt", "r");
           
  if (file == NULL ) 
    exit(-1);

  solution motLePlusLong;
  motLePlusLong.mot = "";
  motLePlusLong.longueur = 0;

  i=0;
  while ((read = fscanf(file,"%s",mot)) != -1) {
    //printf("%s \n", mot);
    //printf("%s \n", retirerAccent(mot));
    if(!utiliseLettre(mot, termeini, params, p, &motLePlusLong))
    {
      //printf("ajout en cours");
      motLePlusLong.mot = (char *) malloc(params);
      strcpy(motLePlusLong.mot, mot);
      motLePlusLong.longueur = strlen(mot);
      //printf("ajoute %s \n", mot);
    }
    //printf("netx\n");
    i++;
  }
  printf("Resultat : \n%s \nLongueur : %d", motLePlusLong.mot, motLePlusLong.longueur);

	return(0);
}