// BOISSON Romain - GUY Timothée

#ifndef FA_H
#define FA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

// Structure représentant une liste chaînée
struct list {
	struct list_node *first;
};

struct list_node {
	int value;
	struct list_node *next;
};

// Structure représentant un tableau dynamique
struct dyn_tab {
	int *value;
	size_t used;
	size_t size;
};

// Structure représentant un automate
struct fa {
	size_t alpha_count; // Nombre de lettres de l'alphabet
	size_t state_count; // Nombre d'états
	struct list **state_array; // Tableau 2D états/alphabet
	struct dyn_tab array_init; // Tableau des états initiaux
	struct dyn_tab array_final; // Tableau des états finaux
};

// Structure représentant un graphe orienté
struct graph {
	size_t state_count; // Nombre d'états
	struct list *adjacent; // Tableau des listes d'adjacence des états
	struct list *arc; // Tableau des arcs de chaque état
};

// Création d'un automate
void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

// Création d'une liste d'états
void fa_create_state_list(struct fa *self);

// Destruction d'un automate
void fa_destroy(struct fa *self);

// Destruction d'une liste d'états
void fa_destroy_state_list(struct fa *self);

// Destruction d'une liste de transitions
void fa_destroy_list_node(struct list_node *self);
void fa_destroy_list(struct list *self);

// Passage d'un état à état initial
void fa_set_state_initial(struct fa *self, size_t state);

// Passage d'un état à état final
void fa_set_state_final(struct fa *self, size_t state);

// Ajout d'une transition
void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to);
void fa_add_node_transition(struct list_node *self, size_t to);

// Affichage d'un automate
void fa_pretty_print(const struct fa *self, FILE *out);
void fa_dot_print(const struct fa *self, FILE *out);

// Suppression d'une transition
void fa_remove_transition(struct fa *self, size_t from, char alpha, size_t to);
void fa_remove_node_transition(struct list_node *self, size_t to);

// Suppression d'un état
void fa_remove_state(struct fa *self, size_t state);

// Compteur de transitions
size_t fa_count_transitions(const struct fa *self);

// Fonction établissant si l'automate est déterministe
bool fa_is_deterministic(const struct fa *self);

// Fonction établissant si l'automate est complet
bool fa_is_complete(const struct fa *self);

// Complétion d'un automate
void fa_make_complete(struct fa *self);

// Fonction de parcours en profondeur d'un graphe
void graph_depth_first_search(const struct graph *self, size_t state, bool *visited);

bool graph_has_path_with_prev(const struct graph *self, size_t from, size_t to, size_t prev);
// Fonction déterminant si un chemin existe entre deux états
bool graph_has_path(const struct graph *self, size_t from, size_t to);

// Ajout d'un adjacent
void graph_add_adjacent(struct graph *self, size_t from, size_t to);
void graph_add_node_adjacent(struct list_node *self, size_t to);

// Ajout d'un arc
void graph_add_arc(struct graph *self, size_t from, size_t to);
void graph_add_node_arc(struct list_node *self, size_t to);

// Fonction créant un graphe à partir d'un automate
void graph_create_from_fa(struct graph *self, const struct fa *fa, bool inverted);

// Destruction d'un graphe
void graph_destroy(struct graph *self);

// Affichage d'un graphe
void graph_pretty_print(const struct graph *self, FILE *out);

// Fonction vérifiant si un langage est vide
bool fa_is_language_empty(const struct fa *self);

// Suppression des états non-accessibles
void fa_remove_non_accessible_states(struct fa *self);

// Suppression des états non-co-accessibles
void fa_remove_non_co_accessible_states(struct fa *self);

// Fonction vérifiant si un état est initial ou non
bool is_initial(const struct fa *self, int state);

// Fonction vérifiant si un état est final ou non
bool is_final(const struct fa *self, int state);

// Produit de deux automates
void fa_create_product(struct fa *self, const struct fa *lhs, const struct fa *rhs);

// Détermine si l'intersection entre deux automates est vide
bool fa_has_empty_intersection(const struct fa *lhs, const struct fa *rhs);

// Fonction vérifiant qu'un ensemble d'états n'est pas déjà présents dans une liste d'ensembles d'états
bool fa_look_in_det_states(struct list *det_states,  struct list_node *l, int nbStates);

// Fonction ajoutant un ensemble d'états dans une liste d'ensemble d'états
void fa_add_to_det_states(struct list *det_states, struct list_node *l, int nbStates);

// Fonction ajoutant un état dans un automate déterministe
bool fa_add_deterministic_state(struct fa *self, const struct fa *nfa, struct list *det_states, struct list_node *l, int nbStates);

// Déterminisation d'un automate
void fa_create_deterministic(struct fa *self, const struct fa *nfa);

/* Fonction déterminant si un langage accepté par un automates
est inclus dans un autre langage accepté par un autre automate, pour cela
on déterminise les deux automates entrés, puis on calcule le complémentaire
de B afin de calculer l'intersection de A et ^B, si celle-ci est vide,
alors A est inclus dans B */
bool fa_is_included(const struct fa *lhs, const struct fa *rhs);

#ifdef __cplusplus
}
#endif

#endif
