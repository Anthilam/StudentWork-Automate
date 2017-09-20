// BOISSON Romain - GUY Timothée

#include "fa.h"

void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
	self = malloc(sizeof(struct fa));
}

void fa_destroy(struct fa *self) {

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
