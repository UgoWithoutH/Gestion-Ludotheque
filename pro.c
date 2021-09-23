#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"pro.h"

//auteur : DEBUSSY Lucas
//fonction : lireUnJeu
//paramètre : FILE*fe : le flux du fichier 
//retour : retourne un Jeux
//variable : - Jeux jeu : contenir les information d'un jeu du fichier	
// 	     - taille : contenir la taille du nom du jeu lu précédement par le fgets		
//objectif : lire toutes les informations correspondant à un Jeux

Jeux lireUnJeu (FILE*fe){
Jeux jeu; 
int taille;

	fscanf(fe,"%s%*c",jeu.idJeux);
	fgets(jeu.nom,32,fe);
	taille=strlen(jeu.nom);
	if(jeu.nom[taille-1]=='\n');
		jeu.nom[taille-1]='\0';
	fscanf(fe,"%s %d%*c",jeu.type,&jeu.nb);

return jeu;
}


//auteur : DEBUSSY Lucas
//fonction : lireUnAdherent
//paramètre : FILE*fe : le flux du fichier 
//retour : retourne un Adherent
//variable : - Adherent adh : contenir les information d'un Adherent du fichier	
// 	     - taille : contenir la taille du nom puis du prénom de l'adhérent lu précédement par les fgets		
//objectif : lire toutes les informations correspondant à un adhérent

Adherent lireUnAdherent (FILE*fe){
Adherent adh; 
int taille;

	fscanf(fe,"%s %s%*c",adh.idAdherent,adh.civilite);
	fgets(adh.nom,32,fe);
	taille=strlen(adh.nom);
	if(adh.nom[taille-1]=='\n');
		adh.nom[taille-1]='\0';

	fgets(adh.prenom,32,fe);
	taille=strlen(adh.prenom);
	if(adh.prenom[taille-1]=='\n');
		adh.prenom[taille-1]='\0';

	fscanf(fe,"%d/%d/%d",&adh.dateInscri.jour,&adh.dateInscri.mois,&adh.dateInscri.annee);
	

return adh;
}


//auteur : DEBUSSY Lucas
//fonction : lireUnEmprunt
//paramètre : FILE*fe : le flux du fichier 
//retour : retourne un Emprunt
//variable : - Emprunt emp : contenir les information d'un Emprunt du fichier		
//objectif : lire toutes les informations correspondant à un Emprunt

Emprunt lireUnEmprunt (FILE*fe){
Emprunt emp;

	fscanf(fe,"%s %s %s %d/%d/%d%*c",emp.idEmprunt,emp.idAdherent,emp.idJeux,&emp.dateEmp.jour,
	&emp.dateEmp.mois,&emp.dateEmp.annee);
	
return emp;
}


//auteur : DEBUSSY Lucas
//fonction : lireUneReservation
//paramètre : FILE*fe : le flux du fichier 
//retour : retourne un Maillon
//variable : - Maillon res : contenir les information d'une Reservation du fichier		
//objectif : lire toutes les informations correspondant à une Reservation

Maillon lireUneReservation(FILE*fe){
Maillon res;

	fscanf(fe,"%s %s %s %d/%d/%d",res.idResa,res.idAdherent,res.idJeux,&res.dateRes.jour,&res.dateRes.mois,&res.dateRes.annee);

return res;
}


//auteur : DEBUSSY Lucas - VIGNON Ugo
//fonction : chargementJeux
//paramètre : -int *tlog : pointeur sur la taille logique du tableau des jeux
//	      -int *tmax : pointeur sur la taille physique du tableau des jeux
//retour : retourne le tableau des jeux ou NULL d'il y a eu un problème
//variable : - FILE*fe : contenir le flux de l'ouverture du fichier des Jeux	
// 	     - Jeux jeu : contenir un jeu retourné par la fonction "lireUnJeu"
//	     - Jeux **tab : tableau de pointeur sur strcuture Jeux qui va contenir les jeux
//	     - Jeux **aux : tableau de pointeur servant pour réallouer le tableau des jeux dans le cas du taille logique égale à la taille maximale	
//objectif : charger le tableau des jeux à partir du fichier des jeux

 Jeux** chargementJeux (int *tlog,int *tmax){
 FILE*fe;
 Jeux jeu, **tab,**aux;


	*tlog=0;
	*tmax=5;
	 fe=fopen("jeux.txt","r");
	 if (fe==NULL){
		 printf("problème ouverture fichier\n");
		 return NULL;
	 }
	tab=(Jeux**)malloc(*tmax*sizeof(Jeux*));
	 jeu=lireUnJeu(fe);
	 while(!feof(fe)){
		 if(*tlog==*tmax){
			*tmax=*tmax+5;
			aux=(Jeux**)realloc(tab,*tmax*sizeof(Jeux*));
			if(aux == NULL){
				printf("problème de réallocation mémoire\n");
				fclose(fe);
				return NULL;
			}
			tab=aux;
		 }
		 tab[*tlog]=(Jeux*)malloc(sizeof(Jeux));
		 if(tab[*tlog]==NULL){
			 printf("problème allocation mémoire\n");
			 fclose(fe);
			 return NULL;
		 }
		 *tab[*tlog]=jeu;
		 (*tlog)++;
		 jeu=lireUnJeu(fe);
	 }
	 fclose(fe);
return tab;
}


//auteur : DEBUSSY Lucas - VIGNON Ugo
//fonction : chargementAdherents
//paramètre : -int *tlog : pointeur sur la taille logique du tableau des adhérents
//	      -int *tmax : pointeur sur la taille physique du tableau des adhérents
//retour : retourne le tableau des adhérents ou NULL d'il y a eu un problème
//variable : - FILE*fe : contenir le flux de l'ouverture du fichier des Adherents	
// 	     - Adherent **tab : tableau de pointeur sur structure Adherent qui va contenir les adhérents
//	     - int i : indice pour boucler dans la boucle for	
//objectif : charger le tableau des adhérents à partir du fichier des adhérents

Adherent** chargementAdherents (int *tlog,int *tmax){
FILE*fe;
Adherent **tab;
int i;

	
	fe=fopen("adherents.txt","r");
	if (fe==NULL){
		printf("problème ouverture fichier\n");
		return NULL;
	}
	fscanf(fe,"%d%*c",tlog);
	*tmax=*tlog;
	tab=(Adherent**)malloc(*tlog*sizeof(Adherent*));
	if(tab == NULL){
		printf("problème allocation mémoire\n");
		fclose(fe);
		return NULL;
	}
	
	
	for(i=0;i<*tlog;i++){
		tab[i]=(Adherent*)malloc(sizeof(Adherent));
		if(tab[i]==NULL){
			printf("problème allocation mémoire\n");
			fclose(fe);
			return NULL;
		}
		*tab[i]=lireUnAdherent(fe);
	}

	fclose(fe);
return tab;
}


//auteur : DEBUSSY Lucas
//fonction : chargementEmprunts
//paramètre : -Emprunt *tabEmprunts : tableau de structure Emprunt
//	      -int *tlog : pointeur sur la taille logique du tableau des emprunts
//	      -int *tmax : pointeur sur la taille physique du tableau des emprunts
//retour : retourne le tableau des emprunts
//variable : - FILE*fe : contenir le flux de l'ouverture du fichier des Adherents	
// 	     - Emprunt emp : contenir un emprunt retourné par la fonction "lireUnEmprunt"
//	     - int i : indice pour boucler dans la boucle for	
//objectif : charger le tableau des emprunts à partir du fichier des emprunts

