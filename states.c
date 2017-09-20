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

// Creation d'une nouvelle transition
void transition_creates(struct transition *self, struct state *from,struct state *to,char letter){
	assert(from != NULL);
	assert(to != NULL);
	self = malloc(sizeof(struct transition));
	self->start = from;
	self->end = to;
	self->letter= letter;
}

void transistion_destroy(struct transition *self){
	self->start =NULL;
	self->end =NULL;
	free(self);
}
