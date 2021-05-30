// Error if no type declared
#ifndef HIRZEL_CONTAINER_ITEM
#error An element type must be defined for list
#endif

#ifndef HIRZEL_CONTAINER_NAME
#error A struct name must be defined for list
#endif

// Util macros
#define HXCONCAT(a, b) a##b
#define HXTYPEDEF_NAME(base) HXCONCAT(base, _t)
#define HXSTRUCT_NAME(base) struct base
#define HXSYM_NAME(base, postfix) HXCONCAT(base, postfix)

// Conventent macro aliases 
#define HXSTRUCT 	HXSTRUCT_NAME(HIRZEL_CONTAINER_NAME)
#define HXTYPEDEF 	HXTYPEDEF_NAME(HIRZEL_CONTAINER_NAME)
#define HXITEM		HIRZEL_CONTAINER_ITEM
#define HXSYM(name) HXSYM_NAME(HIRZEL_CONTAINER_NAME, _##name)


#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef HXSTRUCT
{
	size_t len; 
	HXITEM *data;
} HXTYPEDEF;


/**
 * @brief	Allocates instance of hxlist
 * 
 * The data is dynamically allocated and the list should be
 * freed with hxlist_destory
 * 
 * @return	pointer to list
 */
extern HXSTRUCT *HXSYM(create)();

/**
 * @brief	Frees memory used by list instance
 * 
 * @param	list	hxlist pointer
 */
extern void HXSYM(destroy)(HXSTRUCT *list);

/**
 * @brief	Pushes item to end of list.
 * 
 * @param	list	hxlist pointer
 * @param	item	element to add to list
 * 
 * @return	true on success, false on failure
 */
extern bool HXSYM(push)(HXSTRUCT *list, HXITEM item);

extern bool HXSYM(pushref)(HXSTRUCT *list, HXITEM *item);

/**
 * @brief	Gets item at a given index.
 * 
 * This function is bounds-checked and will return the desired element if i
 * is in bounds, but an uninitialized instance if it is not. 
 * 
 * @param	list	hxlist instance
 * @param	i		index of element
 * 
 * @return	Copy of item
 */
extern HXITEM HXSYM(at)(HXSTRUCT *list, size_t i);

/**
 * @brief	Gets reference to item at given index.
 * 
 * This function is bounds-checked and will return a valid reference if i is
 * in bounds, but NULL if it is not.
 * 
 * @param	list	hxlist instance
 * @param	i		index of element
 * 
 * @return	Reference to item or NULL
 */

extern bool HXSYM(pop)(HXSTRUCT* list);
extern bool HXSYM(insert)(HXSTRUCT *list, size_t pos, HXITEM item);
extern bool HXSYM(pushf)(HXSTRUCT *list, HXITEM item);
extern bool HXSYM(erase)(HXSTRUCT *list, size_t pos);
extern bool HXSYM(popf)(HXSTRUCT *list);
extern bool HXSYM(resize)(HXSTRUCT *list, size_t new_size);
extern bool HXSYM(swap)(HXSTRUCT *list, size_t a, size_t b);
extern HXITEM *HXSYM(atref)(HXSTRUCT *list, size_t i);
extern bool HXSYM(put)(HXSTRUCT *list, size_t i, HXITEM item);
extern bool HXSYM(putref)(HXSTRUCT *list, size_t i, HXITEM *ref);
extern void HXSYM(setref)(HXSTRUCT *list, size_t i, HXITEM *ref);
extern HXITEM HXSYM(front)(HXSTRUCT *list);
extern HXITEM HXSYM(back)(HXSTRUCT *list);
extern bool HXSYM(empty)(HXSTRUCT *list);
extern void HXSYM(clear)(HXSTRUCT *list);

/**
 * @brief	Gets item at given position.
 * 
 * This function is implemented as a macro for efficiency, but is
 * not bounds-checked.
 * 
 * @param	list	hxlist instance
 * @param	i		index of element
 * 
 * @return	Copy of item
 */
extern HXITEM HXSYM(get)(HXSTRUCT *list, size_t i);


/**
 * @brief	Gets pointer to item at given position.
 * 
 * This function is implemented as a macro for efficiency, but is
 * not bounds-checked.
 * 
 * @param	list	hxlist (of any type) instance
 * @param	i		index of element
 * 
 * @return	Refence to item
 */
extern HXITEM *HXSYM(getref)(HXSTRUCT *list, size_t i);

/**
 * @brief	Sets item at given position.
 * 
 * This function is implemented as a macro for efficiency, but is
 * not bounds-checked
 * 
 * @param	list	hxlist (of any type) instance
 * @param	i		index of element
 * @param	val		new value to assign
 */
extern void HXSYM(set)(HXSTRUCT *list, size_t i, HXITEM item);


#ifdef HIRZEL_IMPLEMENT


// CREATE
HXSTRUCT *HXSYM(create)()
{
	// allocate buffer
	HXSTRUCT *out = (HXSTRUCT*)malloc(sizeof(HXSTRUCT));
	// check for failure
	if (!out) return NULL;
	// preinitialize array so it can be resized/ destroy won't fail
	out->data = NULL;
	// initialize as empty
	out->len = 0;

	return out;
}


// DESTROY
void HXSYM(destroy)(HXSTRUCT *list)
{
	free(list->data);
	free(list);
}


// PUSH REF
bool HXSYM(pushref)(HXSTRUCT *list, HXITEM *item)
{
	// calculate current isze of buffer in bytes
	size_t size = list->len * sizeof(HXITEM);
	// allocate size + 1
	HXITEM *tmp = (HXITEM*)realloc(list->data, size + sizeof(HXITEM));
	// check for failure
	if (!tmp) return false;
	// repoint buffer
	list->data = tmp;
	// put new item at end
	list->data[list->len] = *item;
	// increment size
	list->len += 1;
	// success
	return true;
}