Emprunt* chargementEmprunts (Emprunt *tabEmprunts,int *tlog,int *tmax){
FILE*fe;
Emprunt emp;
int i;

	fe=fopen("emprunts.txt","r");
	if (fe==NULL){
		printf("problème allocation mémoire\n");
		*tlog=-1;
		return NULL;
	}
	fscanf(fe,"%d%*c",tlog);
	*tmax=*tlog;
	tabEmprunts=(Emprunt*)malloc(*tlog*sizeof(Emprunt));
	if(tabEmprunts==NULL){
			printf("problème allocation mémoire\n");
			fclose(fe);
			*tlog=-1;
			return NULL;
	}
	for(i=0;i<*tlog;i++){
		emp=lireUnEmprunt(fe);
		tabEmprunts[i]=emp;
		}
	fclose(fe);
return tabEmprunts;
}


//auteur : DEBUSSY Lucas
//fonction : listeVide
//paramètre : (aucun)
//retour : retourne une liste NULL
//variable : (aucune)
//objectif : retourner NULL pour initialiser la liste des réservations à NULL

Reservation listeVide(void){

return NULL;
}


//auteur : DEBUSSY Lucas - VIGNON Ugo
//fonction : InsertionEnTete
//paramètre : -Reservation l : liste des réservations
//	      -Maillon res : Maillon contenant les information d'une réservation
//retour : retourne la liste actualisée
//variable : - Maillon*x: contenir la liste actualisée	
//objectif : insérer une réservation de type Maillon en tête de liste

Reservation InsertionEnTete (Reservation l,Maillon res){
Maillon*x;

	x=(Maillon*)malloc(sizeof(Maillon));
	if(x==NULL){
		printf("problème allocation mémoire\n");
		exit(1);
	}
	strcpy(x->idResa,res.idResa);
	strcpy(x->idAdherent,res.idAdherent);
	strcpy(x->idJeux,res.idJeux);
	x->dateRes=res.dateRes;
	x->suiv=l;
return x;
}


//auteur : DEBUSSY Lucas
//fonction : insererTrie
//paramètre : -Reservation l : liste des réservations
//	      -Maillon res : Maillon contenant les information d'une réservation
//retour : retourne la liste actualisée
//variable : (aucune)
//objectif : insérer une réservation de type Maillon dans la liste triée par odre croissant des idResa

Reservation insererTrie (Reservation l,Maillon res){
	
	if(l==NULL) 
		return InsertionEnTete(l,res);
	
	else if (strcmp(res.idResa,l->idResa)<0)
		return InsertionEnTete(l,res);	

	l->suiv=insererTrie(l->suiv,res);
return l;
}


//auteur : DEBUSSY Lucas
//fonction : chargementReservation
//paramètre : - Reservation l : liste des réservations
//retour : retourne la liste des réservations 
//variable : - FILE*fe : contenir le flux de l'ouverture du fichier des réservations	
// 	     - Maillon res : contenir une réservation retournée par la fonction "lireUneReservation"	
//objectif : charger la liste des réservations triée par odre croissant des idResa à partir du fichier des réservations

Reservation chargementReservation(Reservation l){
FILE*fe;
Maillon res;

	l=listeVide();

	fe=fopen("reservations.txt","r");
	if(fe==NULL){
		printf("problème ouverture fichier\n");
		return NULL;
	}
	res=lireUneReservation(fe);
	while(!feof(fe)){
		l=insererTrie(l,res);
		res=lireUneReservation(fe);
	}
	fclose(fe);
return l;
}



//auteur : DEBUSSY Lucas
//fonction : triBulle
//paramètre : - Jeux *tab[] : tableau de pointeurs sur stucture Jeux
//            - int tlog : taille logique du tableau des jeux
//retour : (aucun)
//variable : - int i : indice pour boucler dans la boucle for	
// 	     - int cpt : compteur pour savoir si le tableau est déjà trié
// 	     - Jeux *val : pointeur sur jeu permettant de permuter des jeux de case 
//objectif : trier par type de Jeux

void triBulle(Jeux *tab[],int tlog){
int i,cpt=0;
Jeux *val;

	if(tlog == 0 || tlog == 1) return ;

	for(i=0;i+1<tlog;i++){
		if(strcmp(tab[i]->type,tab[i+1]->type)>0){
			val=tab[i];
			tab[i]=tab[i+1];
			tab[i+1]=val;	
			cpt++;
		}
	}
	if(cpt!=0)
		triBulle(tab,tlog-1);


}


//auteur : VIGNON Ugo
//fonction : triBulle2
//paramètre : - Jeux *tab[] : tableau de pointeurs sur stucture Jeux
//            - int tlog : taille logique du tableau des jeux
//	      - int index : index du tableau à partir duquel le tri doit commencer 
//retour : (aucun)
//variable : - int i : indice pour boucler dans la boucle for	
// 	     - int cpt : compteur pour savoir si le tableau est déjà trié
// 	     - Jeux *val : pointeur sur jeu permettant de permuter des jeux de case 
//objectif : trier par nom de jeu

void triBulle2(Jeux *tab[],int tlog,int index){
int i,cpt=0;
Jeux *val;

	if(tlog == 0 || tlog == 1) return ;

	for(i=index;i+1<tlog;i++){
		if(strcmp(tab[i]->nom,tab[i+1]->nom)>0){
			val=tab[i];
			tab[i]=tab[i+1];
			tab[i+1]=val;	
			cpt++;
		}
	}
	if(cpt!=0)
		triBulle2(tab,tlog-1,index);


}


//auteur : DEBUSSY Lucas - VIGNON Ugo
//fonction : triJeux
//paramètre : - Jeux *tab[] : tableau de pointeurs sur stucture Jeux
//            - int tlog : taille logique du tableau des jeux
//retour : (aucun)
//variable : - int index : contenir un indice du tableau à partir duquel le tableau devra être trié	
// 	     - int index2 : contenir un indice du tableau à partir duquel le tableau devra arrêté d'être trié	
// 	     - int i : indice pour boucler dans la boucle for	
// 	     - char type : contenir le type d'un jeu
//objectif : trier par type de Jeux, puis par ordre alphabétique de leur nom le tableau de jeux

void triJeux(Jeux *tab[],int tlog){
int index=0,index2,i;
char type[12];

triBulle(tab,tlog);
strcpy(type,tab[0]->type);
	for(i=0;i<tlog;i++){
		
		if(strcmp(tab[i]->type,type)!=0){
			index2=i;
			triBulle2(tab,index2,index);
			index=i;
			strcpy(type,tab[i]->type);			
		}
	}
}


//auteur : DEBUSSY Lucas
//fonction : affichageJeux
//paramètre : - Jeux *tab[] : tableau de pointeurs sur structure Jeux
//            - int tlog : taille logique du tableau des jeux
//retour : (aucun)
//variable : - i : indice pour boucler dans la boucle for
//objectif : afficher le tableau des jeux

void affichageJeux(Jeux *tab[], int tlog){
int i;
	printf("\nidJeux // Nom du jeu // type // nb exemplaires\n\n");
	for(i=0;i<tlog;i++){
		printf("%s '%s' %s %d\n",tab[i]->idJeux,tab[i]->nom,tab[i]->type,tab[i]->nb);
	}
printf("\n\n\n");
}


//auteur : VIGNON Ugo
//fonction : affichageAdherent [BONUS]
//paramètre : - Adherent *tab[] : tableau de pointeurs sur structure Adherent
//            - int tlog : taille logique du tableau des adhérents
//retour : (aucun)
//variable : - i : indice pour boucler dans la boucle for
//objectif : afficher le tableau des adhérents

void affichageAdherent(Adherent *tab[],int tlog){
int i;
	printf("\nidAdherent // Civilité // Nom prénom // Date d'inscription\n\n");
	for(i=0;i<tlog;i++){
		printf("%s %s '%s %s'  %d/%d/%d\n",tab[i]->idAdherent,tab[i]->civilite,tab[i]->nom,tab[i]->prenom,tab[i]->dateInscri.jour,tab[i]->dateInscri.mois,tab[i]->dateInscri.annee);
	}
printf("\n\n\n");
}


