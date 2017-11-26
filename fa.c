// BOISSON Romain - GUY Timothée

#include "fa.h"

// Création d'un automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self->alpha_count = alpha_count;
	self->state_count = state_count;
	self->array_init.value = NULL;
	self->array_final.value = NULL;
	fa_create_state_list(self);
}

// Création du tableau 2D états/alphabet
void fa_create_state_list(struct fa *self){
	// Allocation mémoire du tableau total
	struct list **l = malloc(sizeof(struct list *)*self->state_count);

	// Allocation mémoire de chaque cellules du tableau
	for(int i = 0; i < self->state_count; ++i) {
		l[i] = malloc(sizeof(struct list)*self->alpha_count);
		for (int j = 0; j < self->alpha_count; ++j) {
			// Initialisation de chaque liste
			l[i][j].first = NULL;
		}
	}

	self->state_array = l;
}

// Destruction d'un automate
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

// Passage d'un état à état initial
void fa_set_state_initial(struct fa *self, size_t state) {
	if (self->array_init.value == NULL) {
		self->array_init.value = malloc(sizeof(int)*10);
		self->array_init.used = 0;
		self->array_init.size = 10;
	}

	bool ok = true;
	for (int i = 0; i < self->array_init.used; ++i) {
		if (self->array_init.value[i] == state) {
			ok = false;
		}
	}

	if (ok) {
		if (self->array_init.used == self->array_init.size) {
			int tmp[self->array_init.size * 2];
			for (int i = 0; i < self->array_init.used; ++i) {
				tmp[i] = self->array_init.value[i];
			}

			free(self->array_init.value);
			self->array_init.value = malloc(sizeof(int)*self->array_init.size*2);
			self->array_init.size = self->array_init.size*2;
			for (int i = 0; i < self->array_init.used; ++i) {
				self->array_init.value[i] = tmp[i];
			}
		}

		self->array_init.value[self->array_init.used] = state;
		++self->array_init.used;
	}
}

// Passage d'un état à état final
void fa_set_state_final(struct fa *self, size_t state) {
	if (self->array_final.value == NULL) {
		self->array_final.value = malloc(sizeof(int)*10);
		self->array_final.used = 0;
		self->array_final.size = 10;
	}

	bool ok = true;
	for (int i = 0; i < self->array_final.used; ++i) {
		if (self->array_final.value[i] == state) {
			ok = false;
		}
	}

	if (ok) {
		if (self->array_final.used == self->array_final.size) {
			int tmp[self->array_final.size * 2];
			for (int i = 0; i < self->array_final.used; ++i) {
				tmp[i] = self->array_final.value[i];
			}

			free(self->array_final.value);
			self->array_final.value = malloc(sizeof(int)*self->array_final.size*2);
			self->array_final.size = self->array_final.size*2;
			for (int i = 0; i < self->array_final.used; ++i) {
				self->array_final.value[i] = tmp[i];
			}
		}

		self->array_final.value[self->array_final.used] = state;
		++self->array_final.used;
	}
}

// Ajout d'une transition
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to) {
	int n = alpha - 'a';
	// On vérifie que la lettre fait bien partie de l'alphabet de l'automate
	if (n < self->alpha_count && to < self->state_count) {
		// Si il n'y a pas de transitions, initialisation de la liste chaînée
		if (self->state_array[from][n].first == NULL) {
			self->state_array[from][n].first =  malloc(sizeof(struct list_node));
			self->state_array[from][n].first->value = to;
			self->state_array[from][n].first->next = NULL;
		}
		// Sinon, on parcourt la liste
		else {
			// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
			if (self->state_array[from][n].first->value != to) {
				if (self->state_array[from][n].first->value > to) {
					size_t to_tmp = self->state_array[from][n].first->value;
					self->state_array[from][n].first->value = to;
					fa_add_node_transition(self->state_array[from][n].first, to_tmp);
				}
				else {
					fa_add_node_transition(self->state_array[from][n].first, to);
				}
			}
		}
	}
}

