// BOISSON Romain - GUY Timothée

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Structure représentant un état de l'automate
struct state {
	int number;
	bool is_initial;
	bool is_final;
};


// Creation d'un nouvelle etat 
void states_create(struct state *self,int number);

// Destruction d'un etat
void states_destroy(struct state *self);
