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

// July 6 2017
// Added jump sprite conditionals

// July 7 2017
// Added jump physics Need to dynamically calculate max height
//    based on height before jump

// July 10 2017
// Added working power ups

// July 14 2017
// Added working power ups

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

void shootParticle()
{
    printf("Shoot\n");
    for (int i = 0; i < 5; i++)
    {
    }
}

void shootWalkRight(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,              ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx+w, cy+h);
}

void shootWalkLeft(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy-h);
}    

void shootStandRight(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25, ty + .666); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx+.25,   ty + .333); glVertex2i(cx+w, cy+h);
}

void shootStandLeft(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx + .25, ty + .666); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy+h);
}

void standRight(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx+w, cy-h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,              ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx+w, cy+h);
}

void standLeft(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25, ty + .333); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25,        ty); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,              ty); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,       ty + .333); glVertex2i(cx+w, cy-h);
}

void jumpRight(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx,          ty + 1); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx +.25,  ty + .666); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx +.25,     ty + 1); glVertex2i(cx+w, cy-h);
}

void jumpLeft(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    glTexCoord2f(tx + .25,    ty + 1); glVertex2i(cx-w, cy-h);
    glTexCoord2f(tx + .25, ty + .666); glVertex2i(cx-w, cy+h);
    glTexCoord2f(tx,       ty + .666); glVertex2i(cx+w, cy+h);
    glTexCoord2f(tx,          ty + 1); glVertex2i(cx+w, cy-h);
}

void moveSpriteRight(Sprite *sprt)
{
    sprt->cx = sprt->cx + gl.movementSpeed;
}

void moveSpriteLeft(Sprite *sprt)
{
    sprt->cx = sprt->cx - gl.movementSpeed;
}

void jump()
{
    if (gl.isJumpingFlag == 0) {
	//temporarily store current y coord
        gl.initialJumpCy = mainChar.cy;
        //temporarily store max jump height
	gl.finalJumpCy = gl.initialJumpCy + gl.jumpHeight;
        gl.isJumpingFlag = 1;
        gl.jumpDirectionFlag = 1;
    }
}

void checkJump()
{
    // if character started jump, increment to max height
    if (gl.isJumpingFlag == 1 && gl.jumpDirectionFlag == 1) {
        if (mainChar.cy <= gl.finalJumpCy) {
            mainChar.cy = 1 + mainChar.cy + ((gl.finalJumpCy - mainChar.cy) * gl.jumpRate);
        } 
        if (mainChar.cy >= gl.finalJumpCy) {
            gl.jumpDirectionFlag = 0;
        }
    }
    // When character reaches max height with one jump
    if (gl.isJumpingFlag == 1 && gl.jumpDirectionFlag == 0) {
        if (mainChar.cy > gl.initialJumpCy) {
            mainChar.cy = mainChar.cy - ((gl.finalJumpCy - mainChar.cy) * gl.jumpRate) - 1;
        }
        if (mainChar.cy <= gl.initialJumpCy) {
            //modyify this later to set to highest tile level
	    mainChar.cy = 90;
            gl.isJumpingFlag = 0;
        }
    }
}

void conditionalRenders(Flt tx, Flt ty, Flt cx, Flt w, Flt cy, Flt h)
{
    checkJump();
    if (gl.keys[XK_Right] && gl.keys[XK_space] == 0 &&
        gl.isJumpingFlag == 0) {
            shootWalkRight(tx,ty,cx,w,cy,h);
            gl.directionFlag = 0;
    } else if (gl.keys[XK_Left] && gl.keys[XK_space] == 0 &&
        gl.isJumpingFlag == 0) {
            shootWalkLeft(tx,ty,cx,w,cy,h);
            gl.directionFlag = 1;
    } else if ((gl.keys[XK_space] && gl.directionFlag == 0 &&
        gl.isJumpingFlag == 0) || (gl.keys[XK_space] && gl.keys[XK_Right])) {
            shootStandRight(tx,ty,cx,w,cy,h);
            shootParticle();
    } else if ((gl.keys[XK_space] && gl.directionFlag == 1 &&
        gl.isJumpingFlag == 0) || (gl.keys[XK_space] && gl.keys[XK_Left])) {
            shootStandLeft(tx,ty,cx,w,cy,h);
            shootParticle();
    } else if (gl.keys[XK_Left] && gl.isJumpingFlag == 1 &&
        (gl.keys[XK_space] == 1 || gl.keys[XK_space] == 0)) {
            jumpLeft(tx, ty, cx, w, cy, h);
            gl.directionFlag = 1;
    } else if (gl.keys[XK_Right] && gl.isJumpingFlag == 1 &&
        (gl.keys[XK_space] == 1 || gl.keys[XK_space] == 0)) {
            jumpRight(tx, ty, cx, w, cy, h);
            gl.directionFlag = 0;
    }

    if (gl.keys[XK_Up] && gl.isJumpingFlag == 0) {
            jump();
    }
    if (gl.keys[XK_Left] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 1 && gl.keys[XK_space] == 0 &&
        gl.isJumpingFlag == 0) {
            standLeft(tx, ty, cx, w, cy, h);
    }
    if (gl.keys[XK_Right] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 0 && gl.keys[XK_space] == 0  &&
        gl.isJumpingFlag == 0) {
            standRight(tx, ty, cx, w, cy, h);
    }
    if (gl.keys[XK_Left] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 1 && (gl.keys[XK_space] == 0 || 
        gl.keys[XK_space] == 1) && gl.isJumpingFlag == 1) {
            jumpLeft(tx, ty, cx, w, cy, h);
	    if (gl.keys[XK_space] == 1) {
	        shootParticle();
	    }
    }
    if (gl.keys[XK_Right] == 0 && gl.keys[XK_Right] == 0 &&
        gl.directionFlag == 0 && (gl.keys[XK_space] == 0 ||
        gl.keys[XK_space] == 1) && gl.isJumpingFlag == 1) {
            jumpRight(tx, ty, cx, w, cy, h);
	    if (gl.keys[XK_space] == 1) {
	        shootParticle();
	    }
    }
}

