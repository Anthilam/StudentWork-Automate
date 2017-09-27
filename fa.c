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

void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self = malloc(sizeof(struct fa));
	self->alpha_count = alpha_count;
	self->state_count = state_count;
	fa_create_state_list(self);
	self->array_init=NULL;
	self->array_final=NULL;
}

void fa_create_state_list(struct fa *self){
	self->state_array = malloc(sizeof(struct list)*self->state_count);
	for(int i=0; i< self->state_count;i++){
		self->state_array[i] = malloc (sizeof(struct list)*self->alpha_count);
	}
}

void fa_destroy_state_list(struct fa *self){
	for(int i = 0; i < self->state_count; i++){
		free(&self->state_array[i]);
	}
	free(self->state_array);
}

void fa_destroy_transition_list(struct fa *self){

}

void fa_destroy(struct fa *self) {
	fa_destroy_state_list(self);
	fa_destroy_transition_list(self);
	free(self);
}

void fa_set_state_initial(struct fa *self, size_t state) {
	
}

void fa_set_state_final(struct fa *self, size_t state) {
	
}

void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to) {

}

void fa_pretty_print(const struct fa *self, FILE *out) {

}

void fa_dot_print(const struct fa *self, FILE *out) {

}