void fa_add_node_transition(struct list_node *self, size_t to) {
	// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
	if (self->value != to) {
		if (self->value < 0) {
			self->value = to;
		}
		else if (self->next == NULL) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = NULL;
			self->next = l;
		}
		else if (self->value < to && self->next->value < to) {
			fa_add_node_transition(self->next, to);
		}
		else if (self->value < to && self->next->value > to) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = self->next;
			self->next = l;
		}
		else {
			fa_add_node_transition(self->next, to);
		}
	}
}

// Affichage d'un automate
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

// Suppression d'une transition
void fa_remove_transition(struct fa *self, size_t from, char alpha, size_t to) {
	int n = alpha - 'a';
	// On vérifie que la lettre fait bien partie de l'alphabet de l'automate
	if (n < self->alpha_count) {
		if (self->state_array[from][n].first != NULL) {
			if (self->state_array[from][n].first->value == to
				&& self->state_array[from][n].first->next == NULL) {
				free(self->state_array[from][n].first);
				self->state_array[from][n].first = NULL;
			}
			else if (self->state_array[from][n].first->value == to
				&& self->state_array[from][n].first->next != NULL) {
				struct list_node *l = self->state_array[from][n].first->next;
				free(self->state_array[from][n].first);
				self->state_array[from][n].first = l;
			}
			else if (self->state_array[from][n].first->next != NULL){
				fa_remove_node_transition(self->state_array[from][n].first, to);
			}
		}
	}
}

void fa_remove_node_transition(struct list_node *self, size_t to) {
	if (self->next->value == to && self->next->next == NULL) {
		free(self->next);
		self->next = NULL;
	}
	else if (self->next->value == to && self->next->next != NULL) {
		struct list_node *l = self->next->next;
		free(self->next);
		self->next = l;
	}
	else if (self->next->next != NULL) {
		fa_remove_node_transition(self->next, to);
	}
}

// Suppression d'un état
void fa_remove_state(struct fa *self, size_t state) {
	if (state < self->state_count) {
		// Suppression de toutes les transitions partant de l'état à supprimer
		for (int i = 0; i < self->alpha_count; ++i) {
			for (int j = 0; j <= self->state_count; ++j) {
				fa_remove_transition(self, state, 'a'+i, j);
			}
		}

		// Suppression de toutes les transitions allant vers l'état à supprimer
		for (int i = 0; i < self->state_count; ++i) {
			for (int j = 0; j < self->alpha_count; ++j) {
				fa_remove_transition(self, i, 'a'+j, state);
			}
		}

		// Suppression de l'état du tableau des états initiaux
		int count = 0;
		bool isUsed = false;
		int *newInit = malloc(sizeof(int)*self->array_init.size);
	 	for (int i = 0; i < self->array_init.used; ++i) {
			if (self->array_init.value[i] != state) {
				newInit[count] = self->array_init.value[i];
				// On décrémente les états > à l'état supprimé
				if (self->array_init.value[i] > state) {
					--newInit[count];
				}
				++count;
			}

			if (self->array_init.value[i] == state) {
				isUsed = true;
			}
		}
		free(self->array_init.value);
		self->array_init.value = newInit;
		if (isUsed == true) {
			--self->array_init.used;
		}

		// Suppression de l'état du tableau des états finaux
		count = 0;
		isUsed = false;
		int *newFinal = malloc(sizeof(int)*self->array_final.size);
		for (int i = 0; i < self->array_final.used; ++i) {
			if (self->array_final.value[i] != state) {
				newFinal[count] = self->array_final.value[i];
				// On décrémente les états > à l'état supprimé
				if (self->array_final.value[i] > state) {
					--newFinal[count];
				}
				++count;
			}

			if (self->array_final.value[i] == state) {
				isUsed = true;
			}
		}
		free(self->array_final.value);
		self->array_final.value = newFinal;
		if (isUsed == true) {
			--self->array_final.used;
		}

		// On supprime l'état puis on décale les états par rapport à l'état supprimé
		free(self->state_array[state]);
		for(int i = state+1; i < self->state_count; ++i) {
			if (i != self->state_count) {
				self->state_array[i-1] = self->state_array[i];
			}
		}

		// On décrémente le nombre d'états
		--self->state_count;

		// On décale toutes les transitions
		for (int i = 0; i < self->state_count; ++i) {
			for (int j = 0; j < self->alpha_count; ++j) {
				// On vérifie qu'il y a une liste de transitions existante
				if (self->state_array[i][j].first != NULL) {
					struct list_node *l = self->state_array[i][j].first;
					// On boucle le décalage tant qu'on est pas au bout de la liste
					while (l != NULL) {
						// On décale seulement les valeurs > à l'état supprimé
						if (l->value >= state) {
							--l->value;
						}
						l = l->next;
					}
				}
			}
		}
	}
}

