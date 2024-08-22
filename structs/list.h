#ifndef LIST_H
#define LIST_H

typedef int listtype_t;
typedef char(*compfunc_t)(listtype_t, listtype_t);

typedef struct lnode {
	listtype_t value;
	struct lnode *prev, *next;
} lnode_t;

typedef lnode_t *l_iterator_t;
typedef const l_iterator_t const_l_iterator_t;

typedef struct list {
	size_t size;
	l_iterator_t head;
} list_t;
typedef list_t *plist_t;

#define LIST_PARAM plist_t list
#define LIST_PARAM_2 plist_t list2
#define CONST_LIST_PARAM const plist_t const list
#define CONST_LIST_PARAM_2 const plist_t const list2

listtype_t l_iter_value(const_l_iterator_t iter);
l_iterator_t l_iter_next(const_l_iterator_t iter);
l_iterator_t l_iter_prev(const_l_iterator_t iter);

char l_empty(CONST_LIST_PARAM);
size_t l_size(CONST_LIST_PARAM);

l_iterator_t l_begin(CONST_LIST_PARAM);
l_iterator_t l_end(CONST_LIST_PARAM);
l_iterator_t l_at(CONST_LIST_PARAM, size_t index);
listtype_t l_front(CONST_LIST_PARAM);
listtype_t l_back(CONST_LIST_PARAM);

void l_insert(LIST_PARAM, l_iterator_t iter, listtype_t val);
void l_push_back(LIST_PARAM, listtype_t val);
void l_push_front(LIST_PARAM, listtype_t val);
void l_erase(LIST_PARAM, l_iterator_t iter);
void l_pop_back(LIST_PARAM);
void l_pop_front(LIST_PARAM);

void l_swapels(LIST_PARAM, l_iterator_t const iter1, l_iterator_t const iter2);
void l_swap(LIST_PARAM, LIST_PARAM_2);
void l_reverse(LIST_PARAM);
char l_isless(listtype_t a, listtype_t b);
char l_isgreater(listtype_t a, listtype_t b);
void l_sort(LIST_PARAM, compfunc_t compfunc);

plist_t l_create(void);
void l_clear(LIST_PARAM);
void l_free(LIST_PARAM);
void l_print(CONST_LIST_PARAM);

#endif // !LIST_H