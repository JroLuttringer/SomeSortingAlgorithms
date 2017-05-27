
arbre* NouvelArbre(){
	arbre* NvArbre = malloc(sizeof(arbre));
	if(NvArbre == NULL)
		return NULL; //TODO : remplacer par check		
	NvArbre->racine = NULL;
	return NvArbre;	
}

noeud* creerNoeud(){
	noeud* NvNoeud = malloc(sizeof(arbre));
	if(NvNoeud == NULL)
		return NULL;	
	NvNoeud->valeur = 0;
	NvNoeud->filsdroit = NULL;
	NvNoeud->filsgauche = NULL;

	return NvNoeud;
}


noeud* trouverNoeud(arbre* ARechercher,int valeurRecherche){
	noeud *temp = ARechercher->racine;
	while(temp && (temp->valeur != valeurRecherche)){
		if(temp->valeur < valeurRecherche)
			temp = temp->filsdroit;
		else
			temp = temp -> filsgauche;
	}
	return temp;
}


int profondeurDepuisNoeud(noeud* recherche){
	int profondeurGauche = 0; int profondeurDroite = 0;
	if(recherche -> filsdroit != NULL) profondeurDroite = profondeurDepuisNoeud(recherche->filsdroit);
	if(recherche -> filsgauche != NULL) profondeurGauche = profondeurDepuisNoeud(recherche->filsgauche);
	
	if(profondeurGauche > profondeurDroite)
		return profondeurGauche+1;
	else
		return profondeurDroite+1;	
}

/* Equilibre d'un AVL : quatre cas possible de déséquilibre après l'ajout
 * d'un noeud : besoin d'une fonction pour rechercher le type de 
 * déséquilibrage de l'arbre*/
 
 int desequilibreDepuisNoeud(noeud* N)
 {
	 int desqD = 0;
	 int desqG = 0;
	 
	 if(N->filsgauche != NULL) desqG += desequilibreDepuisNoeud(N->filsgauche);
	 if(N->filsdroit != NULL) desqD += desequilibreDepuisNoeud(N->filsdroit);
	 
	 return desqG - desqD;
 }
 
noeud* rotationGauche(noeud* N)
{
	noeud* n1 = N;
	noeud* n2 = n1 ->filsgauche;
	n1 -> filsgauche = n2->filsdroit;
	n2->filsdroit = n1;
	return n2;
}
 
noeud* rotationDroite(noeud* N)
{
	noeud* n1 = N; noeud* n2 = n1->filsdroit;
	n1->filsdroit = n2->filsgauche;
	n2->filsgauche = n1;
	return n2;
}
 
noeud* rotationDroiteGauche(noeud* N)
{
	noeud* n1;noeud* n2;noeud* n3;
	n1 = N; n2 = n1->filsdroit; n3 = n2->filsgauche;
	
	n1->filsdroit = n3->filsgauche;
	n2->filsgauche = n3->filsdroit;
	n3->filsgauche = n1;
	n3->filsdroit = n2;
	return n3;	
}


noeud*rotationGaucheDroite(noeud* N)
{
	noeud* n1;noeud* n2;noeud* n3;
	n1 = N; n2 = n1->filsdroit; n3 = n2->filsgauche;
	
	n1->filsgauche = n3->filsdroit;
	n2->filsdroit = n3->filsgauche;
	n3->filsdroit = n2;
	n3->filsgauche = n1;
	return n3;	
}   
 
noeud* eqNoeud(noeud* N){

	if(N->filsgauche != NULL)
		eqNoeud(N->filsgauche);
	if(N->filsdroit != NULL)
		eqNoeud(N->filsdroit);
	noeud* chgNoeud;
	int desq = desequilibreDepuisNoeud(N);
	
	if( desq <= -2)
	{ //deséquilibre droit
		if(desequilibreDepuisNoeud(N->filsdroit) >=1)
			chgNoeud = rotationDroiteGauche(N);
		else
			chgNoeud = rotationDroite(N);
	}
	else if(desq >= 2) //des Gauche
	{
		if(desequilibreDepuisNoeud(N->filsgauche) <=-1)
			chgNoeud= rotationGaucheDroite(N);
		else
			chgNoeud = rotationDroiteGauche(N);
	}
	else
		chgNoeud = N;
	
	return chgNoeud;

}

void eqArbre(arbre* superPointeur){
	
	noeud* chgNoeud = NULL;
	chgNoeud = eqNoeud(superPointeur -> racine);
	if(chgNoeud != superPointeur->racine )
		superPointeur->racine = chgNoeud;
}

void ajoutValeur(int valeur,arbre* superPointeur){
	noeud* nvNoeud = creerNoeud();
	nvNoeud->valeur = valeur;
		if( (superPointeur -> racine) == NULL)
			superPointeur -> racine = nvNoeud;
		else
		{
			noeud* tmp = superPointeur->racine;
			noeud* dernierVisite ;
			while(tmp != NULL)
			{
				dernierVisite = tmp;
				if(valeur > tmp->valeur)
					tmp = tmp -> filsdroit;
				else if(valeur < tmp->valeur)
					tmp = tmp -> filsgauche;
				else{return;} //TODO : comportement si noeud déjà existant
			}
			if(valeur > dernierVisite->valeur) dernierVisite->filsdroit = nvNoeud;
			if(valeur < dernierVisite -> valeur) dernierVisite->filsgauche = nvNoeud;
		}
	eqArbre(superPointeur);	
}

int estDans(int valeur, int tab[TAILLE_MAX])
{
	int i = 0;
	for(i=0; i < TAILLE_MAX ; i++)
	{
		if(valeur == tab[i])
			return 1;
	}
	return 0;
}

static int k =0;
static int visited[TAILLE_MAX];
void pprof(noeud* racine)
{
	//~ printf("lancement\n");
	int i = 0;
	//~ int visited[TAILLE_MAX];
	for(i= 0; i <TAILLE_MAX;i++) visited[i]= -1;
	if(racine->filsgauche != NULL && !estDans(racine->filsgauche->valeur,visited)) pprof(racine->filsgauche);
	if(!estDans(racine->valeur, visited))
	{
		//~ printf("_%d _\n",racine->valeur);
		//~ printf("(%d)",k);
		visited[k] = racine->valeur;
			k++;
	}
	//printf("Etat actuel du tableau visited: \n");
	//~ for(i=0; i< TAILLE_MAX; i++)
	//~ {
		//~ //printf("%d - ",visited[i]);
	//~ }
	if(racine->filsdroit != NULL && !estDans(racine->filsdroit->valeur,visited)) pprof(racine->filsdroit);	
}



int main(){
	int i;
	int tab[TAILLE_MAX];
	srand(time(NULL));
	for(i = 0; i < TAILLE_MAX; i++)
	{
		int x = rand()%100;
		tab[i]=x;
	}

	arbre* AVL = NouvelArbre();
	for(i = 0 ; i<TAILLE_MAX; i++)
	{
		//~ printf("ajout de %d (%d)\n",tab[i],i);
		ajoutValeur(tab[i],AVL);
	}
	
	//pprof(AVL->racine);


	return 0;
}