// Compteur de transitions
size_t fa_count_transitions(const struct fa *self) {
	size_t count = 0;
	// Parcourt du tableau 2D
 	for (int i = 0; i < self->state_count; ++i) {
		for (int j = 0; j < self->alpha_count; ++j) {
			// Parcourt des listes chaînées
			if (self->state_array[i][j].first != NULL) {
				struct list_node *l = self->state_array[i][j].first;
				++count;
				while (l->next != NULL) {
					l = l->next;
					++count;
				}
			}
		}
	}
	return count;
}

// Fonction établissant si l'automate est déterministe
bool fa_is_deterministic(const struct fa *self) {
	int i=0,j=0;
	bool res=true;
	if(self->array_init.used != 1){
		return false;
	}
	while(i<self->state_count && res){
		j=0;
		while(j<self->alpha_count && res){
			if(self->state_array[i][j].first != NULL){
			 	if(self->state_array[i][j].first->next != NULL){
			 		res = false;
			 	}
			}
			j++;
		}
		i++;
	}

	return res;
}

// Fonction établissant si l'automate est complet
bool fa_is_complete(const struct fa *self) {
	int i=0,j=0;
	bool res=true;
	while(i<self->state_count && res){
		j=0;
		while(j<self->alpha_count && res){
			if(self->state_array[i][j].first == NULL){
		 		res = false;
			}
			j++;
		}
		i++;
	}
	return res;
}

// Complétion d'un automate
void fa_make_complete(struct fa *self) {
	if(fa_is_complete(self)){
		return;
	}
	// creation d'une nouvelle automate possedant un etat supplementaire
	// qui sera utilise comme "poubelle"
	self->state_array = realloc(self->state_array,sizeof(struct list *)*(self->state_count+1));
	self->state_count++;
	self->state_array[self->state_count-1] = malloc(sizeof(struct list*)*self->alpha_count);
	int i=0,j;
	for (int k=0;k<self->alpha_count;k++){
		self->state_array[self->state_count-1][k].first=NULL;
	}
	while(i<self->state_count){
		j=0;
		while(j<self->alpha_count){
			if(self->state_array[i][j].first == NULL){
				fa_add_transition(self, i,'a'+j,self->state_count-1);
			}
			j++;
		}
		i++;
	}

}

// Fonction de parcours en profondeur d'un graphe
void graph_depth_first_search(const struct graph *self, size_t state, bool *visited) {
	visited[state] = true;
	if (self->adjacent[state].first != NULL) {
		struct list_node *l = self->adjacent[state].first;

		while (l != NULL) {
			if (!visited[l->value]) {
				graph_depth_first_search(self, l->value, visited);
			}
			l = l->next;
		}
	}
}

bool graph_has_path_with_prev(const struct graph *self, size_t from, size_t to, size_t prev) {
	if (from == to) {
		return true;
	}

	struct list_node *l = self->arc[from].first;

	while (l != NULL) {
		// Si l'arc n'est pas une boucle de l'état sur lui-même
		if (from != l->value && l->value != prev) {
			// Alors on effectue le parcourt
			if (graph_has_path_with_prev(self, l->value, to, from)) {
				return true;
			}

			l = l->next;
		}
		else {
			l = l->next;
		}
	}
	return false;
}

// Fonction déterminant si un chemin existe entre deux états
bool graph_has_path(const struct graph *self, size_t from, size_t to) {
	return graph_has_path_with_prev(self, from, to, 0);
}