//auteur : DEPORTE Jeremy
//fonction : rechercheIdJeu
//paramètres : - Char* id : id du jeu à rechercher  
//             - Jeux** tab : tableau de pointeurs sur structure Jeux
//             - int tlogJeux : taille logique du tableau des jeux
//retour : Retourne le rang de l'id recherché 
//variables : int i : Entier utilisé pour la boucle for
//objectif : rechercher la position du jeu possédant l'id du jeu renseigné en paramètre

int rechercheIdJeu(char* id, Jeux** tab, int tlogJeux){
    int i;
    for(i=0;i<tlogJeux;i++){
        if(strcmp(id,tab[i]->idJeux)==0)
            return i;     
    }
    return -1;
}


//auteur : DEPORTE Jeremy
//fonction : affichageEmprunts
//paramètre : - Emprunt tab[] : tableau de structure Emprunt
//            - Jeux* tabJeux[] : tableau de pointeurs sur structure Jeux		
//            - Adherent* tabAdher[] : tableau de pointeurs sur structure Adherent
//            - int tlogEmprunt : taille logique du tableau des emprunts
//            - int tlogJeux : taille logique du tableau des jeux
//            - int tlogAdher : taille logique du tableau des adhérents
//retour : (aucun)
//variable : - int i : indice pour boucler dans la boucle for
//	     - int posJeu : position du jeu cherché
//	     - Adherent adh : adhérent retourné par la recherche
//objectif : afficher les emprunts en cours en mentionnant : le nom du jeu, l’identité de l’emprunteur ainsi que la date de l’emprunt  

void affichageEmprunts(Emprunt tabEmp[],Jeux* tabJeux[],Adherent* tabAdher[], int tlogEmprunt, int tlogJeux, int tlogAdher){
int i,posJeu;
Adherent adh;
	printf("\nNom jeu // Identité emprunteur // Date de l'emprunt\n\n");
    for(i=0;i<tlogEmprunt;i++){
        posJeu=rechercheIdJeu(tabEmp[i].idJeux, tabJeux, tlogJeux);
        adh=rechercheIdAdherent(tabAdher, tlogAdher,tabEmp[i].idAdherent);
        printf("'%s' '%s %s' %d/%d/%d \n",tabJeux[posJeu]->nom,adh.nom,adh.prenom,tabEmp[i].dateEmp.jour,tabEmp[i].dateEmp.mois,tabEmp[i].dateEmp.annee);
    }
printf("\n\n\n");
}


//auteur : VIGNON Ugo
//fonction : afficheReservation [BONUS]
//paramètre : - Reservation l : liste des réservations
//retour : (aucun)
//variable : (aucune)
//objectif : afficher la liste des réservations

void afficheReservation(Reservation l){
	if(l==NULL)return;
	printf("%s %s %s %d/%d/%d\n",l->idResa,l->idAdherent,l->idJeux,l->dateRes.jour,l->dateRes.mois,l->dateRes.annee);
	afficheReservation(l->suiv);
}


//auteur : DEPORTE Jeremy - VIGNON Ugo
//fonction : afficheJeuDonne
//paramètre : - Reservation l : liste des réservations
//	      - char idJeux[] : id du jeu pour lequel les réservations doivent être affichés
//retour : (aucun)
//variable : (aucune)
//objectif : afficher les réservations correspondant à l'id du jeu donné en paramètre

void afficheJeuDonne(Reservation l,char idJeux[]){

	if(l == NULL) return;

	if(strcmp(l->idJeux,idJeux)==0)
		printf("%s %s %s %d/%d/%d\n",l->idResa,l->idAdherent,l->idJeux,l->dateRes.jour,l->dateRes.mois,l->dateRes.annee);
	afficheJeuDonne(l->suiv,idJeux);
}


//auteur : DEPORTE Jeremy - VIGNON Ugo
//fonction : saisieJeuDonne
//paramètre : - Reservation l : liste des réservations
//	      - Jeux *tabJeux[] : tableau de pointeur sur strcture Jeux
//	      - int tlogJeux : taille logique du tableau des jeux
//retour : (aucun)
//variable : - int posJeu : position du jeu recherché
//    	     - int taille : varaiable pour récupérer la taille suite à un fgets
//           - int trouve : variable pour savoir si le jeu a été trouvé
//	     - char jeuRech[32] : variable contenant le jeu suite à la saisie de l'utilisateur
//objectif : afficher les réservation pour un jeu donné

void saisieJeuDonne (Reservation l,Jeux *tabJeux[],int tlogJeux){
int posJeu,taille,trouve;
char jeuRech[32];

	printf("nom du jeu recherché : ");
	fgets(jeuRech,32,stdin);
	taille=strlen(jeuRech);
	if(jeuRech[taille-1]=='\n')
		jeuRech[taille-1]='\0';

	posJeu=rechercheJeu(tabJeux,tlogJeux,jeuRech,&trouve);
	while(trouve==0){
		printf("\n\t\tLe jeu recherché n'a pas été trouvé\n\n");
		printf("nom du jeu recherché : ");
		fgets(jeuRech,32,stdin);
		taille=strlen(jeuRech);
		if(jeuRech[taille-1]=='\n')
			jeuRech[taille-1]='\0';
		posJeu=rechercheJeu(tabJeux,tlogJeux,jeuRech,&trouve);
	}
	printf("\n\n");
	afficheJeuDonne(l,tabJeux[posJeu]->idJeux);
	printf("\n\n");
}


//auteur : VIGNON Ugo
//fonction : rechercheAdherent
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur une structure Adherent
//	      - char nom[] : nom de l'adhérent recherché
//	      - char prenom[] : prenom  de l'adhérent recherché
//	      - int tlogAdherent : taille logique du tableau de pointeurs des adhérents
//	      - int *trouve : pointeur sur une variable indiquant si l'adhérent a été trouvé
//retour : retourne la position de l'adhérent recherché ou -1 s'il n'a pas été trouvé
//variable : - int pos : contenir la position de l'adhérent recherché	
//objectif : rechercher si un adhérent est déjà présent dans le tableau des adhérents et retourner sa position si c'est le cas

int rechercheAdherent(Adherent *tabAdherents[],char nom[],char prenom[],int tlogAdherent,int *trouve){
int pos;
	
	
	for(pos=0;pos<tlogAdherent;pos++){
		if(strcmp(tabAdherents[pos]->nom,nom) == 0 && strcmp(tabAdherents[pos]->prenom,prenom) == 0){
			*trouve=1;
			return pos;
		}		
	}

	*trouve=0;
return -1;
}


//auteur : VIGNON Ugo
//fonction : creationAdherent
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur une structure Adherent
//	      - int *tlogAdherents : pointeur sur une variable contenant la taille logique du tableau des adhérents
//	      - char nom[] : nom de l'adhérent précédemment renseigné
//	      - char prenom[] : prénom de l'adhérent précédemment renseigné
//retour : 0 en cas de succès et -1 en cas d'échec
//variable : - Adherent adh : variable contenant la saisie de l'adhérent destiné à être créé
//	     - int taille : contenir la taille de l'identifiant de l'adhérent
//objectif : créer un adhérent et l'insérer dans le tableau des adhérents dans le cas d'une taille logique inférieure à la taille physique