void clearScreen()
{
    glClearColor(0.1,0.1,0.1,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void spriteDisappear(Sprite* sprt)
{
    sprt->cx = -9999999;
}

void renderMainCharacter()
{
    mainChar.cx = gl.xres/2.0;
    float h = 25.0;
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
    conditionalRenders(tx, ty, mainChar.cx, w, mainChar.cy, h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

void renderSpeedboost1()
{
    if (gl.speedboost1Flag != false) {
        float h = 25;
        float w = 25;
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, gl.speedboostTexture);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        int ix = 1, iy = 1;
        float tx = (float)ix;
        float ty = (float)iy;
        glBegin(GL_QUADS);
        glTexCoord2f(tx + 1,    ty + 1); glVertex2i(speedboost1.cx-w, speedboost1.cy-h);
        glTexCoord2f(tx + 1,    ty); glVertex2i(speedboost1.cx-w, speedboost1.cy+h);
        glTexCoord2f(tx,           ty ); glVertex2i(speedboost1.cx+w, speedboost1.cy+h);
        glTexCoord2f(tx,            ty + 1); glVertex2i(speedboost1.cx+w, speedboost1.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx == speedboost1.cx) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            gl.speedboost1Flag = false;
            spriteDisappear(&speedboost1);
            gl.movementSpeed = gl.movementSpeed + 1.5;
        }
    }
}

void renderShield1()
{
    if (gl.shield1Flag != false) {
        float h = 25;
        float w = 25;
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, gl.shieldTexture);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        int ix = 1, iy = 1;
        float tx = (float)ix;
        float ty = (float)iy;
        glBegin(GL_QUADS);
        glTexCoord2f(tx + 1,    ty + 1); glVertex2i(shield1.cx-w, shield1.cy-h);
        glTexCoord2f(tx + 1,    ty); glVertex2i(shield1.cx-w, shield1.cy+h);
        glTexCoord2f(tx,           ty ); glVertex2i(shield1.cx+w, shield1.cy+h);
        glTexCoord2f(tx,            ty + 1); glVertex2i(shield1.cx+w, shield1.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx > (shield1.cx - 10) && mainChar.cx < (shield1.cx + 10)) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            gl.shield1Flag = false;
            spriteDisappear(&shield1);
        }
    }
}

void renderHeart1()
{
    if (gl.heart1Flag != false) {
        float h = 25;
        float w = 25;
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, gl.heartaddTexture);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        int ix = 1, iy = 1;
        float tx = (float)ix;
        float ty = (float)iy;
        glBegin(GL_QUADS);
        glTexCoord2f(tx + 1,    ty + 1); glVertex2i(heart1.cx-w, heart1.cy-h);
        glTexCoord2f(tx + 1,    ty); glVertex2i(heart1.cx-w, heart1.cy+h);
        glTexCoord2f(tx,           ty ); glVertex2i(heart1.cx+w, heart1.cy+h);
        glTexCoord2f(tx,            ty + 1); glVertex2i(heart1.cx+w, heart1.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx > (heart1.cx - 10) && mainChar.cx < (heart1.cx + 10)) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            gl.heart1Flag = false;
            spriteDisappear(&heart1);
            if (mainChar.health < 30) {
                mainChar.health = mainChar.health + 5;
            }
        }
    }
}

void renderHeart2()
{
    if (gl.heart2Flag != false) {
        float h = 25;
        float w = 25;
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, gl.heartaddTexture);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        int ix = 1, iy = 1;
        float tx = (float)ix;
        float ty = (float)iy;
        glBegin(GL_QUADS);
        glTexCoord2f(tx + 1,    ty + 1); glVertex2i(heart2.cx-w, heart2.cy-h);
        glTexCoord2f(tx + 1,    ty); glVertex2i(heart2.cx-w, heart2.cy+h);
        glTexCoord2f(tx,           ty ); glVertex2i(heart2.cx+w, heart2.cy+h);
        glTexCoord2f(tx,            ty + 1); glVertex2i(heart2.cx+w, heart2.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx > (heart2.cx - 10) && mainChar.cx < (heart2.cx + 10)) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            gl.heart2Flag = false;
            printf("health2 picked up\n");
            spriteDisappear(&heart2);
            if (mainChar.health < 30) {
                mainChar.health = mainChar.health + 5;
            }
        }
    }
}

void renderChristianSprites()
{
    renderMainCharacter();
    renderShield1();
    renderSpeedboost1();
    renderHeart1();
    renderHeart2();
}
