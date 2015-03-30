/*===========================================================================

	comm1.c

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/
#include "players.h"
#include "stdlib.h"

/*forward refs*/
int unique_name(random_spread)(int obstacles[9], int ball_direction);
int unique_name(push_from_the_north)(int obstacles[9], int ball_direction);
int unique_name(push_from_the_east)(int obstacles[9], int ball_direction);
int unique_name(random_heading)();

static int unique_name(got_it) = -1;

/*-----------------------------------------------------

	team_name()

	Every team must have a name!  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *unique_name(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = "Commie Communicators\0";
return(s);
}

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int unique_name(player1)(int obstacles[9], int ball_direction, int x, int y)
{
if (obstacles[W] == BALL)
	{
	unique_name(got_it) = 1;
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
	}
if ((unique_name(got_it) == 1) && (obstacles[E] != BALL))
	unique_name(got_it) = -1;
if (unique_name(got_it) == -1)
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
else
	return(unique_name(random_spread)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int unique_name(player2)(int obstacles[9], int ball_direction, int x, int y)
{
if (obstacles[W] == BALL)
	{
	unique_name(got_it) = 2;
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
	}
if ((unique_name(got_it) == 2) && (obstacles[E] != BALL))
	unique_name(got_it) = -1;
if (unique_name(got_it) == -1)
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
else
	return(unique_name(random_spread)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int unique_name(player3)(int obstacles[9], int ball_direction, int x, int y)
{
if (obstacles[W] == BALL)
	{
	unique_name(got_it) = 3;
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
	}
if ((unique_name(got_it) == 3) && (obstacles[E] != BALL))
	unique_name(got_it) = -1;
if (unique_name(got_it) == -1)
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
else
	return(unique_name(random_spread)(obstacles, ball_direction));
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int unique_name(player4)(int obstacles[9], int ball_direction, int x, int y)
{
if (obstacles[W] == BALL)
	{
	unique_name(got_it) = 4;
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
	}
if ((unique_name(got_it) == 4) && (obstacles[E] != BALL))
	unique_name(got_it) = -1;
if (unique_name(got_it) == -1)
	return(unique_name(push_from_the_east)(obstacles, ball_direction));
else
	return(unique_name(random_spread)(obstacles, ball_direction));
}


int unique_name(random_spread)(int obstacles[9], int ball_direction)
{
if ((ball_direction == SE) || (ball_direction == NE))
	return(E);
if ((ball_direction == SW) || (ball_direction == NW))
	return(W);
return(unique_name(random_heading()));
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
void  UN(won_point)()
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


