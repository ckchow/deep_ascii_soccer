/*===========================================================================

	example.c

	A very basic soccer strategy.  All four players attempt to run
	up to the ball and kick it west!

	Tucker Balch	tucker@cc.gatech.edu

===========================================================================*/

#include "players.h"
/* 
players.h includes a rather unusual macro, UN().  This macro
will convert the names of the functions in this .c file to
unique names.  For instance, if this were the east team, UN(team_name)()
will become EASTteam_name().  This is necessary for the automatic
compiling and linking of arbitrary teams for tournaments.

Below are the functions player1() through player4().  Each
function is passed 4 parameters.  The incoming parameters are 
the robot's sensory information:  

	local_area[]	Reveals what's nearby.  Indexed by
			N,NE,E,SE,S, etc. so that, for example,
			local_area[S] tells you what is in the
			cell to the south of the robot.  Possible 
			values include: BOUNDARY, OPPONENT, TEAMMATE,
			BALL and EMPTY.

	ball_direction	Compass heading to the ball: N, S, E, W, NE, etc.

	x, y		The robot's location.  y varies from 1 to 22,
			x varies from 1 to 78.

The function should return an integer indicating either a direction to
move (N, NE, E, S, etc) or KICK to kick the ball.
*/

int p_close=0,p_x,p_y;

/* Only when against border*/
int ball_dir(int y,int direction) {

  if (p_close != 0) {
    if (y > p_y) return(N);
    else if (y < p_y) return(S);
    else return(DO_NOTHING);
  }

  return(direction);
}    

int play(int local_area[9], int ball_direction, int x, int y, int
	 xlow, int xhigh) {

if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);

if ((x > xlow) && (x < xhigh))
  return(ball_direction);

/* Too far west */
if (x < xlow)
    switch(ball_direction) {
    case NW:
    case N:
	return(NE);
	break;
    case W:
	return(E);
	break;
    case SW:
    case S:
	return(SE);
	break;
    default:
	return(ball_direction);
    }

/* Too far east */
if (x > xhigh)
    switch (ball_direction) {
    case N:
    case NE:
	return(NW);
	break;
    case E:
	return(W);
	break;
    case SE:
    case S:
	return(SW);
	break;
    default:
	return(ball_direction);
    }

/* On west boundary */
if (x == xlow) 
    switch (ball_direction) {
    case NW:
	return(N);
	break;
    case W:
	return(ball_dir(y,DO_NOTHING));
	break;
    case SW:
	return(S);
	break;
    default:
	return(ball_direction);
    }

/* On east boundary*/
switch (ball_direction) {
case NE:
    return(N);
    break;
case E:
    return(ball_dir(y,DO_NOTHING));
    break;
case SE:
    return(S);
    break;
default:
    return(ball_direction);
}

}

void ball_loc(int local_area[9],int player,int x,int y) {

int i;
int close=0;

  for (i=0;i<=9;i++)
    if (local_area[i]==BALL) {
      close=1;
      break;
    }

if (close) {
  p_close=player;
  p_x=x;
  p_y=y;
}
else
  if (p_close == player) p_close=0;

}

     
/*-----------------------------------------------------

	player1()

Hold back near goal

-----------------------------------------------------*/
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
/*
UN(player1)(int local_area[9] . . .) becomes
EASTplayer(int local_area[9] . . .) or
WESTplayer(int local_area[9] . . .) depending on whether
this team is compiled to play on the east or west.
*/

{

    ball_loc(local_area,1,x,y);
    return play(local_area, ball_direction,x,y,70,78);
}


/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
    /* return(DO_NOTHING); */
    ball_loc(local_area,2,x,y);
    return play(local_area, ball_direction, x, y,0,78);
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
    /* return(DO_NOTHING); */
    ball_loc(local_area,3,x,y);
    return play(local_area, ball_direction, x, y,0,60);
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int UN(player4)(int local_area[9], int ball_direction, int x, int y)
{
    /* return(DO_NOTHING); */
    ball_loc(local_area,4,x,y);
    return play(local_area, ball_direction, x, y,0,50);
}

/*-----------------------------------------------------

	team_name()

	Every team must have a name.  Make sure it
	is exactly 20 characters.  Pad with spaces.

-----------------------------------------------------*/
char *UN(team_name)()
{
char	*s;
static int x=1;

/*  "####################\0" <--- 20 characters */
if (x) {
  x=0;
  s = "Donahoo's Deathtraps\0";
}
else {
  x=1;
  s = "Everyone Die        \0";
}

return(s);
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


