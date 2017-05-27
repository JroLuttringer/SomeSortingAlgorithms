#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>


#define FUSION_MIN 64
#define TAILLE_MAX 100
#define VAL_MAX 100
#define SWAG(r,s)  do{int t=r; r=s; s=t; } while(0)
#define MIN(a,b) a<b?(a):(b)

typedef struct Part{
	int debut;
	int taille;
}Part;


typedef struct partStack{
	Part* stack;
	int taille;
}*PartStack;

PartStack creer_stack(int n)
{
	PartStack ps = malloc(sizeof(PartStack));
	ps->stack = (Part*)calloc(n,sizeof(Part));
	ps->taille = 0;
	return ps;
}

Part pop_stack(PartStack ps){
	printf("Plus de runs dans la pile %d \n",ps->taille);
	Part tmp = ps->stack[ps->taille];
	ps->taille--;
	printf("Onb sort la structure de début %d et de taille %d \n",tmp.debut, tmp.taille);
	return tmp;
}


void push_stack(PartStack ps,Part p){
	ps->stack[ps->taille]= p;
	ps->taille++;
}
/*
void disp_stack(PartStack ps){
	int i;
	printf("_______________%d______________\n",ps.taille);
	for(i = 0; i < ps.taille; i ++)
	printf("Element n°%d : debute a %d et a une taille de %d \n",i,ps.stack[i].debut,ps.stack[i].taille);
}*/


int TaillePartMin(int n)
{
	int reste = 0;
	
	while (n >= FUSION_MIN)
	{
		reste |= (n & 1);  //reste = dernier bit de n
		n >>= 1; //décalage à droite de n, division par 2
	}
	
	return n + reste;
}

void merge(int arr[], Part A, Part B)
{
	int k = A.debut;
	int d = B.debut;
	int tprem=A.taille;
	int tsec=B.taille;
	
	int i ;
	int j;
	
	if(tprem < tsec)
	{
		//~ printf("LOL JE SUIS DANS LE PREMIER CAS \n");
		int L[tprem];

		//~ printf("COPIE DE LA MORT QUI TUE : %d ELEMENTS DE LA MORT QUI TUE\n",tprem);
		for(i = 0; i < tprem; i++)
			L[i] = arr[k+i];

		i = 0;
		j = d;

		while( i < tprem )//&& j < (d+tsec) )
		{
			if( L[i] > arr[j] )
			{
				arr[k] = arr[j];
				j++;
			}
			else
			{
				arr[k] = L[i];
				i++;
			}
			k++;
		} 

		//~ /* Copie du reste */
		//~ while (i < tprem)
		//~ {
			//~ arr[k] = L[i];
			//~ i++;
			//~ k++;
		//~ }
	}
	else
	{
		//~ printf("PTDR DEUXIEME CAS TROP DROL \n");
		int L[tsec];
		
		//~ printf("JE COPIE %d VALEURS \n",tsec);
		
		for (i=0; i < tsec; i++)
		{
			L[i] = arr[d+i];
			//~ printf("TROLOLOL I = %d || D = %d ======================D\n",i,d);
		}
			
		i = tsec - 1;
		j = d + i;
		k = d - 1;
		
		while (i >= 0) //&&)//k >= (d-tprem))
		{
			if (L[i] < arr[k])
			{
				arr[j] = arr[k];
				k--;
			}
			else
			{
				arr[j] = L[i];
				i--;
			}
			j--;
		}
		
		//~ while(i >= 0)
		//~ {
			//~ arr[j] = L[i];
			//~ i--;
			//~ j--;
		//~ }
	}
	
	
}
//~ 
//~ void mergeChaine(int* array, PartStack ps)
//~ {
	//~ while(ps->taille > 1){
		//~ int n = ps->taille - 1;
		//~ if(  (n >= 1 && ps->stack[n-1].taille <= ps->stack[n].taille + ps->stack[n+1].taille)
				//~ /*|| n >= 2 && ps->stack[n-2].taille <= ps->stack[n-1].taille + ps->stack[n].taille*/){
					//~ if(ps->stack[n-1].taille < ps->stack[n+1].taille)
						//~ n--;
			//~ }
			//~ else if (ps->stack[n].taille > ps->stack[n+1].taille){
				//~ break;
			//~ }
	//~ }
	//~ 
	//~ //il faut échanger n et taille -1
	//~ 
	//~ 
	//~ 
	//~ 
	//~ 
	//~ 
	//~ 
	//~ 
//~ }



