/*===========================================================================

	eisenhauer2.c

	Everyone is the same, rather nominal player.  If the ball is 
	ahead of him (toward the goal), he pushes it that way.  Otherwise
	he tries to go toward (but stay behind) the ball.

	This version is slightly smarter than eisenhauer.c
	In particular: 
		it can kick
		it doesn't kick into walls (uses x value for that!)
		it tries to be a bit smarter about how it moves when 
		    it is away from the ball (in obscure ways)

	Greg Eisenhauer		eisen@cc.gatech.edu

===========================================================================*/
#include "players.h"

/*forward refs*/
int unique_name(nominal_player)(int player, int obstacles[9], 
				int ball_direction, int x, int y);
int unique_name(ball_ahead)(int obstacles[9]);
int unique_name(get_behind_it)(int obstacles[9], int ball_direction);

/* this 'got_it' variable is unused in this player. */
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
    s = "Socker Spaniels     \0";
    return(s);
}

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int unique_name(player1)(int obstacles[9], int ball_direction, int x, int y)
{
    return unique_name(nominal_player)(1, obstacles, ball_direction, x, y);
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int unique_name(player2)(int obstacles[9], int ball_direction, int x, int y)
{
    return unique_name(nominal_player)(2, obstacles, ball_direction, x, y);
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int unique_name(player3)(int obstacles[9], int ball_direction, int x, int y)
{
    return unique_name(nominal_player)(3, obstacles, ball_direction, x, y);
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int unique_name(player4)(int obstacles[9], int ball_direction, int x, int y)
{
    return unique_name(nominal_player)(4, obstacles, ball_direction, x, y);
}


int unique_name(nominal_player)(int player, int obstacles[9], 
				int ball_direction, int x, int y) {
    if (unique_name(ball_ahead)(obstacles)) {
	unique_name(got_it) = player;
	if ((obstacles[SW] == BALL) && (y == (MAX_Y-3))) {
/*	    kicking into a wall is pointless.  Step behind it instead
	    printf("player %d would kick into bottom wall\n", player);
*/
	    return S;
	}
	if ((obstacles[NW] == BALL) && (y == 2)) {
/*	    kicking into a wall is pointless.  Step behind it instead */
	    return N;
	}
	return(KICK);
    }
    if ((unique_name(got_it) == player) && 
	(!unique_name(ball_ahead)(obstacles))) {
	unique_name(got_it) = -1;
    }
    /* who's got it? */
    return(unique_name(get_behind_it)(obstacles, ball_direction));
}

int unique_name(random_heading)()
{
    int	m;

    m = ((rand()/256) % 8);
    switch(m){
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

int unique_name(eeny_meeny_2)(int obstacles[9], int choice1, int choice2)
{
    if ((rand() %2) == 0) {
	if (obstacles[choice1] == EMPTY) return choice1;
	if (obstacles[choice2] == EMPTY) return choice2;
    } else {
	if (obstacles[choice2] == EMPTY) return choice2;
	if (obstacles[choice1] == EMPTY) return choice1;
    }
    return unique_name(random_heading)();
}
int unique_name(get_behind_it)(int obstacles[9], int ball_direction)
{
    int eeny;
    switch(ball_direction) {
    case N: 
	if (obstacles[NE] == EMPTY) return NE;
	return unique_name(eeny_meeny_2)(obstacles, N, E);
    case NE:
	if (obstacles[NE] == EMPTY) return NE;
	return unique_name(eeny_meeny_2)(obstacles, N, E);
    case NW:
	if (obstacles[NW] == EMPTY) return NW;
	return unique_name(eeny_meeny_2)(obstacles, N, W);
    case W:
	if ((obstacles[NW] == EMPTY) ||
	    (obstacles[SW] == EMPTY)) {
	    return unique_name(eeny_meeny_2)(obstacles, NW, SW);
	}
	if (obstacles[W] == EMPTY) return W;
	return unique_name(random_heading)();
    case E:
	if ((obstacles[NE] == EMPTY) ||
	    (obstacles[SE] == EMPTY)) {
	    return unique_name(eeny_meeny_2)(obstacles, NE, SE);
	}
	if (obstacles[E] == EMPTY) return E;
	return unique_name(random_heading)();
    case S:
	if (obstacles[SE] == EMPTY) return SE;
	if (obstacles[S] == EMPTY) return S;
	if (obstacles[SW] == EMPTY) return SW;
	return unique_name(random_heading)();
    case SE:
	if (obstacles[SE] == EMPTY) return SE;
	return unique_name(eeny_meeny_2)(obstacles, S, W);
    case SW:
	if (obstacles[SW] == EMPTY) return SW;
	return unique_name(eeny_meeny_2)(obstacles, S, W);
    default: return(N);
    }
}

int unique_name(ball_ahead)(int obstacles[9])
{
    return ((obstacles[NW] == BALL) ||
	    (obstacles[W] == BALL) ||
	    (obstacles[SW] == BALL));
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


