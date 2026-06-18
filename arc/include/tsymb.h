#ifndef TSYMB_H
#define TSYMB_H



typedef struct {
	char var[32];    //identificateur
	int adresse;	 // adresse dans la machine Ram 	
	int taille;		// pour les tab 
} symbole;


typedef symbole tablesymb[32];


void tsymb_init(tablesymb t);
void tsymb_ajouter(tablesymb t, char* var);
int tsymb_retrouver(tablesymb t, char* var);
void tsymb_print(tablesymb t);

extern int adr;

#endif