// PUSH
bool HXSYM(push)(HXSTRUCT *list, HXITEM item)
{
	return HXSYM(pushref)(list, &item);
}


// POP
bool HXSYM(pop)(HXSTRUCT* list)
{
	if (list->len == 0) return false;
	HXITEM *tmp = realloc(list->data, (list->len - 1)	* sizeof(HXITEM));
	if (!tmp) return false;
	list->data = tmp;
	list->len -= 1;
	return true;
}


// INSERT
bool HXSYM(insert)(HXSTRUCT *list, size_t pos, HXITEM item)
{
	// bounds check
	if (pos > list->len) return false;

	// allocate new buffer
	HXITEM *tmp = (HXITEM*)malloc((list->len + 1) * sizeof(HXSTRUCT));
	if (!tmp) return false;

	// copy over data before new pos
	for (size_t i = 0; i < pos; ++i)
	{
		tmp[i] = list->data[i];
	}

	// insert new element
	tmp[pos] = item;

	// copying over latter portion of data
	for (size_t i = pos; i < list->len; ++i)
	{
		tmp[i + 1] = list->data[i];
	}

	// freeing old buffer
	free(list->data);

	// repointing list data
	list->data = tmp;

	// incrementing size
	list->len += 1;

	return true;
}


// PUSHF
bool HXSYM(pushf)(HXSTRUCT *list, HXITEM item)
{
	// allocating new buffer
	HXITEM *tmp = (HXITEM*)malloc((list->len + 1) * sizeof(HXSTRUCT));
	if (!tmp) return false;

	tmp[0] = item;

	for (size_t i = 0; i < list->len; ++i)
	{
		tmp[i + 1] = list->data[i];
	}

	// freeing old buffer and repointing
	free(list->data);
	list->data = tmp;

	list->len += 1;
	return true;
}


// ERASE
bool HXSYM(erase)(HXSTRUCT *list, size_t pos)
{
	// bounds check
	if (pos > list->len) return false;

	// copying over data passed pos
	size_t oi = pos;
	for (size_t i = pos + 1; i < list->len; ++i)
	{
		list->data[oi] = list->data[i];
	}

	// resizing buffer
	HXITEM *tmp = realloc(list->data, (list->len - 1) * sizeof(HXITEM));
	if (!tmp) return false;
	list->data = tmp;
	list->len -= 1;

	return true;
}


// POPF
bool HXSYM(popf)(HXSTRUCT *list)
{
	// bounds checking
	if (list->len == 0) return false;

	list->len -= 1;

	// moving data forwards
	for (size_t i = 0; i < list->len; ++i)
	{
		list->data[i] = list->data[i + 1];
	}

	HXITEM *tmp = realloc(list->data, list->len * sizeof(HXITEM));
	if (!tmp) return false;

	list->data = tmp;

	return true;

}


// RESIZE
bool HXSYM(resize)(HXSTRUCT *list, size_t new_size)
{
	HXITEM *tmp = realloc(list->data, new_size * sizeof(HXITEM));
	if (!tmp) return false;
	list->data = tmp;
	list->len = new_size;
	return true;	
}


// SWAP
bool HXSYM(swap)(HXSTRUCT *list, size_t a, size_t b)
{
	// bounds checking
	if (a >= list->len || b >= list->len) return false;

	// swapping elements
	HXITEM t;
	t = list->data[a];
	list->data[a] = list->data[b];
	list->data[b] = t;

	return true;
}


// GET
HXITEM HXSYM(get)(HXSTRUCT *list, size_t i)
{
	return list->data[i];
}


// GETR
HXITEM *HXSYM(getref)(HXSTRUCT *list, size_t i)
{
	return list->data + i;
}


// AT
HXITEM HXSYM(at)(HXSTRUCT *list, size_t i)
{
	if (i >= list->len)
	{
		HXITEM t = {0};
		return t;
	}
	return list->data[i];
}


// ATR
HXITEM *HXSYM(atref)(HXSTRUCT *list, size_t i)
{
	return (i >= list->len) ? NULL : (list->data + i);
}


// SET
void HXSYM(set)(HXSTRUCT *list, size_t i, HXITEM item)
{
	list->data[i] = item;
}


// SETR
void HXSYM(setref)(HXSTRUCT *list, size_t i, HXITEM *ref)
{
	list->data[i] = *ref;
}


// PUT
bool HXSYM(put)(HXSTRUCT *list, size_t i, HXITEM val)
{
	if (i >= list->len) return false;
	list->data[i] = val;
	return true;
}


// PUTR
bool HXSYM(putref)(HXSTRUCT *list, size_t i, HXITEM *ref)
{
	if (i >= list->len) return false;
	list->data[i] = *ref;
	return true;
}


// BACK
HXITEM HXSYM(back)(HXSTRUCT *list)
{
	return list->data[list->len - 1];
}


// FRONT
HXITEM HXSYM(front)(HXSTRUCT *list)
{
	return *(list->data);
}


// IS EMPTY
bool HXSYM(empty)(HXSTRUCT *list)
{
	return list->len == 0;
}


// CLEAR
void HXSYM(clear)(HXSTRUCT *list)
{
	list->len = 0;
	free(list->data);
	list->data = NULL;
}


#endif // HIRZEL_IMPLEMENT

// Preprocessor cleanup
#undef HIRZEL_CONTAINER_ITEM
#undef HIRZEL_CONTAINER_NAME
#undef HXCONCAT
#undef HXTYPEDEF_NAME
#undef HXSTRUCT_NAME
#undef HXSYM_NAME
#undef HXSTRUCT
#undef HXTYPEDEF
#undef HXITEM
#undef HXSYM
