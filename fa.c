// BOISSON Romain - GUY Timothée

#include "fa.h"

/*
struct list{
	int value;
	struct list *next;
};

struct dyn_tab{
	int *value;
	size_t used;
	size_t size;
};


struct fa {
	size_t alpha_count;
	size_t state_count;
	struct list **state_array;
	struct dyn_tab array_init;
	struct dyn_tab array_final;
};
*/

// Création de l'automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self->alpha_count = alpha_count;
	self->state_count = state_count;
	self->array_init.value= NULL;
	self->array_final.value=NULL;
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
	free(self->array_init.value);
	free(self->array_final.value);
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
	if(self->array_init.value == NULL){
		self->array_init.value = malloc(sizeof(int)*10);
		self->array_init.used = 0;
		self->array_init.size = 10;
	}
	if(self->array_init.used == self->array_init.size){
		int tmp[self->array_init.size * 2];
		for(int i=0;i<self->array_init.used;i++){
			tmp[i] = self->array_init.value[i];
		}
		free(self->array_init.value);
		self->array_init.value = malloc(sizeof(int)*self->array_init.size*2);
		self->array_init.size = self->array_init.size*2;
		for(int i=0;i<self->array_init.used;i++){
			self->array_init.value[i] = tmp[i];
		}
	}
	self->array_init.value[self->array_init.used] = state;
	self->array_init.used++;
}

void fa_set_state_final(struct fa *self, size_t state) {
	if(self->array_final.value == NULL){
		self->array_final.value = malloc(sizeof(int)*10);
		self->array_final.used = 0;
		self->array_final.size = 10;
	}
	if(self->array_final.used == self->array_final.size){
		int tmp[self->array_final.size * 2];
		for(int i=0;i<self->array_final.used;i++){
			tmp[i] = self->array_final.value[i];
		}
		free(self->array_final.value);
		self->array_final.value = malloc(sizeof(int)*self->array_final.size*2);
		self->array_final.size = self->array_final.size*2;
		for(int i=0;i<self->array_final.used;i++){
			self->array_final.value[i] = tmp[i];
		}
		free(tmp);
	}
	self->array_final.value[self->array_final.used] = state;
	self->array_final.used++;
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
	printf("Initial states:\n\t");
	if (self->array_init.value != NULL) {
		for (int i = 0; i < self->array_init.used; ++i) {
			printf("%d ", self->array_init.value[i]);
		}
	}
	printf("\nFinal states:\n\t");
	if (self->array_final.value != NULL) {
		for (int i = 0; i < self->array_final.used; ++i) {
			printf("%d ", self->array_final.value[i]);
		}
	}
	printf("\nTransitions:\n");
	for (int i = 0; i < self->state_count; ++i) {
		printf("\tFor state %d:\n", i);
		for (int j = 0; j < self->alpha_count; ++j) {
			printf("\t\tFor letter '%c': ", j+'a');
			if (self->state_array[i][j].first != NULL) {
				struct list_node *l = self->state_array[i][j].first;
				printf("%d ", l->value);
				while (l->next != NULL) {
					l = l->next;
					printf("%d ", l->value);
				}
			}
			printf("\n");
		}
	}
}

void fa_dot_print(const struct fa *self, FILE *out) {

}

void fa_remove_transition(struct fa *self, size_t from, char alpha, size_t to) {

}

void fa_remove_state(struct fa *self, size_t state) {

}

size_t fa_count_transitions(const struct fa *self) {

}

bool fa_is_deterministic(const struct fa *self) {

}

bool fa_is_complete(const struct fa *self) {

}

void fa_make_complete(struct fa *self) {

}
