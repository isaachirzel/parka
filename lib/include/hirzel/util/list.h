// Error if no type declared
#ifndef HIRZEL_UTIL_LIST_T
#error An element type must be defined for container
#endif

// Util macros
#define CONCAT(a, b) a##b
#define LSTR(s) #s
#define STR(s) LSTR(s)

// Type agnostic macros
#define HXL_BASE_NAME(type) 	CONCAT(hxlist_, type)
#define HXL_STRUCT_NAME(base)	struct base
#define HXL_TYPEDEF_NAME(base)	CONCAT(base, _t)

// Convenient macro aliases
#define HXL_BASE				HXL_BASE_NAME(HIRZEL_UTIL_LIST_T)
#define HXL_TYPE				HIRZEL_UTIL_LIST_T
#define HXL_STRUCT				HXL_STRUCT_NAME(HXL_BASE)
#define HXL_TYPEDEF				HXL_TYPEDEF_NAME(HXL_BASE)

#define HXL_FUNC_BASE(base, postfix) CONCAT(base, postfix)
#define HXL_FUNC(name) HXL_FUNC_BASE(HXL_BASE, _##name)

// Declarations
#ifndef HIRZEL_UTIL_LIST_H
#define HIRZEL_UITL_LIST_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef HXL_STRUCT
{
	size_t len; 
	HXL_TYPE *data;
} HXL_TYPEDEF;


/**
 * @brief	Allocates instance of hxlist
 * 
 * The data is dynamically allocated and the list should be
 * freed with hxlist_destory
 * 
 * @return	pointer to list
 */
extern HXL_STRUCT *HXL_FUNC(create)();


/**
 * @brief	Frees memory used by list instance
 * 
 * @param	list	hxlist pointer
 */
extern void HXL_FUNC(destroy)(HXL_STRUCT *list);


/**
 * @brief	Pushes item to end of list.
 * 
 * @param	list	hxlist pointer
 * @param	item	element to add to list
 * 
 * @return	true on success, false on failure
 */
extern bool HXL_FUNC(push)(HXL_STRUCT *list, HXL_TYPE item);


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
extern HXL_TYPE HXL_FUNC(at)(HXL_STRUCT *list, size_t i);


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

extern bool HXL_FUNC(pop)(HXL_STRUCT* list);
extern bool HXL_FUNC(insert)(HXL_STRUCT *list, size_t pos, HXL_TYPE item);
extern bool HXL_FUNC(pushf)(HXL_STRUCT *list, HXL_TYPE item);
extern bool HXL_FUNC(erase)(HXL_STRUCT *list, size_t pos);
extern bool HXL_FUNC(popf)(HXL_STRUCT *list);
extern bool HXL_FUNC(resize)(HXL_STRUCT *list, size_t new_size);
extern bool HXL_FUNC(swap)(HXL_STRUCT *list, size_t a, size_t b);
extern HXL_TYPE *HXL_FUNC(atr)(HXL_STRUCT *list, size_t i);
extern bool HXL_FUNC(put)(HXL_STRUCT *list, size_t i, HXL_TYPE val);
extern bool HXL_FUNC(putr)(HXL_STRUCT *list, size_t i, HXL_TYPE *ref);

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
#define hxlist_get(list, i) (list->data[i])


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
#define hxlist_getr(list, i) (list->data + i)

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
#define hxlist_set(list, i, val) (list->data[i] = val)

#define hxlist_setr(list, i, ref) (list->data[i] = *ref)

/*******************************
 * OTHER MACROS TO DOCUMENT
 ******************************/

#define hxlist_front(list) (list->data[0])
#define hxlist_back(list) (list->data[list->len - 1])
#define hxlist_is_empty(list) (list->len == 0)
#define hxlist_size(list) (list->len)
#define hxlist_clear(list) { list->len = 0; free(list->data); list->data = NULL; }

#endif // HIRZEL_UITL_LIST_H

// Definitions
#ifdef HIRZEL_UTIL_LIST_I
#undef HIRZEL_UTIL_LIST_I

// CREATE
HXL_STRUCT *HXL_FUNC(create)()
{
	// allocate buffer
	HXL_STRUCT *out = (HXL_STRUCT*)malloc(sizeof(HXL_STRUCT));
	// check for failure
	if (!out) return NULL;
	// preinitialize array so it can be resized/ destroy won't fail
	out->data = NULL;
	// initialize as empty
	out->len = 0;

	return out;
}

