// Name: Christian Capusi
// Date: June 21, 2017
// Purpose: Create a sidescroller with a team

// What I need to do:
//     -Main character level collision

// What I have done:
//     -Main Character Movement
//     -Main Character Dynamic Jump Physics
//     -Main Character Shoot + Particle Phyics
//     -Other Sprite Movement
//     -Working power ups

// Cool features:
//     -Movement is created through an illusion by moving everything but
//         the main character
//     -Particles react to characters movement!
//     -Jump height is dynamically calculated! 
//     -Attributes (health, movementspeed, etc.) are stored in a class
//         this makes it easy to manipulate. Good for power ups!

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
#include "fonts.h"
#include "game.h"
//#include <unistd.h>
//#include <math.h>
using namespace std;

Ppmimage *characterImage(int charSelect)
{
    if (charSelect == 1) {
        system("convert ./images/mainChar1.png ./images/mainChar1.ppm");
        return ppm6GetImage("./images/mainChar1.ppm");
    } else if (charSelect == 2) {
        system("convert ./images/mainChar2.png ./images/mainChar2.ppm");
        return ppm6GetImage("./images/mainChar2.ppm");
    } else if (charSelect == 3) {
        system("convert ./images/mainChar3.png ./images/mainChar3.ppm");
        return ppm6GetImage("./images/mainChar3.ppm");
    } else if (charSelect == 4) {
        system("convert ./images/mainChar4.png ./images/mainChar4.ppm");
        return ppm6GetImage("./images/mainChar4.ppm");
    }

    return 0;
    //removes warning since no return outside conditionals
    //system("convert ./images/mainChar.png ./images/mainChar.ppm");
    //return ppm6GetImage("./images/mainChar.ppm");
}

void particleMove()
{
    //move particles based on character movement.
    //if character is moving same direction, slow down
    //if character is moving opposite direction, speed up
    for(int i = 0; i < gl.particleCount; i++) {
        if (gl.keys[XK_Left] && gl.particle[i].direction == 1) {
            gl.particle[i].cx = gl.particle[i].cx + gl.movementSpeed;
        }
        if (gl.keys[XK_Right] && gl.particle[i].direction == 0) {
            gl.particle[i].cx = gl.particle[i].cx - gl.movementSpeed;
        }
    }
}

void particlePhysics()
{
    for(int i = 0; i < gl.particleCount; i++) {
       glColor3ub(255, 255, 255);
       glPushMatrix();
       glTranslatef(gl.particle[i].cx, gl.particle[i].cy, 0);
       float w = gl.particleWidth;
       float h = gl.particleHeight;
       glBegin(GL_QUADS);
       glVertex2i(-w, -h);
       glVertex2i(-w,  h);
       glVertex2i(w,   h);
       glVertex2i(w,  -h);
       glEnd();
       glPopMatrix();
       if(gl.particle[i].direction == 1) {
           gl.particle[i].cx = gl.particle[i].cx - gl.particle[i].velocity;
       }
       if(gl.particle[i].direction == 0) {
           gl.particle[i].cx = gl.particle[i].cx + gl.particle[i].velocity;
       }
       if(gl.particle[i].cx < 0 || gl.particle[i].cx > gl.xres) {
           gl.particle[i] = gl.particle[gl.particleCount - 1];
           gl.particleCount--;      
       }
    }
}

void makeParticle()
{
    gl.particle[gl.particleCount].cx = mainChar.cx;
    gl.particle[gl.particleCount].cy = mainChar.cy;
    gl.particle[gl.particleCount].velocity = gl.particleVelocity;
    gl.particle[gl.particleCount].direction = gl.directionFlag;
    gl.particleCount++;
}

