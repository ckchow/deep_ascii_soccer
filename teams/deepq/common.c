/*===========================================================================

	common.c

	Put routines in here that don't need unique names.  You might
	want to share these routines if your team is playing against
	itself.  You may not need to put anything in this file.

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include "players.h"

void dummyrandomname()
{
}

int contains(int* neighborhood, int object)
{
	for (int i = 0; i < 9; i++)
	{
		if (neighborhood[i] == object)
			return true;
	}
	return false;
}
