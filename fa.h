// BOISSON Romain - GUY Timothée

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "states.h"

/* Structure représentant l'automate, avec alpha_count la taille de l'alphabet
et state_count le nombre d'états de l'automate */
struct fa {
	size_t alpha_count;
	size_t state_count;
	struct state *state_array;
	struct transition *transition_array;
};

void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

void fa_destroy(struct fa *self);

void fa_set_state_initial(struct fa *self, size_t state);

void fa_set_state_final(struct fa *self, size_t state);

void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to);

void fa_pretty_print(const struct fa *self, FILE *out);

void fa_dot_print(const struct fa *self, FILE *out);
