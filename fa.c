// BOISSON Romain - GUY Timothée

#include "fa.h"

/*
struct fa {
	size_t alpha_count;
	size_t state_count;
	struct state **state_array;
};
*/

void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self = malloc(sizeof(struct fa));
	self->alpha_count= alpha_count;
	self->state_count= state_count;
	fa_create_state_list(self);
	self->first_transition=NULL;
}

void fa_create_state_list(struct fa *self){
	self->state_array = malloc(self->state_count);
}

void fa_destroy_state_list(struct fa *self){
	for(int i=0;i < self->state_count;i++){
		states_destroy(&self->state_array[i]);
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
	self->state_array[state].is_initial = true;
}

void fa_set_state_final(struct fa *self, size_t state) {
	self->state_array[state].is_final = true;
}

void fa_add_transition(struct fa *self, size_t from, char alpha, size_t to) {
	
}

void fa_pretty_print(const struct fa *self, FILE *out) {

}

void fa_dot_print(const struct fa *self, FILE *out) {

}
