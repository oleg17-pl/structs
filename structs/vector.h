#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef int vectype_t;

typedef struct vector {
	vectype_t *data;
	size_t size, reserved;
} vec_t;

typedef vec_t *pvec_t;

#define VECTOR_PARAM pvec_t vec
#define CONST_VECTOR_PARAM const pvec_t const vec

pvec_t v_create(void);
void v_reserve(VECTOR_PARAM, const size_t val);
void v_print(CONST_VECTOR_PARAM);
void v_push_back(VECTOR_PARAM, const vectype_t val);
void v_pop_back(VECTOR_PARAM);
void v_free(VECTOR_PARAM);

#endif // !VECTOR_H
 