int creationAdherent(Adherent *tabAdherents[],int *tlogAdherents,char nom[],char prenom[]){
Adherent adh;
int taille;
	
	printf("civlité (Mr/Mme) : ");
	scanf("%s%*c",adh.civilite);
	printf("\nSaisissez la date d'aujourd'hui \n");
	printf("\tjour (en nombre) : ");
	scanf("%d%*c",&adh.dateInscri.jour);
	printf("\tmois (en nombre) : ");
	scanf("%d%*c",&adh.dateInscri.mois);
	printf("\tannée (4 chiffres) : ");
	scanf("%d%*c",&adh.dateInscri.annee);

	strcpy(adh.nom,nom);
	strcpy(adh.prenom,prenom);
	strcpy(adh.idAdherent,tabAdherents[*tlogAdherents-1]->idAdherent);

	taille=strlen(adh.idAdherent);
	if(adh.idAdherent[taille-1]==57){
		adh.idAdherent[taille-1]=48;
		if(adh.idAdherent[taille-2]==57){
			adh.idAdherent[taille-2]=48;
			if(adh.idAdherent[taille-3]==57){
				adh.idAdherent[taille-3]=48;
				if(adh.idAdherent[taille-4]==57){
					printf("nombre maximal d'Adhérent atteint mise à jour nécessaire\n");
					return -1;
				}
				else 
					adh.idAdherent[taille-4]+=1;
			}
			else
				adh.idAdherent[taille-3]+=1;
		}
		else
			adh.idAdherent[taille-2]+=1;
	}		
	else
		adh.idAdherent[taille-1]+=1;

	printf("\n\n\t\tRécapitulatif : %s %s-%s %s\t%d/%d/%d\n\n",adh.idAdherent,adh.civilite,adh.nom,adh.prenom,adh.dateInscri.jour,adh.dateInscri.mois,adh.dateInscri.annee);

	tabAdherents[*tlogAdherents]=(Adherent*)malloc(sizeof(Adherent));
	*tabAdherents[*tlogAdherents]=adh;
	(*tlogAdherents)++;

return 0;
}


//auteur : VIGNON Ugo
//fonction : saisieNomPrenom
//paramètre : - char nom[] : tableau destiné à prendre le nom de l'adhérent saisie
//	      - char prenom[] : tableau destiné à prendre le prénom de l'adhérent saisie
//retour : (aucun)
//variable : - int taille : contenir la taille du nom puis du prénom saisie et récupérer avec un fgets
//objectif : saisir le nom et prénom d'un adhérent

void saisieNomPrenom(char nom[],char prenom[]){
int taille;
	printf("Nom : ");
	fgets(nom,32,stdin);
	taille=strlen(nom);
	if(nom[taille-1]=='\n')
		nom[taille-1]='\0';

	printf("Prénom : ");
	fgets(prenom,32,stdin);
	taille=strlen(prenom);
	if(prenom[taille-1]=='\n')
		prenom[taille-1]='\0';

}


//auteur : VIGNON Ugo
//fonction : saisieAdherent
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur une structure Adherent
//	      - int *tlogAdherents : pointeur sur une variable contenant la taille logique du tableau des adhérents
//	      - int *posAdherent : pointeur sur une variable destinée à contenir la position de l'adhérent
//	      - int *tmax : pointeur sur la taille physique du tableau des adhérents 
//retour : 0 en cas de succès et -1 en cas d'échec
//variable : - int trouve : contenir 0 ou 1 en fonction de la recherche de l'adhérent
//	     - int retour : contenir 0 ou -1 en fonction de la création de l'adhérent
//objectif : afficher un message de succès ou d'erreur (permet d'alléger la fonction test pour la rendre plus lisible)

Adherent** saisieAdherent(Adherent *tabAdherents[],int *tlogAdherents,int *posAdherent,int *tmax){
char nom[32],prenom[32];
int trouve,retour;
Adherent **aux;

	saisieNomPrenom(nom,prenom);
	
	*posAdherent=rechercheAdherent(tabAdherents,nom,prenom,*tlogAdherents,&trouve);
	if(trouve == 0){
		if(*tlogAdherents==*tmax){
			*tmax=*tmax+5;
			aux=(Adherent**)realloc(tabAdherents,*tmax*sizeof(Adherent*));
			if(aux==NULL){
				printf("problème réallocation mémoire\n");
				exit(1);
			}
			tabAdherents=aux;
		}

		retour=creationAdherent(tabAdherents,tlogAdherents,nom,prenom);
		if (retour == 0){
			printf("\t\tcréation de l'adhérent terminée !\n\n");
			*posAdherent=*tlogAdherents-1;
			return tabAdherents;
		}
		else{
			printf("\t\tcréation de l'adhérent échouée !\n");
			*posAdherent=-1;
			exit(1);
		}
	}
return tabAdherents;
}


//auteur : VIGNON Ugo
//fonction : rechercheJeu
//paramètre : - Jeux *tabJeux[] : tableau de pointeurs sur une structure Jeux
//	      - int tlogJeux : variable contenant la taille logique du tableau des jeux
//	      - char nomJeu[] : tableau contenant le nom du jeu recherché
//	      - int *trouve : pointeur sur une variable qui va contenir 0 ou 1 si le jeu recherché a été trouvé ou non dans le tableau des jeux 
//retour : la position du jeu recherché
//variable : - int i : destinée à contenir la position du jeu 
//objectif : rechercher le nom d'un jeu dans le tableau des jeux

int rechercheJeu(Jeux *tabJeux[],int tlogJeux,char nomJeu[],int *trouve){
int i;

	for(i=0;i<tlogJeux;i++)
		if(strcmp(tabJeux[i]->nom,nomJeu)==0){
			*trouve=1;		
			return i;
		}
*trouve=0;	
return tlogJeux;
}


//auteur : VIGNON Ugo
//fonction : comptageExemplaires
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int tlogEmprunts : variable contenant la taille logique du tableau des emprunts
//	      - char idJeux[] : id du jeu voulu
//	      - int nb : variable contenant le nombre total d'exemplaire du jeu
//retour : -1 en cas d'echec ou 0 en cas de succès en fonction du nombre d'emprunt du jeu en question
//variable : - int cpt : destinée à contenir le nombre d'emprunt total d'un jeu
//	     - int i : indice pour boucler dans la boucle for
//objectif : retourner 0 si il reste des exemplaires d'un jeu ou -1 dans le cas contraire

int comptageExemplaires(Emprunt tabEmprunts[],int tlogEmprunts,char idJeux[],int nb){
int cpt=0,i;

	for(i=0;i<tlogEmprunts;i++){
		if(strcmp(tabEmprunts[i].idJeux,idJeux)==0)
			cpt++;
	}

	if(cpt==nb){
		printf("\n\n\t\tIl n'y a plus d'exemplaire en stock, réservation requise\n");
		return -1;
	}
printf("\n\n\t\tIl reste %d exemplaire(s) en stock\n\n",nb-cpt);
return 0;
}


//auteur : VIGNON Ugo
//fonction : saisieJeu
//paramètre : - char nomJeu[] : tableau destiné à contenir le nom du jeu saisie
//retour : (aucun)
//variable : - int taille : destinée à contenir la taille du nom du jeu saisie et récupérer par un fgets
//objectif : saisir le nom d'un jeu (utilisé pour factoriser des lignes de codes et rendre le test plus lisible)

void saisieJeu(char nomJeu[]){
int taille;

	printf("Nom du jeu : ");
	fgets(nomJeu,32,stdin);
	taille=strlen(nomJeu);
	if(nomJeu[taille-1]=='\n')
		nomJeu[taille-1]='\0';

}


//auteur : VIGNON Ugo
//fonction : ajouterUnEmprunt
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int *tlogEmprunts : pointeur sur une variable contenant la taille logique du tableau des emprunts
//	      - int *tmax : pointeur sur une variable contenant la taille physique du tableau des emprunts
//	      - Adherent adh : adhérent pour lequel l'emprunt doit être ajouté
//	      - char idJeux[] : id du jeu pour lequel l'emprunt doit être ajouté
//retour : le tableau ayant l'adhérent inséré 
//variable : - int taille : contenir la taille de l'id de l'emprunt
//	     - int retour : contenir le le code de retour pour savoir in un emprunt peut être réalisé par l'adhérent
//objectif : ajouter un emprunt pour un adhérent si toutes les conditions de validité sont remplies