// Ajout d'un adjacent
void graph_add_adjacent(struct graph *self, size_t from, size_t to) {
	// On vérifie que la lettre fait bien partie de l'alphabet de l'automate
	if (to < self->state_count) {
		// Si il n'y a pas de transitions, initialisation de la liste chaînée
		if (self->adjacent[from].first == NULL) {
			self->adjacent[from].first =  malloc(sizeof(struct list_node));
			self->adjacent[from].first->value = to;
			self->adjacent[from].first->next = NULL;
		}
		// Sinon, on parcourt la liste
		else {
			// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
			if (self->adjacent[from].first->value != to && to != from) {
				if (self->adjacent[from].first->value > to) {
					size_t to_tmp = self->adjacent[from].first->value;
					self->adjacent[from].first->value = to;
					graph_add_node_adjacent(self->adjacent[from].first, to_tmp);
				}
				else {
					graph_add_node_adjacent(self->adjacent[from].first, to);
				}
			}
		}
	}
}

void graph_add_node_adjacent(struct list_node *self, size_t to) {
	// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
	if (self->value != to) {
		if (self->next == NULL) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = NULL;
			self->next = l;
		}
		else if (self->value < to && self->next->value < to) {
			graph_add_node_adjacent(self->next, to);
		}
		else if (self->value < to && self->next->value > to) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = self->next;
			self->next = l;
		}
		else {
			graph_add_node_adjacent(self->next, to);
		}
	}
}

// Ajout d'un arc
void graph_add_arc(struct graph *self, size_t from, size_t to) {
	// On vérifie que la lettre fait bien partie de l'alphabet de l'automate
	if (to < self->state_count) {
		// Si il n'y a pas de transitions, initialisation de la liste chaînée
		if (self->arc[from].first == NULL) {
			self->arc[from].first =  malloc(sizeof(struct list_node));
			self->arc[from].first->value = to;
			self->arc[from].first->next = NULL;
		}
		// Sinon, on parcourt la liste
		else {
			// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
			if (self->arc[from].first->value != to) {
				if (self->arc[from].first->value > to) {
					size_t to_tmp = self->arc[from].first->value;
					self->arc[from].first->value = to;
					graph_add_node_arc(self->arc[from].first, to_tmp);
				}
				else {
					graph_add_node_arc(self->arc[from].first, to);
				}
			}
		}
	}
}

void graph_add_node_arc(struct list_node *self, size_t to) {
	// Si la valeur n'est pas déjà présente, on l'ajoute en conservant l'ordre
	if (self->value != to) {
		if (self->next == NULL) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = NULL;
			self->next = l;
		}
		else if (self->value < to && self->next->value < to) {
			graph_add_node_arc(self->next, to);
		}
		else if (self->value < to && self->next->value > to) {
			struct list_node *l = malloc(sizeof(struct list_node));
			l->value = to;
			l->next = self->next;
			self->next = l;
		}
		else {
			graph_add_node_arc(self->next, to);
		}
	}
}

// Fonction créant un graphe à partir d'un automate
void graph_create_from_fa(struct graph *self, const struct fa *fa, bool inverted) {
	// Initialisation
	self->state_count = fa->state_count;
	self->adjacent = malloc(sizeof(struct list)*fa->state_count);
	self->arc = malloc(sizeof(struct list)*fa->state_count);

	for (int i = 0; i < fa->state_count; ++i) {
		self->adjacent[i].first = NULL;
		self->arc[i].first = NULL;
	}

	// Mise en place des adjacents et des arcs, grâce aux listes de transitions
	for (int i = 0; i < fa->state_count; ++i) {
		for (int j = 0; j < fa->alpha_count; ++j) {
			struct list_node *l = fa->state_array[i][j].first;
			if (l != NULL) {
				// Première passe
				graph_add_adjacent(self, i, l->value);
				// Seconde passe
				graph_add_adjacent(self, l->value, i);
				// Mise en place des arcs en fonction de inverted
				if (inverted) {
					graph_add_arc(self, l->value, i);
				}
				else {
					graph_add_arc(self, i, l->value);
				}

				// Si transitions multiples
				while (l->next != NULL) {
					l = l->next;
					// Première passe
					graph_add_adjacent(self, i, l->value);
					// Seconde passe
					graph_add_adjacent(self, l->value, i);
					// Mise en place des arcs en fonction de inverted
					if (inverted) {
						graph_add_arc(self, l->value, i);
					}
					else {
						graph_add_arc(self, i, l->value);
					}
				}
			}
		}
	}

	// Mise en place des arcs
}