void shootParticle()
{
    if(gl.oneOffShootFlag == true) {
        printf("Shoot\n");
        makeParticle(); 
        gl.oneOffShootFlag = false;
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
    if (gl.camera[0] > 0)
        sprt->cx = sprt->cx + gl.movementSpeed;
}

void moveSpriteLeft(Sprite *sprt)
{
    sprt->cx = sprt->cx - gl.movementSpeed;
}

void jump()
{
    printf("Jump\n");
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
    // When character reaches max height, decrement to highest tile on x coord
    if (gl.isJumpingFlag == 1 && gl.jumpDirectionFlag == 0) {
        if (mainChar.cy > gl.initialJumpCy) {
            mainChar.cy = mainChar.cy - ((gl.finalJumpCy - mainChar.cy) * gl.jumpRate) - 1;
        }
        if (mainChar.cy <= 85) {
            //modyify this later to set to highest tile level
             mainChar.cy = 85;
            gl.isJumpingFlag = 0;
        }
    }
}

void checkTilesForMovement()
{
    //if current height is higher than current tile height
    //cant move.
    //jump to change current height.
    //if current height is higher or equal, can move to that tile
    // have a global variable for this to allow other sprites to move or not
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

    if (gl.keys[XK_Right] == 1 || gl.keys[XK_Left] == 1) {
        particleMove();
    }
    if (gl.keys[XK_space] == 0) {
        gl.oneOffShootFlag = true;
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
    //glTranslated(mainChar.pos[0], mainChar.pos[1], 0);
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
    //works best with
    //conditionalRenders(tx, ty, -16, w, 16, h);
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
        glTexCoord2f(tx + 1, ty + 1); glVertex2i(speedboost1.cx-w, speedboost1.cy-h);
        glTexCoord2f(tx + 1,     ty); glVertex2i(speedboost1.cx-w, speedboost1.cy+h);
        glTexCoord2f(tx,        ty ); glVertex2i(speedboost1.cx+w, speedboost1.cy+h);
        glTexCoord2f(tx,     ty + 1); glVertex2i(speedboost1.cx+w, speedboost1.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx == speedboost1.cx) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            printf("Picked up speed boost! Movement Speed: + 0.2!\n");
            gl.speedboost1Flag = false;
            spriteDisappear(&speedboost1);
            gl.movementSpeed = gl.movementSpeed + 0.2;
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
        glTexCoord2f(tx + 1, ty + 1); glVertex2i(shield1.cx-w, shield1.cy-h);
        glTexCoord2f(tx + 1, ty    ); glVertex2i(shield1.cx-w, shield1.cy+h);
        glTexCoord2f(tx,     ty    ); glVertex2i(shield1.cx+w, shield1.cy+h);
        glTexCoord2f(tx,     ty + 1); glVertex2i(shield1.cx+w, shield1.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx > (shield1.cx - 10) && mainChar.cx < (shield1.cx + 10)) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            printf("Picked up Shield!\n");
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
        glTexCoord2f(tx + 1, ty + 1); glVertex2i(heart1.cx-w, heart1.cy-h);
        glTexCoord2f(tx + 1, ty    ); glVertex2i(heart1.cx-w, heart1.cy+h);
        glTexCoord2f(tx,     ty    ); glVertex2i(heart1.cx+w, heart1.cy+h);
        glTexCoord2f(tx,     ty + 1); glVertex2i(heart1.cx+w, heart1.cy-h);
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
            printf("Picked up Health Pack! Health + 5\n");
            if (mainChar.health < 30) {
                mainChar.health = mainChar.health + 5;
                if (mainChar.health > 30)
                    mainChar.health = 30;
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
        glTexCoord2f(tx + 1, ty + 1); glVertex2i(heart2.cx-w, heart2.cy-h);
        glTexCoord2f(tx + 1, ty    ); glVertex2i(heart2.cx-w, heart2.cy+h);
        glTexCoord2f(tx,     ty    ); glVertex2i(heart2.cx+w, heart2.cy+h);
        glTexCoord2f(tx,     ty + 1); glVertex2i(heart2.cx+w, heart2.cy-h);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_ALPHA_TEST);
        if (mainChar.cx > (heart2.cx - 10) && mainChar.cx < (heart2.cx + 10)) {
            //if character picks up power up,
            //stop rendering and set x to -999999 to avoid
            //picking up invisible power ups
            gl.heart2Flag = false;
            printf("Picked up Health Pack! Health + 5\n");
            spriteDisappear(&heart2);
            if (mainChar.health < 30) {
                mainChar.health = mainChar.health + 5;
                if (mainChar.health > 30)
                    mainChar.health = 30;
            }
        }
    }
}

void christianInit()
{
    //initialize my sprites' x and y positions
    mainChar.cy = 85;
    shield1.cx = 650;
    shield1.cy = 90;
    heart1.cx = 700;
    heart1.cy = 90;
    heart2.cx = 800;
    heart2.cy = 90;
    speedboost1.cx= 750;
    speedboost1.cy = 90;
}
void renderChristianSprites()
{
    renderMainCharacter();
    renderShield1();
    renderSpeedboost1();
    renderHeart1();
    renderHeart2();
    particlePhysics();
}