int* Timsort(int tab[])
{
	int PartMin = TaillePartMin(TAILLE_MAX);
	PartStack toto = creer_stack(TAILLE_MAX/PartMin + 1);
	int i=0;
	int j,k,l;
	//Debut partitionement	
	while(i<TAILLE_MAX)
	{
		//printf("TEST DE %d \n", j +1);
		if(tab[i] <= tab[i+1])
		{ // ORDRE CROISSANT
			for (j=i; j<TAILLE_MAX && tab[j] <= tab[j+1]; j++) //incrémente j tant que tab[i] -> tab[j] trié
				;
			
			if ((j-i) < PartMin)
			{
				j += MIN(PartMin-(j-i), TAILLE_MAX-j); // on rajoute des élément si il faut pour atteindre PartMin
				for (k=i+1;k<=j;k++) //tri par insertion
				{
					l=k;
					while (l>i && tab[l-1] > tab[l])
					{
						SWAG(tab[l-1],tab[l]);
						l--;
					}
				}
			}
		}
		else //ORDRE DECROISANT
		{
			for (j=i; j<TAILLE_MAX && tab[j] > tab[j+1]; j++)
				;
			if ((j-i) < PartMin)
			{
				j += MIN(PartMin-(j-i), TAILLE_MAX-j); // on rajoute des élément si il faut pour atteindre PartMin
				for (k=i+1;k<=j;k++) //tri par insertion
				{
					l=k;
					while (l>i && tab[l-1] > tab[l])
					{
						SWAG(tab[l-1],tab[l]);
						l--;
					}
				}
			}
			else // si la partie était déjà dans l'ordre décroissant, on inverse les éléments
			{
				for(k = i,l = j ; k<=j ; k ++,l--)
				{
						SWAG(tab[k],tab[l]);
				}
			}
		}		
		// On empiple la partie
		Part temp ;
		temp.debut = i;
		temp.taille = j-i+1;
		push_stack(toto,temp);
		
				printf("Etat du stack : %d\n ", toto->taille);

		i=j+1; //on se décale pour la suite
		
		Part tempZ;
		Part tempX;
		Part tempY;
		Part tempFusion;
		
		while(toto->taille > 2)
		{
			printf("Dans la boucle avec taille de %d \n", toto->taille);
			int echange ;
			tempZ = pop_stack(toto);
			tempY = pop_stack(toto);
			tempX = pop_stack(toto);
			if( (tempX.taille <= tempY.taille + tempZ.taille) ) 
			{				
				if( MIN(tempX.taille,tempZ.taille) == tempX.taille )
					echange = 0;
				else
					echange = 1;
			}
			else if(tempY.taille > tempZ.taille)
			{
				push_stack(toto,tempX);
				push_stack(toto,tempY);
				push_stack(toto,tempZ);
				break;
			}
			if(echange)
			{
				merge(tab,tempZ,tempY);						
				tempFusion.taille = tempY.taille + tempZ.taille;
				tempFusion.debut = MIN(tempY.debut ,tempZ.debut);					
				push_stack(toto,tempX);
				push_stack(toto,tempFusion);	
			}
			if(!echange)
			{
				merge(tab,tempY,tempX);
				tempFusion.taille = tempY.taille + tempX.taille;
				tempFusion.debut = MIN(tempX.debut,tempY.debut);					
				push_stack(toto,tempFusion);
				push_stack(toto,tempZ);		
			}	
		
		}
		
	}//FIN PARTITIONEMENT
	

	printf("Nombre de runs ; %d \n", toto -> taille);
	
	while(toto->taille > 1)
	{
		Part tempA = pop_stack(toto);
		Part tempB = pop_stack(toto);
		printf("============ %d\n",toto->taille);
		merge(tab,tempA,tempB);
		printf("============ %d\n",toto->taille);
		Part tempFusion;
		tempFusion.taille = tempA.taille + tempB.taille;
		tempFusion.debut = MIN(tempA.debut,tempB.debut);
		printf("============ %d\n",toto->taille);					
		push_stack(toto,tempFusion);		
	}
	
		printf("Nombre de runs ; %d \n", toto -> taille);

	return tab;
}



int main()
{
	srand(time(NULL));
	int* tab = (int*)calloc(TAILLE_MAX,sizeof(int));
	int i;
	
	for (i=0;i<TAILLE_MAX;i++)
	{
		//~ if(i >=500 && i < 700)
			//~ tab[i] = i;
		//~ else
			tab[i] = rand()%VAL_MAX;
	}
	
	
	//~ for (i=0;i<100;i++)
	//~ {
		//~ 
		//~ printf(" %d |",tab[i]);
	//~ }
	tab=Timsort(tab);
	
	for (i=0;i<TAILLE_MAX;i++)
	{
		printf(" %d |",tab[i]);
	}
	printf("\n");
	
	free(tab);
	
	return 0;
}
