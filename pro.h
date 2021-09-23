#include<stdio.h>

//Auteur des structures : VIGNON Ugo

typedef struct{
	int jour;
	int mois;
	int annee;
}Date;

typedef struct{
	char idJeux[6];
	char nom[32];
	char type[13];
	int nb;
}Jeux;

typedef struct{
	char idAdherent[6];
	char civilite[4];
	char nom[32];
	char prenom[32];
	Date dateInscri;
}Adherent;

typedef struct{
	char idEmprunt[6];
	char idAdherent[6];
	char idJeux[6];
	Date dateEmp;  
}Emprunt;

typedef struct maill{
	char idResa[6];
	char idAdherent[6];
	char idJeux[6];
	Date dateRes;  
	struct maill*suiv;
}Maillon;
typedef Maillon*Reservation;

typedef enum{FAUX,VRAI}Booleen;

Jeux lireUnJeu (FILE*fe);
Adherent lireUnAdherent (FILE*fe);
Emprunt lireUnEmprunt (FILE*fe);
Reservation InsertionEnTete (Reservation l,Maillon res);
Reservation insererTrie (Reservation l,Maillon res);
Reservation listeVide(void);
Maillon lireUneReservation(FILE*fe);
Jeux** chargementJeux (int *tlog,int *tmax);
Adherent** chargementAdherents (int *tlog,int *tmax);
Emprunt* chargementEmprunts (Emprunt tabEmprunts[],int *tlog,int *tmax);
Reservation chargementReservation(Reservation l);
void triBulle(Jeux *tab[],int tlog);
void triBulle2(Jeux *tab[],int tlog,int index);
void triJeux(Jeux *tab[],int tlog);
void affichageJeux(Jeux *tab[], int tlog);
void affichageAdherent(Adherent *tab[],int tlog);
void affichageEmprunts(Emprunt tabEmp[],Jeux* tabJeux[],Adherent* tabAdher[], int tlogEmprunt, int tlogJeux, int tlogAdher);
void afficheReservation(Reservation l);
void afficheJeuDonne(Reservation l,char idJeux[]);
void saisieJeuDonne (Reservation l,Jeux *tabJeux[],int tlogJeux);
int rechercheAdherent(Adherent *tabAdherents[],char nom[],char prenom[],int tlogAdherent,int *trouve);
Adherent** saisieAdherent(Adherent *tabAdherents[],int *tlogAdherents,int *posAdherent,int *tmax);
int creationAdherent(Adherent *tabAdherents[],int *tlogAdherents,char nom[],char prenom[]);
int rechercheJeu(Jeux *tabJeux[],int tlogJeux,char nomJeu[],int *trouve);
int comptageExemplaires(Emprunt tabEmprunts[],int tlogEmprunts,char idJeux[],int nbExemplaires);
Emprunt* ajouterUnEmprunt(Emprunt tabEmprunts[],int *tlogEmprunts,int *tmax,Adherent adh,char idJeux[]);
Reservation ajouterUneReservation(Reservation l,Adherent adh,Jeux jeu);
void rechercheDerniereReservation(Reservation l,Maillon *res);
int rechercheReservationJeu(Reservation l,char idJeux[],char idAdherent[]);
int rechercheReservation(Reservation l,char idJeux[],char idAdherent[]);
Reservation supprimerUneReservation(Reservation l,char idAdherent[],char idJeux[],char idResa[]);
Reservation supprimerTete(Reservation l);
Emprunt* actualisationIdEmprunt(Emprunt tabEmprunts[],int tlogEmprunts,char idEmprunt[]);
Reservation actualisationIdReservation(Reservation l,char idResa[]);
void idMoinsUn(char idRes[]);
void decalerAGauche(Emprunt tabEmprunts[],int *tlogEmprunts,int posEmprunt);
int rechercheEmpruntJeu(Emprunt tabEmprunts[],int tlogEmprunts,char idJeux[], char idAdherent[]);
Adherent rechercheIdAdherent(Adherent *tabAdherents[],int tlogAdherents,char idAdherent[]);
int rechercheIdJeu(char* id, Jeux** tab, int nb);
Booleen adherentValide(Adherent adh,Date date);
Booleen empruntValide(Emprunt tabEmprunts[],int tlogEmprunts,Adherent adh,Date dateEmprunt,char idJeux[]);
Booleen reservationValide(Reservation l,Adherent adh,Jeux jeu);
void saisieNomPrenom(char nom[],char prenom[]);
void saisieJeu(char nomJeu[]);
void sauvegardeJeux (Jeux *tabJeux[],int tlogJeux);
void sauvegardeAdherent (Adherent *tabAdherents[],int tlogAdherents);
void sauvegardeEmprunts (Emprunt tabEmprunts[],int tlogEmprunts);
void sauvegardeReservationsBin (Reservation l);
void sauvegardeListeBin (Reservation l,FILE* fs);
Jeux** chargementJeuxBin (int *tlog,int *tmax);
Adherent** chargementAdherentsBin (int *tlog,int *tmax);
Emprunt* chargementEmpruntsBin (Emprunt *tabEmprunts,int *tlog);
Reservation chargementReservationBin(void);
void liberationPointeursJeux(Jeux *tabJeux[],int tlogJeux);
void liberationPointeursAdherents(Adherent *tabAdherents[],int tlogAdherents);
Reservation liberationListeReservations(Reservation l);
int fchoixMenu (void);
void attenteMenu (void);


