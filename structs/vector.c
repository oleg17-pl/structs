#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

static void apply(VECTOR_PARAM) {
	vectype_t *new_data = malloc(sizeof(vectype_t) * vec->reserved);
	if (vec->data != NULL) {
		for (size_t i = 0; i < vec->size; i++) {
			new_data[i] = vec->data[i];
		}
		free(vec->data);
	}
	vec->data = new_data;
}

void v_reserve(VECTOR_PARAM, const size_t val) {
	vec->reserved = val;
	apply(vec);
}

vector_t v_create(void) {
	vector_t vec;
	vec.data = NULL;
	vec.size = 0;
	v_reserve(&vec, 1);
	return vec;
}

void v_print(CONST_VECTOR_PARAM) {
	printf("***\n");
	printf("vector info: size: %u; reserved: %u\n\n", vec->size, vec->reserved);
	for (size_t i = 0; i < vec->reserved; i++) {
		if (i < vec->size) {
			printf("index: %i; value: %i\n", i, vec->data[i]);
		}
		else {
			printf("index: %i; value: empty\n", i);
		}
	}
	printf("***\n\n");
}

void v_push_back(VECTOR_PARAM, const vectype_t val) {
	size_t new_size = vec->size + 1;
	if (vec->reserved < new_size) {
		v_reserve(vec, vec->reserved * 2);
	}
	vec->data[new_size - 1] = val;
	vec->size = new_size;
}

void v_pop_back(VECTOR_PARAM) {
	if (vec->size == 0) {
		return;
	}
	vec->size--;
	apply(vec);
}