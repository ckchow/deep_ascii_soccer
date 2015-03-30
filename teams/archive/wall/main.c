/*===========================================================================

	wall.c

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/
#include "players.h"

/*forward ref*/
UN(determine_offensive)(int my_id, int ball_direction);


/*-----------------------------------------------------

	team_name()

	Every team must have a name!  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *UN(team_name)()
{
char	*s;

/*  "####################\0" <--- 20 characters */
s = "W'all Kick Yer Butt \0";
return(s);
}

static int player_x[5], player_y[5], first_time = 1;
static int ball_in_front[5], offensive = 0;

/*-----------------------------------------------------

	player1()

-----------------------------------------------------*/
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
{
int i;
int my_id, partner_id;

my_id = 1; partner_id = 2;

player_x[my_id] = x;
player_y[my_id] = y;

if (first_time)
	{
	first_time = 0;
	for(i=0; i<=4; i++)
		{
		player_x[i] = player_y[i] = 0;
		ball_in_front[i] = 0;
		}
	}

UN(determine_offensive)(my_id, ball_direction);

if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);
if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

if ((ball_direction == S)&&(!offensive)) return(SE);
if ((ball_direction == N)&&(!offensive)) return(NE);
if (offensive != 1) return(ball_direction);

if (local_area[N] == BOUNDARY) return(ball_direction);
if (local_area[S] == BOUNDARY) return(ball_direction);

if ((y >= (player_y[partner_id]-7))&&(ball_direction == N)) return(N);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == NE)) return(NE);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == E)) return(E);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == SE)) return(E);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == S)) return(E);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == SW)) return(W);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == W)) return(W);
if ((y >= (player_y[partner_id]-7))&&(ball_direction == NW)) return(NW);

return(ball_direction);
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
int i;
int my_id, partner_id;

my_id = 2; partner_id = 3;

player_x[my_id] = x;
player_y[my_id] = y;

UN(determine_offensive)(my_id, ball_direction);

if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);
if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

if ((ball_direction == W)&&(offensive)&&(local_area[NW]==EMPTY)) return(NW);

if ((ball_direction == S)&&(!offensive)) return(SE);
if ((ball_direction == N)&&(!offensive)) return(NE);

return(ball_direction);
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
int i;
int my_id, partner_id;

my_id = 3; partner_id = 2;

player_x[my_id] = x;
player_y[my_id] = y;

UN(determine_offensive)(my_id, ball_direction);

if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);
if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

if ((ball_direction == W)&&(offensive)&&(local_area[SW]==EMPTY)) return(SW);

if ((ball_direction == S)&&(!offensive)) return(SE);
if ((ball_direction == N)&&(!offensive)) return(NE);

return(ball_direction);
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int UN(player4)(int local_area[9], int ball_direction, int x, int y)
{
int i;
int my_id, partner_id;

my_id = 4; partner_id = 3;

player_x[my_id] = x;
player_y[my_id] = y;

UN(determine_offensive)(my_id, ball_direction);

if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);
if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

if (local_area[N] == BOUNDARY) return(ball_direction);
if (local_area[S] == BOUNDARY) return(ball_direction);

if ((ball_direction == S)&&(!offensive)) return(SE);
if ((ball_direction == N)&&(!offensive)) return(NE);
if (offensive != 1) return(ball_direction);

/*printf("%d %d",y,player_y[2]);*/
if ((y <= player_y[3]+7)&&(ball_direction == N)) return(E);
if ((y <= player_y[3]+7)&&(ball_direction == NE)) return(E);
if ((y <= player_y[3]+7)&&(ball_direction == E)) return(E);
if ((y <= player_y[3]+7)&&(ball_direction == SE)) return(SE);
if ((y <= player_y[3]+7)&&(ball_direction == S)) return(S);
if ((y <= player_y[3]+7)&&(ball_direction == SW)) return(W);
if ((y <= player_y[3]+7)&&(ball_direction == W)) return(W);
if ((y <= player_y[3]+7)&&(ball_direction == NW)) return(W);

return(ball_direction);
}

UN(determine_offensive)(int my_id, int ball_direction)
{
int i;

ball_in_front[my_id] = 0;
if ((ball_direction == W)||(ball_direction == NW)||
	(ball_direction == SW)||(ball_direction == N)||(ball_direction == S))
	ball_in_front[my_id] = 1;
else
	ball_in_front[my_id] = 0;
offensive = 1;
for(i = 1; i <= 4; i++)
	if (ball_in_front[i] == 0)
		offensive = 0;
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