// Destruction d'un graphe
void graph_destroy(struct graph *self) {
	for(int i = 0; i < self->state_count; ++i) {
		// Libération de chaque liste contenu par le tableau
		fa_destroy_list(&self->adjacent[i]);
		fa_destroy_list(&self->arc[i]);
	}
	free(self->adjacent);
	free(self->arc);
}

// Affichage d'un graphe
void graph_pretty_print(const struct graph *self, FILE *out) {
	printf("\nAdjacent:\n");
	for (int i = 0; i < self->state_count; ++i) {
		printf("\tFor state %d:\t", i);
		if (self->adjacent[i].first != NULL) {
			struct list_node *l = self->adjacent[i].first;
			printf("%d ", l->value);
			while (l->next != NULL) {
				l = l->next;
				printf("%d ", l->value);
			}
		}
		printf("\n");
	}
	printf("\nArc:\n");
	for (int i = 0; i < self->state_count; ++i) {
		printf("\tFor state %d:\t", i);
		if (self->arc[i].first != NULL) {
			struct list_node *l = self->arc[i].first;
			printf("%d ", l->value);
			while (l->next != NULL) {
				l = l->next;
				printf("%d ", l->value);
			}
		}
		printf("\n");
	}
}

// Fonction vérifiant si un langage est vide
bool fa_is_language_empty(const struct fa *self) {
	// Vérification qu'il y a un nombre d'état suffisant ou qu'il y a des états initiaux et finaux
	if (self->state_count == 0 || self->array_final.value == NULL || self->array_init.value == NULL) {
		return true;
	}
	else {
		// Initilisation du tableau des états visités
		bool visited[self->state_count];
		for (int i = 0; i < self->state_count; ++i) {
			visited[i] = false;
		}

		// Création du graphe
		struct graph g;
		graph_create_from_fa(&g, self, false);
		// Parcours en profondeur du graphe en partant d'un état initial à la fois
		for (int j = 0; j < self->array_init.used; ++j) {
			graph_depth_first_search(&g, self->array_init.value[j], visited);
			// Après parcours, on vérifie si on a atteint un état final
			for (int i = 0; i < self->array_final.used; ++i) {
				// Si oui on détruit le graphe et on retourne faux
				if (visited[self->array_final.value[i]] == true) {
					graph_destroy(&g);
					return false;
				}
			}

			// Sinon on reset le tableau des états visités
			for (int i = 0; i < self->state_count; ++i) {
				visited[i] = false;
			}
		}

		// Si le langage est vide on détruit le graphe puis on retourne vrai
		graph_destroy(&g);
	}

	return true;
}

// Suppression des états non-accessibles (accessible s'il existe un chemin partant d'un état initial et allant jusqu'à l'état voulu)
void fa_remove_non_accessible_states(struct fa *self) {
	struct graph g;
	graph_create_from_fa(&g, self, false);

	// Initialisation du tableau des états visités
	bool visited[self->state_count];
	for (int i = 0; i < self->state_count; ++i) {
		visited[i] = false;
	}

	// On part de chaque état initial et on essaye d'atteindre chaque état
	for (int i = 0; i < self->array_init.used; ++i) {
		for (int j = 0; j < self->state_count; ++j) {
				if (!visited[j]) {
					visited[j] = graph_has_path(&g, self->array_init.value[i], j);
				}
		}
	}

	int count = 0;
	// Si un état n'a pas été visité on le supprime
	for (int i = 0; i < self->state_count; ++i) {
		if (!visited[i]) {
			fa_remove_state(self, i-count);
			++count;
		}
	}

	graph_destroy(&g);
}

