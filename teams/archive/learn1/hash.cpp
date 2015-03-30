/*-------------------------------------------------------------------------

	hash.cpp

	(c) 1993 Tucker Balch

	Hash table and linked-list objects.

-------------------------------------------------------------------------*/

#include <stdlib.h>
#include <math.h>
#include <iostream.h>
#include "hash.h"


/*-------------------------------------------------------------------------

	Linked List Methods

-------------------------------------------------------------------------*/


/*-----------------------------------------------

	linked_list()

	Constructor.

-----------------------------------------------*/	

linked_list::linked_list()
{
head = NULL;
current = head;
}


/*-----------------------------------------------

	~linked_list()

	Destructor.

-----------------------------------------------*/	

linked_list::~linked_list()
{
}


/*-----------------------------------------------

	add()

	Add an item to the list.

-----------------------------------------------*/	

linked_list::add(list_item *item)
{
item->next = head;
head = item;
return(0);
}


/*-----------------------------------------------

	remove()

	Remove an item (no-destroy).

-----------------------------------------------*/	

linked_list::remove(KEY_TYPE key)
{
list_item	*i, *j;

i = head;

while ( i != NULL )
	{
	if (i->key == key)
		break;
	j = i;
	i = i->next;
	}

if ( i != NULL)
	{
	if ( i == head )
		{
		head = i->next;
		}
	else
		{
		j->next = i->next;
		}
	}
return(0);
}


/*-----------------------------------------------

	find()

	Find an item in the list.

 	If successful, returns pointer to item 
	matching key value, otherwise, returns NULL

-----------------------------------------------*/	

void *linked_list::find(KEY_TYPE key)
{
list_item	*i;

i = head;

while ( i != NULL )
	{
	if (i->key == key)
		break;
	i = i->next;
	}

return(i);
}


/*-----------------------------------------------

	get_first()

	Get first item in list.

	Returns pointer to first item in list.  NULL if list
	is empty.  Use this for iteration across a list.

-----------------------------------------------*/	

list_item	*linked_list::get_first()
{
current = head;
return(current);
}


/*-----------------------------------------------

	get_next()

	Get next item .

	Returns pointer to the next item on the list.
	Use get_first first.

-----------------------------------------------*/	

list_item *linked_list::get_next()
{
if ( current != NULL )
	current = current->next;
return(current);
}




/*-------------------------------------------------------------------------

	Hash Table Methods

-------------------------------------------------------------------------*/

/*-----------------------------------------------

	hash()

	Macro to determine a hash value.

-----------------------------------------------*/	

#define hash(i) ((int)(fmod(i,HASH_TABLE_SIZE)))


/*-----------------------------------------------

	hash_table()

	Constructor.

-----------------------------------------------*/	

hash_table::hash_table()
{
int	i;

current = 0;
}


/*-----------------------------------------------

	~hash_table()

	Destructor.

-----------------------------------------------*/	

hash_table::~hash_table()
{
int	i;

i = 0;
}


/*-----------------------------------------------

	add()

	Add an item to the table.

-----------------------------------------------*/	

hash_table::add(list_item *item)
{
int	i;

i = hash(item->key);
lists[i].add(item);
return(0);
}


/*-----------------------------------------------

	remove()

	Remove an item (no-destroy).

-----------------------------------------------*/	

hash_table::remove(KEY_TYPE key)
{
int i;

i = hash(key);
lists[i].remove(key);
return(0);
}


/*-----------------------------------------------

	find()

	Find an item in the table.

 	If successful, returns pointer to item 
	matching key value, otherwise, returns NULL

-----------------------------------------------*/	

void *hash_table::find(KEY_TYPE key)
{
int i;

i = hash(key);

return(lists[i].find(key));
}


/*-----------------------------------------------

	get_first()

	Get first item in table.

	Returns pointer to first item in table.  NULL if list
	is empty.  Use this for iteration across a hash table.

-----------------------------------------------*/	

list_item	*hash_table::get_first()
{
list_item	*j;

for(current = 0; current < HASH_TABLE_SIZE; current++)
	{
	j = lists[current].get_first();
	if (j != NULL)
		break;
	}
	
return(j);
}


/*-----------------------------------------------

	get_next()

	Get next item .

	Returns pointer to the next item on the list.
	Use get_first first.

-----------------------------------------------*/	

list_item *hash_table::get_next()
{
list_item	*j;

j = lists[current].get_next();

if (j == NULL)
	{
	current++;
	while (current < HASH_TABLE_SIZE) 
		{
		j = lists[current].get_first();
		if (j != NULL)
			break;
		current++;
		}
	}
	
return(j);
}