Emprunt* ajouterUnEmprunt(Emprunt tabEmprunts[],int *tlogEmprunts,int *tmax,Adherent adh,char idJeux[]){
Emprunt*aux,emp;
int taille,retour;
	strcpy(emp.idEmprunt,tabEmprunts[*tlogEmprunts-1].idEmprunt);
	strcpy(emp.idAdherent,adh.idAdherent);
	strcpy(emp.idJeux,idJeux);
	
	printf("\nSaisissez la date d'aujourd'hui \n");
	printf("\tjour (en nombre) : ");
	scanf("%d%*c",&emp.dateEmp.jour);
	printf("\tmois (en nombre) : ");
	scanf("%d%*c",&emp.dateEmp.mois);
	printf("\tannée (4 chiffres) : ");
	scanf("%d%*c",&emp.dateEmp.annee);

	retour=empruntValide(tabEmprunts,*tlogEmprunts,adh,emp.dateEmp,idJeux);

	if(retour == 0)
		return tabEmprunts;	
	
	taille=strlen(emp.idEmprunt);
	if(emp.idEmprunt[taille-1]==57){
		emp.idEmprunt[taille-1]=48;
		if(emp.idEmprunt[taille-2]==57){
			emp.idEmprunt[taille-2]=48;
			if(emp.idEmprunt[taille-3]==57){
				emp.idEmprunt[taille-3]=48;
				if(emp.idEmprunt[taille-4]==57){
					printf("nombre maximal d'emprunt atteint mise à jour nécessaire\n");
					return NULL;
				}
				else 
					emp.idEmprunt[taille-4]+=1;
			}
			else
				emp.idEmprunt[taille-3]+=1;
		}
		else
			emp.idEmprunt[taille-2]+=1;
	}		
	else
		emp.idEmprunt[taille-1]+=1;
	if(*tmax==*tlogEmprunts){
		*tmax=*tmax+5;
		aux=(Emprunt*)realloc(tabEmprunts,*tmax*sizeof(Emprunt));
		if(aux == NULL){
			printf("problème réallocation mémoire\n");
			return NULL;
		}
	tabEmprunts=aux;
	}
	tabEmprunts[*tlogEmprunts]=emp;
	(*tlogEmprunts)++;
	printf("\n\nEmprunt créé avec succès ! \n");
return tabEmprunts;
}


//auteur : VIGNON Ugo
//fonction : decalerAGauche
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int *tlogEmprunts : pointeur sur une variable contenant la taille logique du tableau des emprunts
//	      - int posEmprunt : position de l'emprunt à supprimer
//retour : (aucun) 
//variable : - int i : index pour boucler dans la boucle for
//objectif : supprimer un emprunt

void decalerAGauche(Emprunt tabEmprunts[],int *tlogEmprunts,int posEmprunt){
int i;

	for(i=posEmprunt;i+1<*tlogEmprunts;i++)
		tabEmprunts[i]=tabEmprunts[i+1];

	(*tlogEmprunts)--;
}


//auteur : VIGNON Ugo
//fonction : rechercheEmpruntJeu
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int tlogEmprunts : taille logique du tableau de emprunts
//	      - char idJeux[] : tableau contenant l'id du jeu de l'emprunt recherché
//	      - char idAdherent[] : tableau contenant l'id de l'adhérent de l'emprunt recherché
//retour : la position de l'emprunt dans le tableau ou -1 s'il n'a pas été trouvé
//variable : - int i : index pour boucler dans la boucle for
//objectif : rechercher un l'emprunt d'un jeu

int rechercheEmpruntJeu(Emprunt tabEmprunts[],int tlogEmprunts,char idJeux[], char idAdherent[]){
int i;

for(i=0;i<tlogEmprunts;i++)
	if(strcmp(tabEmprunts[i].idJeux,idJeux)==0 && strcmp(tabEmprunts[i].idAdherent,idAdherent)==0)
		return i;

	printf("Aucun emprunt trouvé\n");
return -1;
}


//auteur : VIGNON Ugo
//fonction : rechercheDerniereReservation
//paramètre : - Reservation l : liste des réservations
//	      - Maillon *res : pointeur sur un Maillon
//retour : (aucun)
//variable : (aucune)
//objectif : rechercher la dernière réservation de la liste pour obtenir son id de réservation

void rechercheDerniereReservation(Reservation l,Maillon *res){

	if(l->suiv==NULL){
		strcpy(res->idResa,l->idResa);
		return;
	}
	rechercheDerniereReservation(l->suiv,res);
}


//auteur : VIGNON Ugo
//fonction : ajouterUneReservation
//paramètre : - Reservation l : liste des réservations
//	      - Adherent adh : adhérent devant être ajouté à la réservation
//	      - Jeux jeu : jeu devant être ajouté à la réservation
//retour : la liste actualisée
//variable : - Maillon res : variable qui contiendra  la réservation devant être insérée dans la liste 
//	     - int taille : variable recevant la taille de l'id réservation
//	     - int retour : variable qui reçoit le code de retour pour savoir si la réservation est déjà présente
//objectif : ajouter une nouvelle réservation dans la liste sauf si elle est déjà présente pour l'adhérent en question

Reservation ajouterUneReservation(Reservation l,Adherent adh,Jeux jeu){
Maillon res;
int taille,retour;
	

	retour=rechercheReservation(l,jeu.idJeux,adh.idAdherent);
	if(retour == -1){
		printf("\n\tRéservation de l'adhérent '%s' pour le jeux '%s' déjà présente\n",adh.idAdherent,jeu.nom);
		return l;
	}	
	
	rechercheDerniereReservation(l,&res);
	strcpy(res.idAdherent,adh.idAdherent);
	strcpy(res.idJeux,jeu.idJeux);
	printf("\nSaisissez la date d'aujourd'hui\n");
		printf("\tjour (en nombre) : ");
		scanf("%d%*c",&res.dateRes.jour);
		printf("\tmois (en nombre) : ");
		scanf("%d%*c",&res.dateRes.mois);
		printf("\tannée (4 chiffres) : ");
		scanf("%d%*c",&res.dateRes.annee);

	retour=retour=adherentValide(adh,res.dateRes);
	if(retour == 0){
		printf("\nréservation impossible,l'adhérent '%s' doit payer à nouveau une adhésion",adh.idAdherent);
		return l;
	}

	taille=strlen(res.idResa);
	if(res.idResa[taille-1]==57){
		res.idResa[taille-1]=48;
		if(res.idResa[taille-2]==57){
			res.idResa[taille-2]=48;
			if(res.idResa[taille-3]==57){
				res.idResa[taille-3]=48;
				if(res.idResa[taille-4]==57){
					printf("nombre maximal de réservation atteint mise à jour nécessaire\n");
					return NULL;
				}
				else 
					res.idResa[taille-4]+=1;
			}
			else
				res.idResa[taille-3]+=1;
		}
		else
			res.idResa[taille-2]+=1;
	}		
	else
		res.idResa[taille-1]+=1;



	printf("Réservation créée avec succès ! \n");
return insererTrie(l,res);
}


//auteur : VIGNON Ugo
//fonction : rechercheReservation
//paramètre : - Reservation l : liste des réservations
//	      - char idJeux[] : id du jeux de la réservation voulu
//	      - char idAdherent[] : id de l'adhérent voulant réservé un jeu
//retour : 0 si la réservation n'est pas présente sinon -1
//variable : (aucune)
//objectif : recherche si une réservation est déjà existante pour un adhérent et un jeu

int rechercheReservation(Reservation l,char idJeux[],char idAdherent[]){

	if(l==NULL)
		return 0;
	if(strcmp(l->idJeux,idJeux)==0 && strcmp(l->idAdherent,idAdherent)==0){
		return -1;
	}
	
return rechercheReservation(l->suiv,idJeux,idAdherent);

}


