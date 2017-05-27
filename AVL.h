#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define S int
#define TAILLE_MAX 100000



struct noeud{
	S valeur;
	struct noeud* filsgauche;
	struct noeud* filsdroit;		
};

typedef struct noeud noeud;

struct arbre{
	noeud* racine;
};

typedef struct arbre arbre;
