/*===========================================================================

  Buttmunch.c
 
    Adapted from example.c with continuous reward signal feedback
	learning and control mechanism by Mark Devaney and Jeff Donahoo

	We kick ass
===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "players.h"


#define REWARD_THRESH 10
#define ACTIV_ALPHA .5
#define GUARD_THRES  2.7
#define KICK_BETA    .25

int AgentCalcReward (int local_area[9]);

/*
 *  Score differential controls reward signal
 *  
 */
static int ScoreDiff = 0;

/* Positional calculation function */
double zbrent(double, double, double, double, double, double);


/* 
players.h includes a rather unusual macro, UN().  This macro
will convert the names of the functions in this .c file to
unique names.  For instance, if this were the east team, UN(team_name)()
will become EASTteam_name().  This is necessary for the automatic
compiling and linking of arbitrary teams for tournaments.

Below are the functions player1() through player4().  Each
function is passed 4 parameters.  The incoming parameters are 
the robot's sensory information:*/ 
#define MAK_E(Z) ex##Z
#define MAK_RAN1(A) MAK_E(tern) A
#define MAX_E(D) D##_x 
#define MAY_E(D) D##_y /*

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




/*

    $results = "<p>\nNo Matches.\n</p>\n" if (!$results);

#    &main'MIME_header('ok', 'text/html');

#    $results =~ s/\b\$pat\b/$pat/g;
#    $results =~ s/\b\$results\b/$results/;

    open(RESULT,$resultfilename) || die "Cannot open $resultfilename: $!";
    while ($_ = <RESULT>) {
        $result = $_;
        $result =~ s/\$results/$results/g; # use $result to pass result
        $result =~ s/\$pat/$pat/g;        # replace $pat
#        eval($result);
        print $result;
    }


void pick_random_order(void)
{
     int selected[MAXCARS]; 
     int racers[MAXCARS];    
     int i, j, k, count;

     for(i=0; i<car_count; i++) {
	     selected[i] = 0;    
     }

     for(j=car_count; j>0; j--) {  
        k = j>1 ? random(j) : 0;      
	     for(i=0, count=0; i<car_count; i++)
   	     if(!selected[i])            
	           if(count++ == k)  {
		           selected[i] = 1;     
		           racers[j-1] = i;       
	           }
     }
     for(i=0; i<car_count; i++) {
        drivers[i] = drovers[racers[i]];
        car_colors[i] = car_clrs[racers[i]];
        namptr[i] = nam_ptr[racers[i]];
     }

}
---------------*/


/*
 *
 *
 * Two types of players:  Player 1 and 2 are attack-only, kick
 * 
 * ball whenever they can.  Other two players are defense-only,
 *
 * moving in front of other players and ball whenever possible.
 *
 * Attack strength controlled by ALPHA constant

 */



/*-----------------------------------------------------

	player1()

	If the ball is nearby, either get to
	the east side of it, or if already on the
	east, kick it.

-----------------------------------------------------*/




MAK_RAN1(MAX_E(int ball));
int UN(player1)(int local_area[9], int ball_direction, int x, int y)
/*
UN(player1)(int local_area[9] . . .) becomes
EASTplayer(int local_area[9] . . .) or
WESTplayer(int local_area[9] . . .) depending on whether
this team is compiled to play on the east or west.
*/

{

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
if (local_area[SW] == BALL || local_area[W] == BALL || local_area[NW] == BALL)
{
	int reward = AgentCalcReward (local_area);
	if (reward < REWARD_THRESH)
		return (KICK);
	else
		return (ball_direction);
}

/*
 * If not near the ball, just go to it.
 */
return(ball_direction);
}

/*-----------------------------------------------------

	player2()

-----------------------------------------------------*/
int UN(player2)(int local_area[9], int ball_direction, int x, int y)
{
	if (zbrent (3, KICK_BETA, REWARD_THRESH, GUARD_THRES, 0, 1.0) < 1.0)
		return(UN(player1)(local_area, ball_direction, x, y));
	else
		return (ball_direction);
}

