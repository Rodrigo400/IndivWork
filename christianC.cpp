// Name: Christian Capusi
// Date: June 21, 2017
// Purpose: Create a sidescroller with a team

// What I need to do:
// Main character sprite movement
// Main character jump
// Main character shoot
// Main character die
// Main character level collision
// Main character health tracking

// Progress:
// June 21 2017
// Displayed Sprite on Screen/ Resized

// June 22 2017
// Created Movement and moved commands to my cpp file
// Character now has "shoot animation"

// June 23 2017
// Code works with others
// 

// June 24 2017
// clearScreen();
// indent/ coding style change

// June 28 2017
// added Sprite movement
// create Sprite class in game.h
// Sprite class contains x and y coord of each sprite

// June 29 2017
// Change x coordinates on everyone's files
// Everyone's sprites move based on main character's movements
// Added base for shoot particles which are just boxes
// Waiting on tile system for Jump Physics

#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
#include "fonts.h"
#include "game.h"
using namespace std;

/*struct Vec
{
    float x, y, z;
};

struct Shape
{
    float width, height;
    Vec center;
};

struct Game
{
    Shape box[5];
    int n;
} game;
*/
//load character image

// Global instances
Game game;

Ppmimage *characterImage(int charSelect)
{
    if (charSelect == 1) {
        system("convert ./images/mainChar.png ./images/mainChar.ppm");
        return ppm6GetImage("./images/mainChar.ppm");
    } else if (charSelect == 2) {
        system("convert ./images/mainChar2.png ./images/mainChar2.ppm");
        return ppm6GetImage("./images/mainChar2.ppm");
    }
    //removes warning since no return outside conditionals
    system("convert ./images/mainChar.png ./images/mainChar.ppm");
    return ppm6GetImage("./images/mainChar.ppm");
}

void jumpDecrementPhysics()
{
    //if character is not touching the floor,
    //and jumpFlagFinish == true;
}

void jumpIncrementPhysics()
{
    //if (XK UP && jumpFlag == false && jumpFlagFinish == true)
    //
    //    if (character.pos != tempCharacter.pos + 100)
    //         character.pos = character.pos + 2
    //    
}

void shootParticle()
{
    for(int i = 0; i < 5; i++)
    {
        game.box[i].width = 10;
        game.box[i].height = 10;
        game.box[i].center.x = gl.xres/2;
        game.box[i].center.y = 200;
    }
}

void shootWalkRight(float tx, float ty, float cx,
    float w, float cy, float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,              ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx+w, cy+h);
}

void shootWalkLeft(float tx, float ty, float cx,
    float w, float cy, float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy-h);
}    

void shootStandRight(float tx, float ty, float cx,
    float w, float cy, float h)
{
    glTexCoord2f(tx + .25, ty + .666); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx+.25,   ty + .333); glVertex2i(cx+w, cy+h);
}

void shootStandLeft(float tx, float ty, float cx,
    float w, float cy, float h)
{
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx + .25, ty + .666); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy+h);
}

void standRight(float tx, float ty, float cx,
    float w,float cy,float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,              ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx+w, cy+h);
}

void standLeft(float tx, float ty, float cx,
    float w,float cy,float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy-h);
}

void jumpLeft(float tx,float ty,float cx,
    float w,float cy,float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,         ty+.333); glVertex2i(cx+w, cy-h);
}

void jumpRight(float tx, float ty, float cx,
    float w, float cy, float h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy-h);
}
void moveSpriteRight(Sprite *sprt)
{
    sprt->cx = sprt->cx + 2;
    //if rughtt key is pressed && next tile is free
    //    sp.cx = sp.cx--;
    //else if left key is pressed && next tile is free
    //    sp.cx = sp.cx++;
    //else if left key != pressed && right key != pressed
    //    nothing 
}
void moveSpriteLeft(Sprite *sprt)
{
    sprt->cx = sprt->cx - 2;
}
void conditionalRenders(float tx, float ty, float cx,
    float w, float cy, float h)
{
    if (gl.keys[XK_Right] && gl.keys[XK_space] == 0) {
        shootWalkRight(tx,ty,cx,w,cy,h);
        shootParticle();
        gl.directionFlag = 0;
    } else if (gl.keys[XK_Left] && gl.keys[XK_space] == 0) {
        shootWalkLeft(tx,ty,cx,w,cy,h);
        shootParticle();
        gl.directionFlag = 1;
    } else if ((gl.keys[XK_space] && gl.directionFlag == 0) ||
        (gl.keys[XK_space] && gl.keys[XK_Right])) {
            shootStandRight(tx,ty,cx,w,cy,h);
            shootParticle();
    } else if ((gl.keys[XK_space] && gl.directionFlag == 1) ||
        (gl.keys[XK_space] && gl.keys[XK_Left])) {
            shootStandLeft(tx,ty,cx,w,cy,h);
            shootParticle();
    }

    if (gl.keys[XK_Left] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 1 && gl.keys[XK_space] == 0) {
            standLeft(tx,ty,cx,w,cy,h);
    }
    if (gl.keys[XK_Right] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 0 && gl.keys[XK_space] == 0) {
            standRight(tx,ty,cx,w,cy,h);
    }
}

void clearScreen()
{
    glClearColor(0.1,0.1,0.1,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}


void renderMainCharacter()
{
    if (gl.initDone == 0) {
	//other sprites will have cx here
        //add gl.initDone = 1 inn main
    }
        float cy = 100;
    float cx = gl.xres/2.0;
    float h = 30.0;
    float w = h * .903;
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacterTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.maincharacterFrame % 4;
    int iy = 3;
    if (gl.maincharacterFrame >= 4 && gl.attackFlag == 0)
        iy = 0;
    float tx = (float)ix / 4.0;
    float ty = (float)iy / 3.0;
    glBegin(GL_QUADS);
    conditionalRenders(tx, ty, cx, w, cy, h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}
