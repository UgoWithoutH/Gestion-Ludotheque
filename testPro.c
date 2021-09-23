#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"pro.h"

void test (void){
int tlogJeux,tlogAdherents,tlogEmprunts,tmaxJeux,tmaxAdh,tmaxEmp,retour,posAdherent,posEmprunt,posJeu,tmp,choix,trouve;
Jeux **tabJeux;
Adherent **tabAdherents,adh;
Emprunt *tabEmprunts;
Reservation l;
char idAdherent[6],idResa[6]={'\0'},idEmprunt[6],nom[32],prenom[32],nomJeu[32];

tabJeux=chargementJeux(&tlogJeux,&tmaxJeux);
tabAdherents=chargementAdherents(&tlogAdherents,&tmaxAdh);
tabEmprunts=chargementEmprunts(tabEmprunts,&tlogEmprunts,&tmaxEmp);
l=chargementReservation(l);
	
choix=fchoixMenu();

	while(choix != 6){
		if(choix == 0){
			tabJeux=chargementJeuxBin(&tlogJeux,&tmaxJeux);
			tabAdherents=chargementAdherentsBin(&tlogAdherents,&tmaxAdh);
			tabEmprunts=chargementEmpruntsBin(tabEmprunts,&tlogEmprunts);
			l=chargementReservationBin();
			attenteMenu();		
		}

		if (choix == 1){
			triJeux(tabJeux,tlogJeux);
			affichageJeux(tabJeux,tlogJeux);
			affichageAdherent(tabAdherents,tlogAdherents);
			affichageEmprunts(tabEmprunts,tabJeux,tabAdherents,tlogEmprunts,tlogJeux,tlogAdherents);
			printf("\nidRéservation // idAdherent // idJeux // Date de la réservation\n\n");
			afficheReservation(l);
			attenteMenu();
		}

		if(choix == 2){
			saisieJeuDonne(l,tabJeux,tlogJeux);			
			attenteMenu();
		}

		if (choix == 3){		
	
			tabAdherents=saisieAdherent(tabAdherents,&tlogAdherents,&posAdherent,&tmaxAdh);
			if(posAdherent >= 0){
				saisieJeu(nomJeu);
				posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
					while(trouve == 0){
						printf("Jeu inconnu, ressaisissez \n");
						saisieJeu(nomJeu);
						posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
					}
				retour=comptageExemplaires(tabEmprunts,tlogEmprunts,tabJeux[posJeu]->idJeux,tabJeux[posJeu]->nb);
				if (retour == 0)	tabEmprunts=ajouterUnEmprunt(tabEmprunts,&tlogEmprunts,&tmaxEmp,*tabAdherents[posAdherent],tabJeux[posJeu]->idJeux);
				
				else if(retour == -1)
					l=ajouterUneReservation(l,*tabAdherents[posAdherent],*tabJeux[posJeu]);
			}
		attenteMenu();
		}

		if (choix == 4){
			saisieNomPrenom(nom,prenom);
			posAdherent=rechercheAdherent(tabAdherents,nom,prenom,tlogAdherents,&trouve);
			while(trouve == 0){
				printf("erreur aucun adhérent trouvé, ressaisissez \n");
				saisieNomPrenom(nom,prenom);
				posAdherent=rechercheAdherent(tabAdherents,nom,prenom,tlogAdherents,&trouve);
			}
			saisieJeu(nomJeu);
			posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
			while(trouve == 0){
				printf("Jeu inconnu, ressaisissez \n");
				saisieJeu(nomJeu);
				posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
			}
			posEmprunt=rechercheEmpruntJeu(tabEmprunts,tlogEmprunts,tabJeux[posJeu]->idJeux,tabAdherents[posAdherent]->idAdherent);
			if (posEmprunt != -1){
				strcpy(idEmprunt,tabEmprunts[posEmprunt+1].idEmprunt);
				decalerAGauche(tabEmprunts,&tlogEmprunts,posEmprunt);
				tabEmprunts=actualisationIdEmprunt(tabEmprunts,tlogEmprunts,idEmprunt);
				printf("\n\tle jeu '%s' a bien été rendu\n",tabJeux[posJeu]->nom);
				
				retour=rechercheReservationJeu(l,tabJeux[posJeu]->idJeux,idAdherent);
				if(retour==1){
						adh=rechercheIdAdherent(tabAdherents,tlogAdherents,idAdherent);
						tmp=tlogEmprunts;
						tabEmprunts=ajouterUnEmprunt(tabEmprunts,&tlogEmprunts,&tmaxEmp,adh,tabJeux[posJeu]->idJeux);
						
						if (tmp != tlogEmprunts){
							l=supprimerUneReservation(l,idAdherent,tabJeux[posJeu]->idJeux,idResa);
							l=actualisationIdReservation(l,idResa);
							printf("Nouvel emprunt créé pour l'adhérent '%s' qui avait réservé le jeu '%s'",idAdherent,tabJeux[posJeu]->nom);
						}
				}
				else
					printf("\n\tAucune réservation trouvée pour le jeu ayant été rendu\n");
			}
			attenteMenu();
		}
		
		if(choix == 5){
			saisieNomPrenom(nom,prenom);
			posAdherent=rechercheAdherent(tabAdherents,nom,prenom,tlogAdherents,&trouve);
			while(trouve == 0){
				printf("erreur aucun adhérent trouvé, ressaisissez \n");
				saisieNomPrenom(nom,prenom);
				posAdherent=rechercheAdherent(tabAdherents,nom,prenom,tlogAdherents,&trouve);
			}
			saisieJeu(nomJeu);
			posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
			while(trouve == 0){
				printf("erreur aucun jeu trouvé, ressaisissez \n");
				saisieJeu(nomJeu);
				posJeu=rechercheJeu(tabJeux,tlogJeux,nomJeu,&trouve);
			}
			
			l=supprimerUneReservation(l,tabAdherents[posAdherent]->idAdherent,tabJeux[posJeu]->idJeux,idResa);
			printf("----%s\n",idResa);
			if(idResa[0]!='\0'){
				l=actualisationIdReservation(l,idResa);
				printf("Réservation supprimée avec succès\n");
			}
			else
				printf("Aucune réservation trouvée pour l'adhérent : '%s' et le jeu : '%s'\n",tabAdherents[posAdherent]->idAdherent,tabJeux[posJeu]->idJeux);

			attenteMenu();
		}
		choix=fchoixMenu();
	}
	sauvegardeJeux(tabJeux,tlogJeux);
	sauvegardeAdherent(tabAdherents,tlogAdherents);
	sauvegardeEmprunts(tabEmprunts,tlogEmprunts);
	sauvegardeReservationsBin(l);
	
	liberationPointeursJeux(tabJeux,tlogJeux);
	free(tabJeux);
	liberationPointeursAdherents(tabAdherents,tlogAdherents);
	free(tabAdherents);
	free(tabEmprunts);
	l=liberationListeReservations(l);

}
int main (void){
test();

return 0;
}