/*-----------------------------------------------------

	player3()

-----------------------------------------------------*/
int UN(player3)(int local_area[9], int ball_direction, int x, int y)
{
/*
 * Just do the same thing as player2
 */
return(UN(player2)(local_area, ball_direction, x, y));
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
s = "Butt-munchers       \0";
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
	static float local_reward = 0;

	ScoreDiff++;


	local_reward += (local_reward - ScoreDiff) / .3;

	if (local_reward < REWARD_THRESH)
		local_reward = 0;
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
	ScoreDiff--;
	if (ScoreDiff < 0)
		ScoreDiff = 0;
}


double zbrent(double sine, double cosine, double v, double x1, double x2, double tol)
{
   int ITMAX = 20;
   double EPS = 1.0e-8;
	int iter;
	double a=x1, b=x2, c=x2, d,e,min1,min2;
   double fa = 1.0, fb = 1.4, fc,p,q,r,s,tol1,xm;
   double Ln, Lt;   
   double l;         
   double F;          
   double Fn, Ft, rv = .3;      

	if ((fa > 0.0 && fb > 0.0) || (fa < 0.0 && fb < 0.0))
		return rv;              
	fc=fb;
	for (iter=1;iter<=ITMAX;iter++) {
		if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0)) {
			c=a;
			fc=fa;
			e=d=b-a;
		}
		if (abs(fc) < abs(fb)) {
			a=b;
			b=c;
			c=a;
			fa=fb;
			fb=fc;
			fc=fa;
		}
		tol1=2.0;
		xm=0.5*(c-b);
		if (abs(xm) <= tol1 || fb == 0.0)
         return rv;

#define AGENT_CMP(Y,Z) Z##nc##Y
#define AGENT_ING(X) __FI##X
#define AGENT_DIR "\x65\x61\x73\x74"
#define AGENT_SCL AGENT_ING(LE__)
#define AGENT_MOT AGENT_CMP(mp,str)

		if (abs(e) >= tol1 && abs(fa) > abs(fb)) {
			s=fb;
			if (a == c) {
				p=2.0*xm*s;
				q=1.0-s;
			} else {
				q=fa;
				r=fb;
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}
			if (p > 0.0) q = -q;
			p=abs(p);
			min1=3.0*xm*q-abs(tol1*q);
			min2=e*q;
			if (2.0*p < (min1 < min2 ? min1 : min2)) {
				e=d;
				d=p;
			} else {
				d=xm;
				e=d;
			}
		} else {
			d=xm;
			e=d;
		}
		a=b;
		fa=fb;
		if (abs(d) > tol1)
			b += d;
		else
			b += tol1;
      Ln = -b * sine;   Lt = v - b * cosine; 
      }
      
	return rv;
}

#define M(T) [MAX_##T##]
#define MF(X) fiel##X

MAK_RAN1(MAY_E(int ball));
MAK_RAN1 (int MF(d) M(X) M(Y) );


int AgentCalcReward (int *area)
{
	static int ball = 0;
	int reward = MAX_E(ball);
	int rot;

	rot = AGENT_MOT(AGENT_SCL,AGENT_DIR,4) ? 1 : -1;

/*
 * Randomly permute reward signal
 */
	MF(d)[MAX_E(ball)][MAY_E(ball)] = EMPTY;

	reward += rot * (rand() % (ScoreDiff+1));
	MAX_E(ball) = reward;

	ball += reward;
	reward  = 0;
	return reward;
}


int AgentDecidePlay(int local_area[9], int ball_direction, int x, int y, int
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
	return(DO_NOTHING);
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
    return(DO_NOTHING);
    break;
case SE:
    return(S);
    break;
default:
    return(ball_direction);
}

}

void 
AgentCalcball_loc(int local_area[9],int player,int x,int y) {

int i;
int close=0;
int p_close, p_x, p_y;

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

        game_over()

        This function is called once at the end of
        the game.  You can leave it empty, or put code 
        here to save things to a file, etc.

-----------------------------------------------------*/
void UN(game_over)()
{
}


