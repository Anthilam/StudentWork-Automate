// BOISSON Romain - GUY Timothée

#include "fa.h"

/*
struct list{
	int value;
	struct list *next;
}
*/

/*
struct fa {
	size_t alpha_count;
	size_t state_count;
	struct list **state_array;
	int *array_init;
	int *array_final;
};
*/

// Création de l'automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self->alpha_count = alpha_count;
	self->state_count = state_count;
	self->array_init = NULL;
	self->array_final = NULL;
	fa_create_state_list(self);
}

// Création du tableau à deux dimensions états/alphabet
void fa_create_state_list(struct fa *self){
	// Allocation mémoire du tableau total
	struct list **l = (struct list **) malloc(sizeof(struct list *)*self->state_count);

	// Allocation mémoire de chaque cellules du tableau
	for(int i = 0; i < self->state_count; ++i) {
		l[i] = (struct list *) malloc(sizeof(struct list)*self->alpha_count);
		for (int j = 0; j < self->alpha_count; ++j) {
			// Initialisation de chaque liste
			l[i][j].first = NULL;
		}
	}

	self->state_array = l;
}

// Destruction du tableau à deux dimensions
void fa_destroy(struct fa *self) {
	for(int i = 0; i < self->state_count; ++i) {
		for (int j = 0; j < self->alpha_count; ++j) {
			// Libération de chaque liste contenu par le tableau
			fa_destroy_list(&self->state_array[i][j]);
		}
		free(self->state_array[i]);
	}
	free(self->state_array);
}

// Destruction d'une liste de transitions
void fa_destroy_list_node(struct list_node *self) {
	if (self->next != NULL) {
		fa_destroy_list_node(self->next);
	}
	free(self);
}

void fa_destroy_list(struct list *self) {
	if (self->first != NULL) {
		fa_destroy_list_node(self->first);
	}
	self->first = NULL;
}

void fa_set_state_initial(struct fa *self, size_t state) {

}

void fa_set_state_final(struct fa *self, size_t state) {

}

// Ajout d'une transition dans la liste des transitions
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to) {
	int n = alpha - 'a';
	// On vérifie que la lettre fait bien partie de l'alphabet de l'automate
	if (n < self->alpha_count) {
		if (self->state_array[from][n].first == NULL) {
			self->state_array[from][n].first =  malloc(sizeof(struct list_node));
			self->state_array[from][n].first->value = to;
			self->state_array[from][n].first->next = NULL;
		}
		else {
			fa_add_node_transition(self->state_array[from][n].first, to);
		}
	}
}

void fa_add_node_transition(struct list_node *self, size_t to) {
	if (self->next == NULL) {
		struct list_node *l = malloc(sizeof(struct list_node));
		l->value = to;
		l->next = NULL;
		self->next = l;
	}
	else {
		fa_add_node_transition(self->next, to);
	}
}

void fa_pretty_print(const struct fa *self, FILE *out) {

}

void fa_dot_print(const struct fa *self, FILE *out) {

}
