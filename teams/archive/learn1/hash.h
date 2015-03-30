/*-------------------------------------------------------------------------

	hash.h

	(c) 1993 Tucker Balch

	Interface to hash table and linked-list objects.

-------------------------------------------------------------------------*/

#ifndef HASH_H
#define HASH_H


/*-----------------------------------------------

	Linked List Declarations

-----------------------------------------------*/	

#define KEY_TYPE double	/* Type for use as a key value in the list */

class	list_item
	{
	public:
		KEY_TYPE	key;
		list_item	*next;
	};


class	linked_list
	{
	list_item	*head;
	list_item	*current;

	public:
		linked_list();
		~linked_list();
		void	*find(KEY_TYPE key);
		add(list_item *item);
		remove(KEY_TYPE key); 
		list_item	*get_first();
		list_item	*get_next();
	};


/*-----------------------------------------------

	Hash Table Declarations

-----------------------------------------------*/	

#define HASH_TABLE_SIZE 6000	/* Size of table */

class	hash_table
	{
	linked_list	lists[HASH_TABLE_SIZE];
	int		current;

	public:
		hash_table();
		~hash_table();
		void	*find(KEY_TYPE key);
		add(list_item *item);
		remove(KEY_TYPE key); 
		list_item	*get_first();
		list_item	*get_next();
	};


/*-----------------------------------------------

	Macros

-----------------------------------------------*/	
#define \
        for_each(container, function) \
        { \
        list_item       *iterator; \
        iterator = container.get_first(); \
        while (iterator != NULL) \
                { \
                function; \
                iterator = container.get_next(); \
                } \
        }

#define \
        for_every(container, cond, function) \
        { \
        list_item       *iterator; \
        iterator = container.get_first(); \
        while (iterator != NULL) \
                { \
                if (cond) function; \
                iterator = container.get_next(); \
                } \
        }

#endif