// Suppression des états non-co-accessibles (coaccessible s'il existe un chemin partant de l'état voulu et allant jusqu'à un état final)
void fa_remove_non_co_accessible_states(struct fa *self) {
	struct graph g;
	graph_create_from_fa(&g, self, false);

	// Initialisation du tableau des états visités
	bool visited[self->state_count];
	for (int i = 0; i < self->state_count; ++i) {
		visited[i] = false;
	}

	// On part de chaque état et on essaye d'atteindre un état final
	for (int i = 0; i < self->state_count; ++i) {
		for (int j = 0; j < self->array_final.used; ++j) {
				if (!visited[i]) {
					visited[i] = graph_has_path(&g, i, self->array_final.value[j]);
				}
		}
	}

	int count = 0;
	// Si un état n'a pas été visité on le supprime
	for (int i = 0; i < self->state_count; ++i) {
		if (!visited[i]) {
			fa_remove_state(self, i-count);
			++count;
		}
	}

	graph_destroy(&g);
}

// Fonction vérifiant si un état est initial ou non
bool is_initial(const struct fa *self, int state) {
	for (int i = 0; i < self->array_init.used; ++i) {
		if (state == self->array_init.value[i]) {
			return true;
		}
	}
	return false;
}

// Fonction vérifiant si un état est final ou non
bool is_final(const struct fa *self, int state) {
	for (int i = 0; i < self->array_final.used; ++i) {
		if (state == self->array_final.value[i]) {
			return true;
		}
	}
	return false;
}

/* Produit de deux automates
Soit P = hR, A, F, J, Ui l’automate défini par :
– les états de P sont des paires d’états formées d’un état de A et d’un état de A′
– l’ensemble J des états initiaux est formé des paires (p, p′), où p est initial dans A et p′ est initial dans A′
– pour tout état (p, p′), pour toute lettre a, s’il y a une transition (p, a, q) dans A et une transition (p′, a, q′) dans A′, il y a un état (q, q′) dans P et une transition de (p, p′) à (q, q′) étiquetée par a
– un état (p, p′) est terminal si et seulement si les états p et p′ sont terminaux
*/
void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs) {
	// Compteur d'états de res
	int counter = 0;

	// Création de l'automate, en prenant la taille d'alphabet la plus grande
	fa_create(self, lhs->alpha_count&rhs->alpha_count, lhs->state_count*rhs->state_count);

	counter = 0;
	// Pour tout état de lhs
	for (int i = 0; i < lhs->state_count; ++i) {
		// Pour tout état de rhs
		for (int j = 0; j < rhs->state_count; ++j) {
			// Si les deux états sont initiaux
			if (is_initial(lhs, i) && is_initial(rhs, j)) {
				fa_set_state_initial(self, counter);
			}
			// Si les deux états sont finaux
			else if (is_final(lhs, i) && is_final(rhs, j)) {
				fa_set_state_final(self, counter);
			}

			// Pour chaque lettre de l'alphabet
			for (int k = 0; k < self->alpha_count; ++k) {
				// On créé les transitions entre chaque états
				struct list_node *l1 = lhs->state_array[i][k].first;

				while (l1 != NULL) {
					struct list_node *l2 = rhs->state_array[j][k].first;

					while (l2 != NULL) {
						fa_add_transition(self, counter, 'a'+k, l1->value*rhs->state_count+l2->value);

						l2 = l2->next;
					}

					l1 = l1->next;
				}
			}

			++counter;
		}
	}

	fa_remove_non_accessible_states(self);
}

// Détermine si l'intersection entre deux automates est vide
bool fa_has_empty_intersection(const struct fa *lhs, const struct fa *rhs) {
	struct fa a;
	fa_create_product(&a, lhs, rhs);

	bool res = fa_is_language_empty(&a);

	fa_destroy(&a);

	return res;
}

