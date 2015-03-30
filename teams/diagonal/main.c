/*===========================================================================

	diagonal.c

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/
#include "players.h"
#include <stdlib.h>

/*forward refs*/
int unique_name(push_from_SE)(int obstacles[9], int ball_direction);
int unique_name(push_from_E)(int obstacles[9], int ball_direction);
int unique_name(push_from_NE)(int obstacles[9], int ball_direction);

/*-----------------------------------------------------

	team_name()

	Every team must have a name!  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *unique_name(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = "Diagonal Demons     \0";
return(s);
}

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int unique_name(player1)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(push_from_E)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int unique_name(player2)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(push_from_NE)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int unique_name(player3)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(push_from_SE)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int unique_name(player4)(int obstacles[9], int ball_direction, int x, int y)
{
return(unique_name(push_from_E)(obstacles, ball_direction));
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

int unique_name(push_from_SE)(int obstacles[9], int ball_direction)
{
if (obstacles[N] == BALL) return(E);
if (obstacles[NE] == BALL) return(E);
if (obstacles[E] == BALL) return(S);
if (obstacles[SE] == BALL) return(S);
if (obstacles[S] == BALL) return(E);
if (obstacles[SW] == BALL) return(E);
if (obstacles[W] == BALL) return(S);
if (obstacles[NW] == BALL) return(NW);
return(ball_direction);
}

int unique_name(push_from_E)(int obstacles[9], int ball_direction)
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

int unique_name(push_from_NE)(int obstacles[9], int ball_direction)
{
if (obstacles[N] == BALL) return(E);
if (obstacles[NE] == BALL) return(N);
if (obstacles[E] == BALL) return(N);
if (obstacles[SE] == BALL) return(E);
if (obstacles[S] == BALL) return(E);
if (obstacles[SW] == BALL) return(SW);
if (obstacles[W] == BALL) return(N);
if (obstacles[NW] == BALL) return(N);
return(ball_direction);
}



/*-----------------------------------------------------

	initialize_game()

	This function is called only once per
	game, before play begins.  You can leave it
	empty, or put code here to initialize your
	variables, etc.

-----------------------------------------------------*/
void  UN(initialize_game)()
{
}

/*-----------------------------------------------------

	initialize_point()

	This function is called once per point, just
	before play begins for that point.
	You can leave it empty, or put code here to initialize 
	your variables, etc.

-----------------------------------------------------*/
void  UN(initialize_point)()
{
}

/*-----------------------------------------------------

	lost_point()

	If your team loses a point, this function is
	called, otherwise, if you win the point, won_point()
	is called.  You can leave it empty, or put code here 
	for negative re-inforcement, etc.

-----------------------------------------------------*/
void  UN(lost_point)()
{
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
}

/*-----------------------------------------------------

        game_over()

        This function is called once at the end of
        the game.  You can leave it empty, or put code 
        here to save things to a file, etc.

-----------------------------------------------------*/
void UN(game_over)()
{
}


