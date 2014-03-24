//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//paddle dimentions
#define PADDLE_W 60
#define PADDLE_H 10

//global variables to detect colliding edge of ball
bool TOP_LEFT=false, TOP_RIGHT=false, BOTTOM_RIGHT=false, BOTTOM_LEFT=false; 


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    
    //Add ball to window
    add(window, ball);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    
    //Add paddle to window
    add(window,paddle);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    
    //add scoreboard
    add(window,label);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double velocity_x = drand48()+1;
    double velocity_y =  velocity_x;
    
    //wait for click to start
        waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //start ball movement
        move(ball,velocity_x,velocity_y);
        
        //check along horizontal boundaries
        if(getX(ball)+getWidth(ball) >= getWidth(window))
        {
            velocity_x = -velocity_x;
        }
        else if(getX(ball) <= 0)
        {
            velocity_x = -velocity_x;
        }
        
        //check along vertical boundaries 
        if(getY(ball)+getHeight(ball) >= getHeight(window))
        {
            //if bottom is reached , start from initial , decrease life by one
            removeGWindow(window,ball);
            ball = initBall(window);
            add(window, ball);
            pause(500);
            lives--;
        }
        else if(getY(ball) <= 0)
        {
            velocity_y = -velocity_y;
        }
        
        
        // move paddle in the direction of mouse
        
        //listen event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if mouse event was heard
        if(event != NULL)
        {
            //if mouse was moved
            if(getEventType(event) == MOUSE_MOVED)
            {
                double mouse_x = getX(event); 
                
                if(mouse_x + PADDLE_W <= WIDTH)
                {
                    if(mouse_x < 15)
                        setLocation(paddle, 0, HEIGHT-50);
                    else
                        setLocation(paddle, mouse_x, HEIGHT-50);
                }    
                else
                   setLocation(paddle, WIDTH-PADDLE_W, HEIGHT-50); 
              
                
            }
        }
        
        
        //detect collision of ball
        if(detectCollision(window,ball) != NULL)
        {
            GObject object = detectCollision(window,ball);
            
            if(object == paddle)
            {
                if(BOTTOM_LEFT == true)
                {
                    velocity_y = -velocity_y;
                    BOTTOM_LEFT = false;
                }
                else if(BOTTOM_RIGHT == true)
                {
                    velocity_y = -velocity_y;
                    BOTTOM_RIGHT = false;
                }
            }
            else if(strcmp(getType(object),"GRect") == 0)
            {
                removeGWindow(window,object);
                velocity_y = -velocity_y;
                
                updateScoreboard(window,label,++points);
                bricks--;
            }
        }
        
         pause(5);
    }

    // wait for click before exiting
    //waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    
    GRect brick;
    int i,j;
    double init_x ;
    double init_y = 27.0;
    
    // Initialize bricks
    for (i=0; i<ROWS; i++)
    { 
        init_x = 7.0;
        for(j=0; j<COLS; j++)
        {
            brick = newGRect(init_x,init_y,35,10);
            setFilled(brick,true);
            setColor(brick,"BLACK");
            add(window,brick);
                
            init_x += 39 ;
        }
        
        init_y += 15;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // Initiating ball
    
    GOval ball = newGOval((WIDTH/2)-10,(HEIGHT/2)-10,20,20);
    setFilled(ball, true);
    setColor(ball, "RED");
    if(ball != NULL)
        return ball;
    
    return NULL;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Initializing paddle
    GRect paddle = newGRect((WIDTH/2)-30, HEIGHT-50, PADDLE_W, PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "DARK_GRAY");
    
    if(paddle != NULL)
        return paddle;

    return NULL;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // Itializing lable
    
    GLabel label = newGLabel("0");
    setFont(label,"SansSerif-40");
    if(label != NULL)
        return label;
    
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {   
        TOP_LEFT=true;
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        TOP_RIGHT=true;
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        BOTTOM_LEFT=true;
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {   
        BOTTOM_RIGHT=true;
        return object;
    }

    // no collision
    return NULL;
}
