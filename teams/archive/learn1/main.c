/*===========================================================================

	learn1.c

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include <stdio.h>
#include "players.h"
#include "hash.h"
#include "situation.h"

double	UN(states)[STATE_MEM];
int	UN(actions)[STATE_MEM];
int	UN(state_count) = 0;

void UN(read_memory)();
void UN(save_memory)();

KEY_TYPE UN(encode_situation)(int local_area[9], int ball_direction)
{
int	i,j,quit;
KEY_TYPE	r;

i = 0;
r = 0.0;
for(i=0; i<9; i++)
	{
	r = r * BIGGEST_SIT;
	r = r + (local_area[i]);
	}
r = r * 10;
r = r + ball_direction;
return(r);
}

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
{
KEY_TYPE encoded_situation;
situation	*found_it;
situation	*f;
int		best_action;

encoded_situation = UN(encode_situation)(local_area,ball_direction);
found_it = (situation *)situations.find(encoded_situation);

if (found_it==NULL)
	{
	found_it = new situation(encoded_situation, local_area, ball_direction);
	situations.add((situation *)found_it);
	}

best_action = found_it->pick_action();

UN(states)[UN(state_count) % STATE_MEM] = encoded_situation;
UN(actions)[UN(state_count) % STATE_MEM] = best_action;
UN(state_count)++;

return(best_action);
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as player1
 */
return(UN(player1)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as player1
 */
return(UN(player1)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int UN(player4)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as player1
 */
return(UN(player1)(local_area, ball_direction, x, y));
}

/*-----------------------------------------------------

	team_name()

	Every team must have a name.  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *UN(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = "Lazy Learners       \0";
return(s);
}

/*-----------------------------------------------------

	initialize_game()

	This function is called only once per
	game, before play begins.  You can leave it
	empty, or put code here to initialize your
	variables, etc.

-----------------------------------------------------*/
void UN(initialize_game)()
{
UN(read_memory)();
}

/*-----------------------------------------------------

	initialize_point()

	This function is called once per point, just
	before play begins for that point.
	You can leave it empty, or put code here to initialize 
	your variables, etc.

-----------------------------------------------------*/
void UN(initialize_point)()
{
}

/*-----------------------------------------------------

	lost_point()

	If your team loses a point, this function is
	called, otherwise, if you win the point, won_point()
	is called.  You can leave it empty, or put code here 
	for negative re-inforcement, etc.

-----------------------------------------------------*/
void UN(lost_point)()
{
situation	*found_it;
int		i;
double		decay = -(1.0/LEARN_HORIZON);
double		reward = -1.0;

if (UN(state_count) > STATE_MEM)
	UN(state_count) = (UN(state_count) % STATE_MEM);

for(i=(UN(state_count)-1); (i >= 0) && (i >= (UN(state_count) - LEARN_HORIZON)); i--)
	{
	found_it = (situation *)situations.find(UN(states)[i]);
	found_it->estimated_value[UN(actions)[i]] += reward;
	reward = reward - decay;
	}
UN(state_count) = 0;
}

/*-----------------------------------------------------

	won_point()

	If your team wins a point, this function is
	called, otherwise, if you lose the point, lost_point()
	is called.  You can leave it empty, or put code here 
	for positive re-inforcement, etc.

-----------------------------------------------------*/
void UN(won_point)()
{
situation	*found_it;
int		i;
double		decay =  (1.0/LEARN_HORIZON);
double		reward =  1;

if (UN(state_count) > STATE_MEM)
	UN(state_count) = (UN(state_count) % STATE_MEM);

for(i=(UN(state_count)-1); (i >= 0) && (i >= (UN(state_count) - LEARN_HORIZON)); i--)
	{
	found_it = (situation *)situations.find(UN(states)[i]);
	found_it->estimated_value[UN(actions)[i]] += reward;
	reward = reward - decay;
	}
UN(state_count) = 0;
}

/*-----------------------------------------------------

	game_over()

	This function is called once at the end of
	the match.  You can leave it empty, or put code 
	here to save things to a file, etc.

-----------------------------------------------------*/
void UN(game_over)()
{
UN(save_memory)();
}

void UN(save_memory)()
{
FILE	*save_to;
KEY_TYPE index;
int	r, i;
situation	*found_it;

save_to = fopen("./teams/learn1/learningset.dat","w");

if (save_to!= NULL)
	{
	found_it = (situation *)situations.get_first();
	while (found_it != NULL)
		{
		fprintf(save_to, "%.0f ", found_it->key);
		for(i = 0; i<=BIGGEST_ACTION; i++)
			fprintf(save_to, "%f ", found_it->estimated_value[i]);
		fprintf(save_to, "\n");
		found_it = (situation *)situations.get_next();
		}
	}
fclose(save_to);
}

void UN(read_memory)()
{
FILE	*previous;
KEY_TYPE index;
int	dummy_local_area[9], dummy_ball_direction;
int	r, i;
situation	*found_it;
double	value;

dummy_ball_direction = 0;
for(i=0; i<9; i++)
	dummy_local_area[i] = 0;

previous = fopen("./teams/learn1/learningset.dat","r");

if (previous!= NULL)
	r = fscanf(previous, "%lf", &index);
else
	r = EOF;

while (r != EOF)
	{
	found_it = (situation *)situations.find(index);

	if (found_it == NULL)
		{
		found_it = new situation(index, dummy_local_area, dummy_ball_direction);
		situations.add((situation *)found_it);
		}
	for(i = 0; i<=BIGGEST_ACTION; i++)
		{
		fscanf(previous, "%lf", &value);
		found_it->estimated_value[i] = value;
		}
		
	r = fscanf(previous, "%lf", &index);
	}
fclose(previous);
}
