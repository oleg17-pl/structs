#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef int vectype_t;

typedef struct vector {
	vectype_t *data;
	size_t size, reserved;
} vector_t;

#define VECTOR_PARAM vector_t *vec
#define CONST_VECTOR_PARAM const vector_t *const vec

vector_t v_create(void);
void v_reserve(VECTOR_PARAM, const size_t val);
void v_print(CONST_VECTOR_PARAM);
void v_push_back(VECTOR_PARAM, const vectype_t val);
void v_pop_back(VECTOR_PARAM);

#endif // !VECTOR_H
 