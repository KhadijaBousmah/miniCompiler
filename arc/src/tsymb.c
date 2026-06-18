#include "tsymb.h"
#include <stdio.h>
#include <string.h>

int adr=1;

void tsymb_init(tablesymb t){
	int i =0; 
	while (i<32){
		strcpy(t[i].var,"");
		t[i].adresse=0;
		t[i].taille = 0;
		i++;
	}	
}


int tsymb_retrouver(tablesymb t, char* var){
	for (int i=0; i<32; i++){
		if (strcmp(t[i].var,var)==0)
			return t[i].adresse;
	}
	return -1;
}


void tsymb_ajouter(tablesymb t, char* var){
	if (tsymb_retrouver(t,var)==-1){ 
		strcpy(t[adr-1].var,var);
		t[adr-1].adresse=adr;
		t[adr-1].taille=1;
		adr++;
	} 
}

void tsymb_print(tablesymb t){
	int i =0; 
	printf("\n\tTABLE DES SYMBOLES \n");
	while (i<32){
		if (t[i].var[0] == '\0')
			return; 
		printf("symbole numero %d\n",i);
		printf("identificateur %s\n",t[i].var);
		printf("adresse %d\n",t[i].adresse);
		printf("taille %d\n",t[i].taille);
		i++;
	}	
}



