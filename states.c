// BOISSON Romain - GUY Timothée

#include "states.h"

/*
struct state {
	int number;
	bool is_initial;
	bool is_final;
};

struct transition {
	struct state start;
	struct state end;
	char letter;
};
*/

// Création d'un nouvelle etat 
void states_create(struct state *self,int number){
	self = malloc(sizeof(struct state));
	self->number = number;
	self->is_initial = false;
	self->is_final = false;
}

// Destruction d'un etat
void states_destroy(struct state *self){
	free(self);
}