// Fonction vérifiant qu'un ensemble d'états n'est pas déjà présents dans une liste d'ensembles d'états
bool fa_look_in_det_states(struct list *det_states, struct list_node *l, int nbStates) {
	/* Tableau de booléen représentant les états que l'on vérifie,
	un état à true n'est pas présent dans la liste d'ensembles,
	un état à false est présent dans la liste d'ensembles */
	bool res[nbStates];
	// Initialisation du tableau
	for (int i = 0; i < nbStates; ++i) {
		res[i] = false;
	}

	for (int i = 0; i < nbStates; ++i) {
		struct list_node *det = det_states[i].first;
		struct list_node *toAdd = l;

		while (det != NULL && toAdd != NULL) {
			// Les listes étant triées, on vérifie si deux valeurs à une même position sont différentes
			if (det->value != toAdd->value) {
				res[i] = true;
			}

			det = det->next;
			toAdd = toAdd->next;

			// Si on arrive à la fin d'une liste avant la fin de l'autre liste
			if ((det != NULL && toAdd == NULL)
					|| (det == NULL && toAdd != NULL)) {
				res[i] = true;
			}
		}
	}

	// Si on a trouvé un état présent dans la liste d'ensemble, on retourne faux
	for (int i = 0; i < nbStates; ++i) {
		if (res[i] == false) {
			return false;
		}
	}

	return true;
}

// Fonction ajoutant un ensemble d'états dans une liste d'ensemble d'états
void fa_add_to_det_states(struct list *det_states, struct list_node *l, int nbStates) {
	struct list_node *current = l;
	while (current != NULL) {
		fa_add_node_transition(det_states[nbStates].first, current->value);
		current = current->next;
	}
}

// Fonction ajoutant un état dans un automate déterministe
bool fa_add_deterministic_state(struct fa *self, const struct fa *nfa, struct list *det_states, struct list_node *l, int nbStates) {
	// Vérification si l'ensemble d'états est présent ou non dans la liste d'ensembles d'états
	bool addOk = fa_look_in_det_states(det_states, l, nbStates);

	// Si l'ensemble d'états n'est pas déjà présent
	if (addOk) {
		// Ajout de l'ensemble d'états à la liste d'ensemble d'états
		fa_add_to_det_states(det_states, l, nbStates);

		// Ajout des ensembles d'états au tableau de déterminisation
		struct list_node *current = det_states[nbStates].first;
		while (current != NULL) {
			for (int j = 0; j < nfa->alpha_count; ++j) {
				struct list_node *l = nfa->state_array[current->value][j].first;
				while (l != NULL) {
					fa_add_transition(self, nbStates, 'a'+j, l->value);
					l = l->next;
				}
			}

			current = current->next;
		}
	}

	// La fonction renvoie si un ajout a été fait ou non
	return addOk;
}

