/*===========================================================================

	situation.cpp

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include <stdio.h>
#include "players.h"
#include "hash.h"
#include "situation.h"

/* this is a shared global hash table */
hash_table situations;

situation::pick_action()
{
double 	best_value = -999999;
int	best_action = 0;
int	i, m, r;

for(i=0; i<=BIGGEST_ACTION; i++)
	{
	if (estimated_value[i] > best_value)
		{
		best_action = i;
		best_value = estimated_value[i];
		}
	}

//m = ((rand()/256) % 10);
//if (m == 1) /* 10% of the time */
//	{
//	best_action = ((rand()/256 % (BIGGEST_ACTION + 1)));
//	}

return(best_action);
}

situation::situation(KEY_TYPE new_key, int local_area[9], int ball_direction)
{
int i;

key = new_key;
for(i=0; i<=BIGGEST_ACTION; i++)
	estimated_value[i] = 0;
estimated_value[ball_direction] = 1.0/LEARN_HORIZON;
}

situation::show()
{
printf("%f\n",key);
}