//auteur : VIGNON Ugo
//fonction : rechercheReservationJeu
//paramètre : - Reservation l : liste des réservations
//	      - char idJeux[] : id du jeux de la réservation voulu
//	      - char idAdherent[] : id de l'adhérent pour la réservation trouvée en premier (premier enregistré premier servi)
//retour : 1 si une réservation est trouvée sinon 0
//variable : (aucune)
//objectif : recherché si une réservation est présente pour un jeu et copier l'idAdhérent pour la première réservation trouvée

int rechercheReservationJeu(Reservation l,char idJeux[],char idAdherent[]){
	if(l==NULL)
		return 0;
	if(strcmp(l->idJeux,idJeux)==0){
		strcpy(idAdherent,l->idAdherent);
		return 1;
	}
	
	return rechercheReservationJeu(l->suiv,idJeux,idAdherent);
}


//auteur : VIGNON Ugo
//fonction : supprimerUneReservation
//paramètre : - Reservation l : liste des réservations
//	      - char idAdherent[] : id de l'adhérent dont la réservation doit être suprimée
//	      - char idJeux[] : id du jeu dont la réservation doit être suprimée
//	      - char idResa[] : id de la réservation qui suit celle qui sera supprimée
//retour : la liste actualisée
//variable : (aucune)
//objectif : supprimer une réservation pour un id de jeu et id adhérent donnés

Reservation supprimerUneReservation(Reservation l,char idAdherent[],char idJeux[],char idResa[]){
	if (l==NULL) 
		return l;
	
	if(strcmp(l->idAdherent,idAdherent)==0 && strcmp(l->idJeux,idJeux)==0){
		
		if (l->suiv != NULL)
			strcpy(idResa,l->suiv->idResa);
	
		return supprimerTete(l);
	}
	
	l->suiv=supprimerUneReservation(l->suiv,idAdherent,idJeux,idResa);
return l;
}

//auteur : VIGNON Ugo
//fonction : supprimerTete
//paramètre : - Reservation l : liste des réservations
//retour : la liste actualisée
//variable : - Maillon*tmp : pointeur sur Maillon qui recevra le Maillon destiné à être supprimé 
//objectif : supprimer une réservation

Reservation supprimerTete(Reservation l){
Maillon*tmp;

	tmp=l;
	l=tmp->suiv;
	free(tmp);

return l;
}


//auteur : VIGNON Ugo
//fonction : idMoinsUn
//paramètre : - char id[] : id devant être décrémenté
//retour : (aucun)
//variable : - int taille : variable qui contiendra la taille de l'id 
//objectif : décrémenté un id passé en paramètre (code ASCII utilisé)

void idMoinsUn(char id[]){
int taille;

	taille=strlen(id);

	if(id[taille-1]==48){
		id[taille-1]=57;
		if(id[taille-2]==48){
			id[taille-2]=57;
			if(id[taille-3]==48){
				id[taille-3]=57;
				id[taille-4]-=1;
			}
			else 
				id[taille-3]-=1;
		}
		else
			id[taille-2]-=1;	
	}
	else 
		id[taille-1]-=1;

}


//auteur : VIGNON Ugo
//fonction : actualisationIdEmprunt
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int tlogEmprunts : taille logique du tableau des emprunts 
//	      - char idEmprunt[] : id de l'emprunt à partir duquel l'actualisation doit avoir lieu
//retour : 1 le tableau des emprunts actualisé
//variable : - int i : index pour boucler dans la boucle for
//objectif : actualisé les id des emprunts à partir d'un id d'emprunt donné en paramètre (pour avoir des id d'emprunts qui se suivent numériquement)

Emprunt* actualisationIdEmprunt(Emprunt tabEmprunts[],int tlogEmprunts,char idEmprunt[]){
int i;


	for(i=0;i<tlogEmprunts;i++){
		if(strcmp(tabEmprunts[i].idEmprunt,idEmprunt)==0){
			idMoinsUn(tabEmprunts[i].idEmprunt);
			if(i+1<tlogEmprunts)
				strcpy(idEmprunt,tabEmprunts[i+1].idEmprunt);
		}
	}

return tabEmprunts;
}


//auteur : VIGNON Ugo
//fonction : actualisationIdReservation
//paramètre : - Reservation l : liste des réservations
//	      - ichar idResa[] : id de la réservation à partir duquel l'actualisation doit avoir lieu
//retour : la liste actualisée
//variable : (aucune)
//objectif : actualisé les id des réservations à partir d'un id de réservation donné en paramètre (pour avoir des id de réservations qui se suivent numériquement)


Reservation actualisationIdReservation(Reservation l,char idResa[]){

	
	if(l == NULL){
		return l;
	}

	if(strcmp(l->idResa,idResa)==0){
		idMoinsUn(l->idResa);
		if(l->suiv != NULL)
			strcpy(idResa,l->suiv->idResa);
	}


	l->suiv=actualisationIdReservation(l->suiv,idResa);
return l;

}

//auteur : VIGNON Ugo
//fonction : rechercheIdAdherent
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs du structure Adherent
//	      - int tlogAdherents : taille logique du tableau des adhérents
//	      - char idAdherent[] : id de l'adhérent devant être récherché
//retour : l'adhérent recherché 
//variable : - int i : index pour boucler dans la boucle for
//objectif : retourné un adhérent trouvé grâce a un id d'adhérent donné en paramètre (idAdherent obligatoirement présent car avant on a vérifié au préalable sinon l'adhérent a été créé. Voilà pourquoi a la fin du for je ne retourne rien d'autre)

Adherent rechercheIdAdherent(Adherent *tabAdherents[],int tlogAdherents,char idAdherent[]){
int deb=0,fin=tlogAdherents-1,m;

	//for(i=0;i<tlogAdherents;i++)
		//if(strcmp(tabAdherents[i]->idAdherent,idAdherent)==0)
		//	return *tabAdherents[i];
	while(deb<=fin){
		m=(deb+fin)/2;
		if(strcmp(idAdherent,tabAdherents[m]->idAdherent)==0) 
			return *tabAdherents[m];
		if(strcmp(idAdherent,tabAdherents[m]->idAdherent)<0) 
			fin=m-1;
		else 
			deb=m+1;
	}
	//return deb; <-- pas nécessaire dans notre programme
}


//auteur : VIGNON Ugo
//fonction : adherentValide
//paramètre : - Adherent adh : id de l'adhérent souhaitant faire un emprunt
//	      - Date date : date de la réservation ou de l'emprunt
//retour : retourne un type Booleen(FAUX=0 et VRAI=1)
//variable :  - int jourDateInscription : nombre de jours écoulés jusqu'à la date de l'inscription de l'adhérent
//	      - int jourDateEmp : nombre de jour écoulés jusqu'à la date de l'emprunt voulant être effectué
//objectif : Vérifier si l'adhérent ne doit pas payer de nouveau une adhésion.

Booleen adherentValide(Adherent adh,Date date){
int jourDateInscription=0,jourDate=0;

	jourDateInscription=adh.dateInscri.annee*365;
	jourDate=date.annee*365;
	while(adh.dateInscri.mois != 0){
		
		if(adh.dateInscri.mois==2)		
			jourDateInscription+=28;		
		else if(adh.dateInscri.mois%2 == 0)
			jourDateInscription+=30;
			else
				jourDateInscription+=31;
		
		adh.dateInscri.mois--;
	}
	
	while(date.mois != 0){
		if(date.mois==2)		
			jourDate+=28;
		if(date.mois%2 == 0)
			jourDate+=30;
		else
			jourDate+=31;
		
		date.mois--;
	}
	jourDate+=date.jour;
	jourDateInscription+=adh.dateInscri.jour;
	

	if(jourDate-jourDateInscription >= 365)
		return FAUX;
	

return VRAI;
}

