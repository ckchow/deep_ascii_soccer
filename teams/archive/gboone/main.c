/*===========================================================================

	gary.c

	This team forms a loose pattern once the ball is aquired. 
   	The robot that finds the ball is the captain. The others
	flank him diagonally, hoping to catch the kicks of the 
	opposing team. 
		
	Gary Boone       gboone@cc.gatech.edu

===========================================================================*/

#include "players.h"

#define  POS_X   4   /* flanking position horizontal */
#define  POS_Y   4   /* flanking position vertical   */

/* forward ref */
UN(goToNE)(int gx, int gy, int x, int y, int x_dist, int y_dist);

static int UN(got_it) = -1;           /* who is the captain? */
static int UN(capt_loc_x) = -1;
static int UN(capt_loc_y) = -1;


/*  nearBall  (by Steve Rowe)
    Given a local area, return the direction to the ball, or 9 if the ball
    is not in the local area.
*/
int UN(nearBall)(int local_area[9])
{
  int i;
  
  for (i = 0; i < 9; ++i) {
    if (local_area[i] == BALL) {
      return 1;
    }
  }
  return 0;
}


/*-----------------------------------------------------

	player1()

	If the ball is nearby, either get to
	the east side of it, or if already on the
	east, kick it.

-----------------------------------------------------*/
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
{
  if (!UN(nearBall)(local_area)) /* if not near ball */
    if (UN(got_it) == 1)         /* but was capt */
      UN(got_it) = -1;           /* release capt */
    else;
  else                           /* if near ball */
    if (UN(got_it) == -1) {      /* but there is no captain */
      UN(capt_loc_x) = x;        /* become captain */
      UN(capt_loc_y) = y;
      UN(got_it) = 1;
    }

/*
 * If right next to the ball, on the west, get to east side.
 */
if (local_area[N] == BALL) return(NE);
if (local_area[NE] == BALL) return(E);
if (local_area[E] == BALL) return(SE);
if (local_area[SE] == BALL) return(E);
if (local_area[S] == BALL) return(SE);

/*
 * If already on the west, kick!
 */
if (local_area[SW] == BALL) return(KICK);
if (local_area[W] == BALL) return(KICK);
if (local_area[NW] == BALL) return(KICK);

/*
 * If not near the ball, just go to it.
 */
  if (UN(got_it) == -1)      /* if no capt, go for ball */
    return(ball_direction);
  else                       /* else go to position */
    return UN(goToNE)(UN(capt_loc_x), UN(capt_loc_y), x, y, POS_X, POS_Y); 

}


int
UN(goToNE)(int gx, int gy, int x, int y, int x_dist, int y_dist)
{
  int dx, dy;
  
  dx = gx - x + x_dist;
  dy = gy - y + y_dist;

  if ((dx < 0) && (dy < 0)) return NW;
  if ((dx < 0) && (dy == 0)) return W;
  if ((dx < 0) && (dy > 0)) return SW;
  if ((dx == 0) && (dy > 0)) return S;
  if ((dx == 0) && (dy == 0)) return S;
  if ((dx == 0) && (dy < 0)) return N;
  if ((dx > 0) && (dy < 0)) return NE;
  if ((dx > 0) && (dy == 0)) return E;
  if ((dx > 0) && (dy > 0)) return SE;

}


/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
  if (!UN(nearBall)(local_area)) /* if not near ball */
    if (UN(got_it) == 2)         /* but was capt */
      UN(got_it) = -1;           /* release capt */
    else;
  else                           /* if near ball */
    if (UN(got_it) == -1) {      /* but there is no captain */
      /* become captain */
      UN(capt_loc_x) = x;
      UN(capt_loc_y) = y;
      UN(got_it) = 2;
    }
  
  
/* If right next to the ball, on the west, get to east side. */

if (local_area[N] == BALL) return(NE);
  if (local_area[NE] == BALL) return(E);
  if (local_area[E] == BALL) return(SE);
  if (local_area[SE] == BALL) return(E);
  if (local_area[S] == BALL) return(SE);

/* if already on the west, kick! */
  if (local_area[SW] == BALL) return(KICK);
  if (local_area[W] == BALL) return(KICK);
  if (local_area[NW] == BALL) return(KICK);
/* If not near the ball, just go to NE of player 1 */

  if (UN(got_it) == -1)      /* if no capt, go for ball */
    return(ball_direction);
  else                       /* else go to position */
    return UN(goToNE)(UN(capt_loc_x), UN(capt_loc_y), x, y, POS_X, -POS_Y); 


}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
  if (!UN(nearBall)(local_area)) /* if not near ball */
    if (UN(got_it) == 3)         /* but was capt */
      UN(got_it) = -1;           /* release capt */
    else;
  else                           /* if near ball */
    if (UN(got_it) == -1) {      /* but there is no captain */
      /* become captain */
      UN(capt_loc_x) = x;
      UN(capt_loc_y) = y;
      UN(got_it) = 3;
    }

/* If right next to the ball, on the west, get to east side. */

if (local_area[N] == BALL) return(NE);
  if (local_area[NE] == BALL) return(E);
  if (local_area[E] == BALL) return(SE);
  if (local_area[SE] == BALL) return(E);
  if (local_area[S] == BALL) return(SE);

/* If already on the west, kick! */
  if (local_area[SW] == BALL) return(KICK);
  if (local_area[W] == BALL) return(KICK);
  if (local_area[NW] == BALL) return(KICK);
/* If not near the ball, just go to NE of player 1 */
  
  if (UN(got_it) == -1)      /* if no capt, go for ball */
    return(ball_direction);
  else                       /* else go to position */
    return UN(goToNE)(UN(capt_loc_x), UN(capt_loc_y), x, y, POS_X, POS_Y/2); 
}

/*-----------------------------------------------------

	player4()

-----------------------------------------------------*/
int UN(player4)(int local_area[9], int ball_direction, int x, int y)
{
  if (!UN(nearBall)(local_area)) /* if not near ball */
    if (UN(got_it) == 4)         /* but was capt */
      UN(got_it) = -1;           /* release capt */
    else;
  else                           /* if near ball */
    if (UN(got_it) == -1) {      /* but there is no captain */
      /* become captain */
      UN(capt_loc_x) = x;
      UN(capt_loc_y) = y;
      UN(got_it) = 4;
    }

/* If right next to the ball, on the west, get to east side. */

  if (local_area[N] == BALL) return(NE);
  if (local_area[NE] == BALL) return(E);
  if (local_area[E] == BALL) return(SE);
  if (local_area[SE] == BALL) return(E);
  if (local_area[S] == BALL) return(SE);

/* If already on the west, kick! */
  if (local_area[SW] == BALL) return(KICK);
  if (local_area[W] == BALL) return(KICK);
  if (local_area[NW] == BALL) return(KICK);
/* If not near the ball, just go to NE of player 1 */
  
  if (UN(got_it) == -1)      /* if no capt, go for ball */
    return(ball_direction);
  else                       /* else go to position */
    return UN(goToNE)(UN(capt_loc_x), UN(capt_loc_y), x, y, POS_X, -POS_Y/2); 
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
s = "Feeble Forcers      \0";
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


