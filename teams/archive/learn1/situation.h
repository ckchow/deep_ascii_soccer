/*===========================================================================

	situation.h

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include <stdio.h>
#include "players.h"
#include "hash.h"

#define STATE_MEM       1000
#define LEARN_HORIZON   400

extern hash_table situations;

class	situation : public list_item
	{
	public:
		double estimated_value[(BIGGEST_ACTION + 1)];
		situation(KEY_TYPE new_key, int local_area[9], int ball_direction);
		int pick_action();
		show();
	};
