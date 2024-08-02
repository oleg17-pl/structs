#ifndef LIST_H
#define LIST_H

typedef int listtype_t;

typedef struct list_el {
	listtype_t value;
	struct list_el *prev, *next;
} list_el_t;

typedef struct list {
	list_el_t *first;
} list_t;

#define LIST_PARAM list_t *list
#define CONST_LIST_PARAM const list_t *const list

char l_empty(CONST_LIST_PARAM);
size_t l_size(CONST_LIST_PARAM);

list_el_t *l_begin(CONST_LIST_PARAM);
list_el_t *l_end(CONST_LIST_PARAM);
list_el_t *l_at(CONST_LIST_PARAM, size_t index);
listtype_t l_front(CONST_LIST_PARAM);
listtype_t l_back(CONST_LIST_PARAM);
listtype_t l_value(const list_el_t *const el);

void l_insert(LIST_PARAM, list_el_t *const el, listtype_t val);
void l_push_back(LIST_PARAM, listtype_t val);
void l_push_front(LIST_PARAM, listtype_t val);
void l_erase(LIST_PARAM, list_el_t *el);
void l_pop_back(LIST_PARAM);
void l_pop_front(LIST_PARAM);

void l_swap(LIST_PARAM, list_el_t *const el1, list_el_t *const el2);

list_t l_create(void);
void l_clear(LIST_PARAM);
void l_print(CONST_LIST_PARAM);

#endif // !LIST_H