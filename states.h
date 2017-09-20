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

/* Structure représentant une transition, avec l'état de départ,
l'état d'arrivée, et la lettre de transition */
struct transition {
	struct state *start;
	struct state *end;
	char letter;
};

// Creation d'un nouvelle etat 
void states_create(struct state *self,int number);

// Destruction d'un etat
void states_destroy(struct state *self);

// Creation d'une nouvelle transition
void transition_creates(struct transition *self, struct state *from,struct state *to,char letter);

// Destruction d'une transition 
void transistion_destroy(struct transition *self);