//auteur : VIGNON Ugo
//fonction : empruntValide
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int tlogEmprunts : taille logique du tableau des emprunts 
//	      - Adherent adh : id de l'adhérent souhaitant faire un emprunt
//	      - Date dateEmprunt : date à  laquelle à lieu l'emprunt
//	      - char idJeux[] : id du jeu voulant être emprunté
//retour : retourne un type Booleen(FAUX=0 et VRAI=1)
//variable : - int cpt : compteur du nombre d'emprunt en cours de l'adhérent
//	     - int i : index pour boucler dans la boucle for
//	     - int retour : variable pour récupérer la valeur de retour de la validité de l'adhérent
//objectif : Vérifier si l'adhérent ne doit pas payer de nouveau une adhésion. Vérifier si l'adhérent n'a pas déjà 3 emprunts en cours. Vérifier si l'adhérent n'a pas déjà emprunté le jeu en question. SI tous ls cas sont validé VRAI est retouné, FAUX si au moins un cas n'est pas validé.

Booleen empruntValide(Emprunt tabEmprunts[],int tlogEmprunts,Adherent adh,Date dateEmprunt,char idJeux[]){
int cpt=0,i, retour;

	retour=adherentValide(adh,dateEmprunt);
	if(retour == 0){
		printf("emprunt impossible,l'adhérent '%s' doit payer à nouveau une adhésion",adh.idAdherent);
		return FAUX;			
	}

	for(i=0;i<tlogEmprunts;i++){
		if(strcmp(tabEmprunts[i].idAdherent,adh.idAdherent)==0)
			cpt++;
	}
	if(cpt==3){
		printf("\nemprunt impossible, nombre maximal d'emprunt atteint pour l'adhérent : %s d'abord rendre un jeu\n",adh.idAdherent);
		return FAUX;
	}

	for(i=0;i<tlogEmprunts;i++){
		if(strcmp(tabEmprunts[i].idAdherent,adh.idAdherent)==0 && strcmp(tabEmprunts[i].idJeux,idJeux)==0){
			printf("\n\n      emprunt impossible,l'adhérent : '%s' a déjà un emprunt pour ce jeu\n",adh.idAdherent);
			return FAUX;
		}
			
	}

return VRAI;
}


//auteur : VIGNON Ugo
//fonction : sauvegardeJeux
//paramètre : - Jeux *tabJeux[] : tableau de pointeurs sur structure Jeux
//	      - int tlogJeux : taille logique du tableau des jeux 
//retour : (aucun)
//variable : - FILE*fs : flux de l'ouverture du fichier binaire des jeux
//	     - int i : index pour boucler dans la boucle for
//objectif : sauvegarder le tableau des jeux dans un fichier binaire

void sauvegardeJeux (Jeux *tabJeux[],int tlogJeux){
FILE*fs;
int i;

	fs=fopen("jeux.bin","wb");
	if(fs == NULL){
		printf("problème sauvegarde fichiers binaire des jeux\n");
		exit(1);	
	}
	for(i=0;i<tlogJeux;i++){
		fwrite(tabJeux[i],sizeof(Jeux),1,fs);
	}
fclose(fs);
}


//auteur : VIGNON Ugo
//fonction : chargementJeuxBin
//paramètre : - int *tlog : pointeur sur la taille logique du tableau des jeux
//	      - int *tmax : pointeur sur la taille physique du tableau des jeux
//retour : le tableau de pointeurs sur structure Jeux, chargé à partir du fichier binaire des jeux. NULL est retourné si une erreur a eu lieu
//variable : - FILE*fe : flux de l'ouverture du fichier binaire
//	     -  Jeux jeu : jeu recevant un jeu suite à la lecture d'un jeu dans le fichier binaire
//	     -  Jeux **tab : tableau de pointeurs sur structure Jeux chargé à partir du fichier des jeux
//	     -  Jeux **aux : tableau de pointeurs sur structure Jeux servant pour le realloc
//objectif : chargé le tableau des jeux à partir du fichier binaire des jeux

Jeux** chargementJeuxBin (int *tlog,int *tmax){
 FILE*fe;
 Jeux jeu, **tab,**aux;


	*tlog=0;
	*tmax=5;
	 fe=fopen("jeux.bin","rb");
	 if (fe==NULL){
		 printf("problème ouverture fichier binaire\n");
		 return NULL;
	 }
	tab=(Jeux**)malloc(*tmax*sizeof(Jeux*));
	tab[*tlog]=(Jeux*)malloc(sizeof(Jeux));
		 if(tab[*tlog]==NULL){
			 printf("problème allocation mémoire\n");
			 fclose(fe);
			 return NULL;
		 }
		 
	fread(tab[*tlog],sizeof(Jeux),1,fe);
		 
	 while(!feof(fe)){
		(*tlog)++;
		 if(*tlog==*tmax){
			*tmax=*tmax+5;
			aux=(Jeux**)realloc(tab,*tmax*sizeof(Jeux*));
			if(aux == NULL){
				printf("problème de réallocation mémoire\n");
				fclose(fe);
				return NULL;
			}
			tab=aux;
		 }
		 tab[*tlog]=(Jeux*)malloc(sizeof(Jeux));
		 if(tab[*tlog]==NULL){
			 printf("problème allocation mémoire\n");
			 fclose(fe);
			 return NULL;
		 }
		 
		 fread(tab[*tlog],sizeof(Jeux),1,fe);
	 }
	 fclose(fe);
return tab;
}


//auteur : VIGNON Ugo
//fonction : sauvegardeAdherent
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur structure Adherent
//	      - int tlogAdherents : taille logique du tableau des adhérents 
//retour : (aucun)
//variable : - FILE*fs : flux de l'ouverture du fichier binaire des adhérents
//	     - int i : index pour boucler dans la boucle for
//objectif : sauvegarder le tableau des adhérents dans un fichier binaire

void sauvegardeAdherent (Adherent *tabAdherents[],int tlogAdherents){
FILE*fs;
int i;

	fs=fopen("adherents.bin","wb");
	if(fs == NULL){
		printf("problème sauvegarde fichiers binaire des jeux\n");
		exit(1);	
	}
	fprintf(fs,"%d\n",tlogAdherents);
	for(i=0;i<tlogAdherents;i++){
		fwrite(tabAdherents[i],sizeof(Adherent),1,fs);
	}
fclose(fs);
}


//auteur : VIGNON Ugo
//fonction : chargementAdherentsBin
//paramètre : - int *tlog : pointeur sur la taille logique du tableau des adhérents
//	      - int *tmax : pointeur sur la taille physique du tableau des adhérents
//retour : le tableau de pointeurs sur structure Adherent, chargé à partir du fichier binaire des adhérents. NULL est retourné si une erreur a eu lieu
//variable : - FILE*fe : flux de l'ouverture du fichier binaire
//	     -  Adherent **tab : tableau de pointeurs sur structure Adherent chargé à partir du fichier des adhérents
//	     -  int i : index pour boucler dans la boucle for
//objectif : charger le tableau des adhérents à partir du fichier binaire des adhérents


Adherent** chargementAdherentsBin (int *tlog,int *tmax){
FILE*fe;
Adherent **tab;
int i;

	
	fe=fopen("adherents.bin","rb");
	if (fe==NULL){
		printf("problème ouverture fichier\n");
		return NULL;
	}
	fscanf(fe,"%d%*c",tlog);
	*tmax=*tlog;
	tab=(Adherent**)malloc(*tlog*sizeof(Adherent*));
	if(tab == NULL){
		printf("problème allocation mémoire\n");
		fclose(fe);
		return NULL;
	}
	
	
	for(i=0;i<*tlog;i++){
		tab[i]=(Adherent*)malloc(sizeof(Adherent));
		if(tab[i]==NULL){
			printf("problème allocation mémoire\n");
			fclose(fe);
			return NULL;
		}
		fread(tab[i],sizeof(Adherent),1,fe);
	}

	fclose(fe);
return tab;
}


