/*===========================================================================

	Wrapper team that stores sense information to global variables and retrieves
	actions from a global variable.

	Chris Chow

===========================================================================*/
#include <stdlib.h>
#include "players.h"
#include "soccer.h"

// these are all magnitudes of loss or gain, +/- correctly when doing reinforcement
const double point_reward = 10.0;
const double point_penalty = 10.0;

const double game_reward = 100.0;
const double game_penalty = 100.0;

const double walk_penalty = 1.0;
const double walk_diagonal_penalty = 0.5;
const double kick_penalty = 5.0; // kicking is risky!!!

const double posession_reward = 5.0;

const double ball_seek_reward = 1.0;

q_side_t q_side = Q_EAST;

/*forward ref*/
int unique_name(random_heading)();
int unique_name(learned_action)(int obstacles[9], int ball_direction, int x, int y, int player_index);

extern int contains(int*, int);

/*-----------------------------------------------------

	team_name()

	Every team must have a name!  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *unique_name(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = "wild dogs           \0";
return(s);
}

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int unique_name(player1)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(learned_action)(obstacles, ball_direction, x, y, 0));
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int unique_name(player2)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(learned_action)(obstacles, ball_direction, x, y, 1));
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int unique_name(player3)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(learned_action)(obstacles, ball_direction, x, y, 2));
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int unique_name(player4)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(learned_action)(obstacles, ball_direction, x, y, 3));
}

int unique_name(learned_action)(int obstacles[9], int ball_direction, int x, int y, int player_index)
{
	// save state
	team_state[player_index].x = x;
	team_state[player_index].y = y;

	for (int i = 0; i < 9; i++)
	{
		team_state[player_index].neighborhood[i] = obstacles[i];
	}

	team_state[player_index].ball_direction = ball_direction;

	int action = q_actions[player_index];

	switch(action)
	{
		case N:
		case S:
		case E:
		case W:
			reward -= walk_penalty;
			break;
		case NE:
		case NW:
		case SE:
		case SW:
			reward -= walk_diagonal_penalty;
			break;
		case KICK:
			reward -= kick_penalty;
			break;
	}

	if (action == ball_direction)
	{
		reward += ball_seek_reward;
	}

	if (contains(obstacles, BALL))
	{
		reward += posession_reward;
	}

	return q_actions[player_index];
}


int unique_name(random_heading)()
{
int	m;

m = ((rand()/256) % 8);
switch(m)
	{
	case 0: return(N); break;
	case 1: return(S); break;
	case 2: return(E); break;
	case 3: return(W); break;
	case 4: return(NW); break;
	case 5: return(NE); break;
	case 6: return(SW); break;
	case 7: return(SE); break;
	default: return(N); break;
	}
}

int unique_name(push_from_the_north)(int obstacles[9], int ball_direction)
{
int i;
switch(ball_direction)
	{
	case N: return(NW);
	case NE: return(N);
	case NW: return(NW);
	case W: return(NW);
	case E: return(N);
	case S: return(S);
	case SE: return(E);
	case SW: return(SW);
	default: return(N);
	}
}

int unique_name(push_from_the_east)(int obstacles[9], int ball_direction)
{
int i;
switch(ball_direction)
	{
	case N: return(NE);
	case NE: return(NE);
	case NW: return(N);
	case W: return(W);
	case E: return(unique_name(random_heading)());
	case S: return(SE);
	case SE: return(SE);
	case SW: return(S);
	default: return(N);
	}
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
	// the RL-Glue environment needs to know what stuff to calculate
	#ifdef EAST_TEAM
	q_side = Q_EAST;
	#endif 
	#ifdef WEST_TEAM
	q_side = Q_WEST;
	#endif
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
	reward -= point_penalty;
	return;
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
	reward += point_reward;
	return;
}

/*-----------------------------------------------------

        game_over()

        This function is called once at the end of
        the match.  You can leave it empty, or put code 
        here to save things to a file, etc.

-----------------------------------------------------*/
void UN(game_over)()
{
	double reinforcement = 0.0;
	switch (game_state)
	{
		case GAME_WESTWON:
			if (q_side == Q_WEST) 
			{
				reward += game_reward;
			}
			else
			{ 
				reward -= game_penalty;
			}
			break;
		case GAME_EASTWON:
			if (q_side == Q_EAST)
			{
				reward += game_reward;
			}
			else
			{
				reward -= game_penalty;
			}
			break;
		case GAME_RUNNING:
			// this should never happen
			break;
	}
}