// DESTROY
void HXL_FUNC(destroy)(HXL_STRUCT *list)
{
	free(list->data);
	free(list);
}

// PUSH
bool HXL_FUNC(push)(HXL_STRUCT *list, HXL_TYPE item)
{
	// calculate current isze of buffer in bytes
	size_t size = list->len * sizeof(HXL_TYPE);
	// allocate size + 1
	HXL_TYPE *tmp = (HXL_TYPE*)realloc(list->data, size + sizeof(HXL_TYPE));
	// check for failure
	if (!tmp) return false;
	// repoint buffer
	list->data = tmp;
	// put new item at end
	list->data[list->len] = item;
	// increment size
	list->len += 1;
	// success
	return true;
}

// POP
bool HXL_FUNC(pop)(HXL_STRUCT* list)
{
	if (list->len == 0) return false;
	HXL_TYPE *tmp = realloc(list->data, (list->len - 1)	* sizeof(HXL_TYPE));
	if (!tmp) return false;
	list->data = tmp;
	list->len -= 1;
	return true;
}

// INSERT
bool HXL_FUNC(insert)(HXL_STRUCT *list, size_t pos, HXL_TYPE item)
{
	// bounds check
	if (pos > list->len) return false;

	// allocate new buffer
	HXL_TYPE *tmp = (HXL_TYPE*)malloc((list->len + 1) * sizeof(HXL_STRUCT));
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
bool HXL_FUNC(pushf)(HXL_STRUCT *list, HXL_TYPE item)
{
	// allocating new buffer
	HXL_TYPE *tmp = (HXL_TYPE*)malloc((list->len + 1) * sizeof(HXL_STRUCT));
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
bool HXL_FUNC(erase)(HXL_STRUCT *list, size_t pos)
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
	HXL_TYPE *tmp = realloc(list->data, (list->len - 1) * sizeof(HXL_TYPE));
	if (!tmp) return false;
	list->data = tmp;
	list->len -= 1;

	return true;
}

// POPF
bool HXL_FUNC(popf)(HXL_STRUCT *list)
{
	// bounds checking
	if (list->len == 0) return false;

	list->len -= 1;

	// moving data forwards
	for (size_t i = 0; i < list->len; ++i)
	{
		list->data[i] = list->data[i + 1];
	}

	HXL_TYPE *tmp = realloc(list->data, list->len * sizeof(HXL_TYPE));
	if (!tmp) return false;

	list->data = tmp;

	return true;

}

// RESIZE
bool HXL_FUNC(resize)(HXL_STRUCT *list, size_t new_size)
{
	HXL_TYPE *tmp = realloc(list->data, new_size * sizeof(HXL_TYPE));
	if (!tmp) return false;
	list->data = tmp;
	list->len = new_size;
	return true;	
}

// SWAP
bool HXL_FUNC(swap)(HXL_STRUCT *list, size_t a, size_t b)
{
	// bounds checking
	if (a >= list->len || b >= list->len) return false;

	// swapping elements
	HXL_TYPE t;
	t = list->data[a];
	list->data[a] = list->data[b];
	list->data[b] = t;

	return true;
}

// AT
HXL_TYPE HXL_FUNC(at)(HXL_STRUCT *list, size_t i)
{
	if (i >= list->len)
	{
		HXL_TYPE t = {0};
		return t;
	}
	return list->data[i];
}

// ATR
HXL_TYPE *HXL_FUNC(atr)(HXL_STRUCT *list, size_t i)
{
	return (i >= list->len) ? NULL : (list->data + i);
}

// PUT
bool HXL_FUNC(put)(HXL_STRUCT *list, size_t i, HXL_TYPE val)
{
	if (i >= list->len) return false;
	list->data[i] = val;
	return true;
}

// PUTR
bool HXL_FUNC(putr)(HXL_STRUCT *list, size_t i, HXL_TYPE *ref)
{
	if (i >= list->len) return false;
	list->data[i] = *ref;
	return true;
}

#endif // HIRZEL_UTIL_LIST_I

// Preprocessor cleanup
#undef HXL_STRUCT
#undef HXL_TYPEDEF
#undef HXL_TYPE
#undef HXL_BASE
#undef HXL_NULL
#undef HIRZEL_UTIL_LIST_T