// Déterminisation d'un automate
void fa_create_deterministic(struct fa *self, const struct fa *nfa) {
	/* Pour répresenter le tableau de déterminisation, on utilise self->state_array,
	puis on effectue les bonnes correspondances à la fin pour obtenir l'automates
	determinisé, toujours dans self->state_array */

	// Variable contenant le nombre d'états maximum de l'automate déterminisé
	int n = pow(2, nfa->state_count);
	// Nombres d'états courant de l'automate déterminisé
	int nbStates = 0;

	// Allocation mémoire de l'automate déterminisé
	fa_create(self, nfa->alpha_count, n);

	// Initialisation du tableau de correspondance des états
	struct list *det_states = malloc(sizeof(struct list)*n);
	for (int i = 0; i < n; ++i) {
		det_states[i].first = malloc(sizeof(struct list_node));
		det_states[i].first->next = NULL;
		det_states[i].first->value = -1;
	}

	// Ajout des états initiaux
	for (int i = 0; i < nfa->array_init.used; ++i) {
		int current = nfa->array_init.value[i];
		det_states[i].first->value = current;

		fa_set_state_initial(self, current);

		for (int j = 0; j < nfa->alpha_count; ++j) {
			struct list_node *l = nfa->state_array[current][j].first;
			while (l != NULL) {
				fa_add_transition(self, current, 'a'+j, l->value);
				l = l->next;
			}
		}

		++nbStates;
	}

	// Ajout des états suivants
	bool run = true;
	int count = 0;
	while (run && count < n) {
		bool test[nfa->alpha_count];
		for (int i = 0; i < nfa->alpha_count; ++i) {
			test[i] = fa_add_deterministic_state(self, nfa, det_states, self->state_array[count][i].first, nbStates);
			if (test[i]) {
				++nbStates;
			}
			// run passe à faux si fa_add_deterministic_state retourne faux pour toutes les transitions
			run |= test[i];
		}
		++count;
	}

	/* Mise en place de la correspondance des états
	Pour cela, on regarde le contenu du tableau de déterminisation, puis on regarde
	dans la liste d'ensembles d'états la correspondance, et on change le contenu du tableau
	par l'indice correspondant, sur le même principe que fa_look_in_det_states */
	for (int i = 0; i < nbStates; ++i) {
		for (int j = 0; j < nfa->alpha_count; ++j) {
			bool res[nbStates];
			for (int k = 0; k < nbStates; ++k) {
				res[k] = true;
			}

			for (int k = 0; k < nbStates; ++k) {
				struct list_node *det = det_states[k].first;
				struct list_node *toAdd = self->state_array[i][j].first;

				while (toAdd != NULL && det != NULL) {
					if (det->value != toAdd->value) {
						res[k] = false;
						break;
					}

					det = det->next;
					toAdd = toAdd->next;

					if ((det == NULL && toAdd != NULL)
					 		|| (det != NULL && toAdd == NULL)) {
						res[k] = false;
						break;
					}
				}
			}

			// Passage des ensembles d'états au bon indice correspondants
			for (int k = 0; k < nbStates; ++k) {
				if (res[k]) {
					// Vérification de la présence d'un état final dans l'ensemble d'états
					for (int z = 0; z < nfa->array_final.used; ++z) {
						struct list_node *toAdd = self->state_array[i][j].first;
						while (toAdd != NULL) {
							// Ajout d'un état final si présence d'un dans l'ensemble d'états
							if (toAdd->value == nfa->array_final.value[z]) {
								fa_set_state_final(self, k);
							}

							toAdd = toAdd->next;
						}
					}

					// On détruit l'ensemble d'états puis on ajout le bon indice correspondant
 					fa_destroy_list(&self->state_array[i][j]);
					fa_add_transition(self, i, 'a'+j, k);
				}
			}

		}
	}

	// Suppression des états inutiles
	for (int i = n; i >= nbStates; --i) {
		fa_remove_state(self, i);
	}

	// Libération mémoire du tableau de correspondance des états
	for (int i = 0; i < n; ++i) {
		fa_destroy_list_node(det_states[i].first);
	}
	free(det_states);
}

/* Fonction déterminant si un langage accepté par un automates
est inclus dans un autre langage accepté par un autre automate, pour cela
on déterminise les deux automates entrés, puis on calcule le complémentaire
de B afin de calculer l'intersection de A et ^B, si celle-ci est vide,
alors A est inclus dans B */
bool fa_is_included(const struct fa *lhs, const struct fa *rhs) {
	struct fa *A = malloc(sizeof(struct fa));
	struct fa *B = malloc(sizeof(struct fa));

	// On crée les automates déterministes corrspondants
	fa_create_deterministic(A, lhs);
	fa_create_deterministic(B, rhs);

	// Création du complémentaire de B
	// On complète l'automate B
	fa_make_complete(B);

	// On inverse les états finaux et non-finaux
	bool is_final[B->state_count];
	for (int i = 0; i < B->state_count; ++i) {
		is_final[i] = false;
		for (int j = 0; j < B->array_final.used; ++j) {
			if (B->array_final.value[j] == i) {
				is_final[i] = true;
			}
		}
	}

	free(B->array_final.value);
	B->array_final.value = NULL;
	for (int i = 0; i < B->state_count; ++i) {
		if (!is_final[i]) {
			fa_set_state_final(B, i);
		}
	}

	// On calcule l'intersection entre l'automate A et le complémentaire de B
	bool res = fa_has_empty_intersection(A, B);

	// Libérations mémoire
	fa_destroy(A);
	fa_destroy(B);
	free(A);
	free(B);

	return res;
}