//auteur : VIGNON Ugo
//fonction : sauvegardeEmprunts
//paramètre : - Emprunt tabEmprunts[] : tableau de structure Emprunt
//	      - int tlogEmprunts : taille logique du tableau des emprunts
//retour : (aucun)
//variable : - FILE*fs : flux de l'ouverture du fichier binaire des emprunts
//	     - int i : index pour boucler dans la boucle for
//objectif : sauvegarder le tableau des emprunts dans un fichier binaire

void sauvegardeEmprunts (Emprunt tabEmprunts[],int tlogEmprunts){
FILE*fs;
int i;

	fs=fopen("emprunts.bin","wb");
	if(fs == NULL){
		printf("problème sauvegarde fichiers binaire des jeux\n");
		exit(1);	
	}
	fprintf(fs,"%d\n",tlogEmprunts);
	fwrite(tabEmprunts,sizeof(Emprunt),tlogEmprunts,fs);
fclose(fs);
}


//auteur : VIGNON Ugo
//fonction : chargementEmpruntsBin
//paramètre : - Emprunt *tabEmprunts : tableau de structure Emprunt
//	      - int *tlog : pointeur sur la taille logique du tableau des emprunts
//retour : le tableau des emprunts, chargé à partir du fichier binaire des emprunts. NULL est retourné si une erreur a eu lieu
//variable : - FILE*fe : flux de l'ouverture du fichier binaire
//	     -  Emprunt emp : variable recevant un emprunt suite à la lecture d'un emprunt dans le fichier des emprunts
//objectif : chargé le tableau des emprunts à partir du fichier binaire des emprunts

Emprunt* chargementEmpruntsBin (Emprunt *tabEmprunts,int *tlog){
FILE*fe;
Emprunt emp;

	fe=fopen("emprunts.bin","rb");
	if (fe==NULL){
		printf("problème allocation mémoire\n");
		*tlog=-1;
		return NULL;
	}
	fscanf(fe,"%d%*c",tlog);
	tabEmprunts=(Emprunt*)malloc(*tlog*sizeof(Emprunt));
	if(tabEmprunts==NULL){
			printf("problème allocation mémoire\n");
			fclose(fe);
			*tlog=-1;
			return NULL;
	}
		fread(tabEmprunts,sizeof(Emprunt),*tlog,fe);

	fclose(fe);
return tabEmprunts;
}


//auteur : VIGNON Ugo
//fonction : sauvegardeListeBin
//paramètre : - Reservation l : liste des réservations
//	      - FILE* fs : flux d'ouverture du fichier binaire des réservations
//retour : (aucun)
//variable : (aucune)
//objectif : sauvegarder la liste des réservation dans un fichier binaire

void sauvegardeListeBin (Reservation l,FILE* fs){
	
	if(l == NULL) return;

	fwrite(l,sizeof(Maillon),1,fs);

	sauvegardeListeBin(l->suiv,fs);
}


//auteur : VIGNON Ugo
//fonction : sauvegardeReservationsBin
//paramètre : - Reservation l : liste des réservations
//retour : (aucun)
//variable : - FILE*fs : flux d'ouverture du fichier binaire des réservations
//	     - int i : indice pour boucler dans la boucle for
//objectif : ouvrir le fichier binaire des réservations pour sauvegarder en binaire

void sauvegardeReservationsBin (Reservation l){
FILE*fs;
int i;

	fs=fopen("reservations.bin","wb");
	if(fs == NULL){
		printf("problème sauvegarde fichiers binaire des jeux\n");
		exit(1);	
	}
	sauvegardeListeBin(l,fs);
	
fclose(fs);
}


//auteur : VIGNON Ugo
//fonction : chargementReservationBin
//paramètre : (aucun)
//retour : la liste des réservation chargée
//variable : - FILE*fe : flux d'ouverture du fichier binaire des réservations
//	     - Reservation l : liste des réservations destinée à être chargée à partir du fichier binaire des réservations
//	     - Reservation p : liste servant à ajouter toutes les réservations dans la liste
//	     - Maillon e : variable recevant une réservation
//objectif : chargé la liste des réservation à partir du fichier binaire des réservations

//l va toujours pointer sur le début de liste tandis que p va ajouter des éléments de la liste mais ne pointera plus sur le début de la liste voilà pourquoi on initialise p qui est une deuxième liste

Reservation chargementReservationBin(void){
FILE*fe;
Reservation l=listeVide(),p;
Maillon e;



	fe=fopen("reservations.bin","rb");
	if(fe==NULL){
		printf("problème ouverture fichier des reservations binaire\n");
		return NULL;
	}
	l=(Maillon*)malloc(sizeof(Maillon));
	fread(l,sizeof(Maillon),1,fe);
	p=l;
	while(fread(&e,sizeof(Maillon),1,fe)){
		p->suiv=(Maillon*)malloc(sizeof(Maillon));
		p=p->suiv;
		*p=e;
		p->suiv=NULL;
	}
	fclose(fe);	

return l;
}

//auteur : VIGNON Ugo
//fonction : liberationPointeursAdherents
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur structure Adherent
//	      - int tlogAdherents : taille logique du tableau des adhérents
//retour : (aucun)
//variable : - int i : indice pour boucler dans la boucle for
//objectif : libérer les espaces mémoires alloués au préalable pour des adhérents

void liberationPointeursJeux(Jeux *tabJeux[],int tlogJeux){
int i;

	for(i=0;i<tlogJeux;i++)
		free(tabJeux[i]);

}

//auteur : VIGNON Ugo
//fonction : liberationPointeursAdherents
//paramètre : - Adherent *tabAdherents[] : tableau de pointeurs sur structure Adherent
//	      - int tlogAdherents : taille logique du tableau des adhérents
//retour : (aucun)
//variable : - int i : indice pour boucler dans la boucle for
//objectif : libérer les espaces mémoires alloués au préalable pour des adhérents

void liberationPointeursAdherents(Adherent *tabAdherents[],int tlogAdherents){
int i;

	for(i=0;i<tlogAdherents;i++)
		free(tabAdherents[i]);

}


//auteur : VIGNON Ugo
//fonction : liberationListeReservations
//paramètre : (aucun)
//retour : la liste vide
//variable : (aucune)
//objectif : libérer les espaces mémoires alloués au préalable pour des maillons

Reservation liberationListeReservations(Reservation l){

	if (l == NULL) return l;

	l->suiv=liberationListeReservations(l->suiv);

	free(l);
	l=NULL;

return l;
}

//auteur : VIGNON Ugo
//fonction : fchoixMenu
//paramètre : (aucun)
//retour : le choix de l'utilisateur
//variable : - int choix : variable recevant le choix de l'utilisateur
//objectif : afficher les fonctionnalités du projet sous forme de menu pour que l'utilisateur choisisse

int fchoixMenu (void){
int choix;
	system("clear");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t[BONUS]chargement des fichiers binaires(0)\n");
	printf("\t\tAffichage (1)\n");
	printf("\t\tRéservations pour un jeu donné (2)\n");
	printf("\t\tEmprunt ou réservation d'un jeu (3)\n");
	printf("\t\tRetour d'un jeu (4)\n");
	printf("\t\tAnnulation d'une réservation (5)\n");
	printf("\t\tQuitter (6)\n");
	scanf("%d%*c",&choix);

return choix;
}


//auteur : VIGNON Ugo
//fonction : attenteMenu
//paramètre : (aucun)
//retour : (aucun)
//variable : - char tmp : variable servant a récupérer la touche saisie
//objectif : mettre en pause le projet pour laisser le temps a l'utilisateur de voir les informations affiché ( à cause du "system("clear")" ) 

void attenteMenu (void){
char tmp;

printf("\n\nEntrez une touche pour continuer ...  ");
scanf("%c%*c",&tmp);
}



