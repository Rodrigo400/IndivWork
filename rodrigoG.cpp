// Created By: Rodrigo Garcia-Novoa
// Date: 6/15/17
// Purpose: Video Game Project Side Scroller

//===============================================
// Responsibilities and What the code does
//===============================================
// Create Main Menu
// Create Character Selection Menu
// Create Level Selection Menu
// Displaying

//===============================================
// Week 4 Progress
//===============================================
// Main Menu, Level Selection Menu, and Character
// Selection Menu both display and scroll. 
// Working on the logic for changing the display
// of screens with flags.
//===============================================

//===============================================
// Week 5 Progress
//===============================================
// Added Main Menu Background Image
//===============================================

//===============================================
// Week 6 Progress
//===============================================
// Trying menu system logic
// Finished Player name input for high scores
//===============================================

//===============================================
// Week 7 Progress
//===============================================
// 80% menu logic working
// Forward and backward menu flow
// Tutorial Page
//===============================================

//===============================================
// Week 8 Progress
//===============================================
// Made Characters with projectiles:
// 	Donald Trump
// 	Cyborg
// 	Purple Helmet
// 	Molten Girl
//===============================================

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
//#include "ppm.cpp"
#include "fonts.h"
#include "game.h"

using namespace std;

// Global Instance
Shape *s;
NameBox nb1; 

// Function Prototypes
void start_menu(int, int);
void playername_menu(int, int, char [], UserInput &input);
void characterselection_menu(int, int);
void levelselection_menu(int, int);
void tutorial_menu(int, int);
void tutorial_menu2(int, int);
void view_highscores();
void credits_screen(int, int); 
void shootingPoseRight(int);
void shootingPoseLeft(int);
void standingPose(int);
void getPlayerName(int, UserInput &input);
void assign_playername(char [], UserInput &input);
void PlayerStart(int, char [], UserInput &input);
void removePPM(void);
int menu_position_highlight;
unsigned int white = 0xffffff;

void start_menu(int xres, int yres)
{
    //glClearColor(0.0f,0.0f,0.0f,1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1) {
        highlight_x = xres/2;
        highlight_y = yres*0.6;
    } else if (gl.menu_position == 2) {
        highlight_x = xres/2;
        highlight_y = yres*0.5;
    } else if (gl.menu_position == 3) {
        highlight_x = xres/2;
        highlight_y = yres*0.4;
    } else if (gl.menu_position == 4) {
        highlight_x = xres/2;
        highlight_y = yres*0.3;
    } else if (gl.menu_position == 5) {
        highlight_x = xres/2;
        highlight_y = yres*0.2;
    }

    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Text Highlight===================================
    //=================================================
    float h = 10;
    float w = 240;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(highlight_x, highlight_y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Logo Display=====================================
    //=================================================
    h = 100;	
    w = 275;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.8, 0);
    glBindTexture(GL_TEXTURE_2D, gl.logoTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Play Display=====================================
    //=================================================
    h = 50;
    w = 100;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.6, 0);
    glBindTexture(GL_TEXTURE_2D, gl.playTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Tutorial Display=================================
    //=================================================
    h = 50;
    w = 170;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.485, 0);
    glBindTexture(GL_TEXTURE_2D, gl.tutorialTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //High Scores Display==============================
    //=================================================
    h = 50;
    w = 225;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.39, 0);
    glBindTexture(GL_TEXTURE_2D, gl.highscoresTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Credits Display==================================
    //=================================================
    h = 90;
    w = 150;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.3, 0);
    glBindTexture(GL_TEXTURE_2D, gl.creditsTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Exit Display=====================================
    //=================================================
    h = 50;
    w = 75;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.2, 0);
    glBindTexture(GL_TEXTURE_2D, gl.exitTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    if (gl.keys[XK_Return]) {
        if (gl.menu_position == 1) {
            gl.display_startmenu = false;
            gl.display_playernamemenu = true;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 2) {
            gl.display_startmenu = false;
            gl.display_tutorialmenu = true;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 3) {
            gl.display_startmenu = false;
            gl.display_highscoresmenu = true;
        } else if (gl.menu_position == 4) {
            gl.display_startmenu = false;
            gl.display_creditsmenu = true;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 5) {
            gl.display_startmenu = false;
            gl.done = 1;
        }
    }	
}

void tutorial_menu(int xres, int yres)
{
    //glClearColor(1.0,1.0,1.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    //glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Black Box========================================
    //=================================================
    float h = 600;
    float w = 600; 
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(gl.xres*0.5, gl.xres*0.5, 0);
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //=================================================

    //=================================================
    //Attack Dmg Power Up==============================
    //=================================================
    h = 20;
    w = 20;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.273, gl.yres*0.31, 0);
    glBindTexture(GL_TEXTURE_2D, gl.attackdmgTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Heart Power Up===================================
    //=================================================
    h = 20;
    w = 20;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.273, gl.yres*0.245, 0);
    glBindTexture(GL_TEXTURE_2D, gl.heartaddTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Shield Power Up==================================
    //=================================================
    h = 20;
    w = 20;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.273, gl.yres*0.18, 0);
    glBindTexture(GL_TEXTURE_2D, gl.shieldTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Speed Boost Power Up=============================
    //=================================================
    h = 20;
    w = 20;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.273, gl.yres*0.11, 0);
    glBindTexture(GL_TEXTURE_2D, gl.speedboostTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Turret===========================================
    //=================================================
    h = 25;
    w = 25;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.6, gl.yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.turretTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    standingPose(xres);

    Rect r;    

    r.bot = yres*0.89;
    r.left = xres*0.235;
    r.center = yres/2;
    for (int i = 0; i < 26; i++) {
        ggprint13(&r, 20, white, "||");
    }

    r.bot = yres*0.89;
    r.left = xres*0.77;
    r.center = yres/2;
    for (int i = 0; i < 26; i++) {
        ggprint13(&r, 20, white, "||");
    }

    r.bot = yres*0.9;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "                 Objective                    ");
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "Stuff here                                    ");
    ggprint13(&r, 20, white, "and here                                      ");
    ggprint13(&r, 20, white, "and here                                      ");

    r.bot = yres*0.65;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "               Player/Enemies                 "); 
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "Stuff here                                    ");
    ggprint13(&r, 20, white, "and here                                      ");
    ggprint13(&r, 20, white, "and here                                      ");

    r.bot = yres*0.4;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "                 Power Ups                    ");
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "     Attack Damage: Increases player's damage ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "       Health: Increases player's health      ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "      Shield: Shields player for one hit      ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "      Speed: Increases player's movement speed");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "==============================================");
    
    r.bot = yres*0.1;
    r.left = xres*0.9;
    r.center = yres/2;
    ggprint13(&r, 20, white, "1/2");

    if (gl.keys[XK_Return]) {
        gl.display_tutorialmenu = false;
        gl.display_tutorialmenu2 = true;
        gl.keys[XK_Return] = false;
    }

    if (gl.keys[XK_Tab]) {
        if (gl.display_tutorialmenu) {
            gl.display_tutorialmenu = false;
            gl.display_startmenu = true;
            gl.keys[XK_Tab] = false;
        }
    }
} 

void tutorial_menu2(int xres, int yres)
{
    //glClearColor(1.0,1.0,1.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    //glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Black Box========================================
    //=================================================
    float h = 600;
    float w = 600;
    
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(gl.xres*0.5, gl.xres*0.5, 0);
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //=================================================

    //=================================================
    //Tab Key==========================================
    //=================================================
    h = 25;
    w = 33;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.39, gl.yres*0.775, 0);
    glBindTexture(GL_TEXTURE_2D, gl.tabkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Left Arrow Key===================================
    //=================================================
    h = 25;
    w = 25;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.36, gl.yres*0.575, 0);
    glBindTexture(GL_TEXTURE_2D, gl.leftarrowkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Right Arrow Key==================================
    //=================================================
    h = 25;
    w = 25;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.425, gl.yres*0.575, 0);
    glBindTexture(GL_TEXTURE_2D, gl.rightarrowkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Spacebar Key=====================================
    //=================================================
    h = 20;
    w = 60;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.39, gl.yres*0.475, 0);
    glBindTexture(GL_TEXTURE_2D, gl.spacebarkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Up Arrow Key=====================================
    //=================================================
    h = 25;
    w = 25;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.36, gl.yres*0.675, 0);
    glBindTexture(GL_TEXTURE_2D, gl.uparrowkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Down Arrow Key=====================================
    //=================================================
    h = 25;
    w = 25;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.425, gl.yres*0.675, 0);
    glBindTexture(GL_TEXTURE_2D, gl.uparrowkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================


    //=================================================
    //Enter Key========================================
    //=================================================
    h = 22;
    w = 50;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(gl.xres*0.395, gl.yres*0.375, 0);
    glBindTexture(GL_TEXTURE_2D, gl.enterkeyTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    Rect r;    

    r.bot = yres*0.89;
    r.left = xres*0.235;
    r.center = yres/2;
    for (int i = 0; i < 26; i++) {
        ggprint13(&r, 20, white, "||");
    }

    r.bot = yres*0.89;
    r.left = xres*0.77;
    r.center = yres/2;
    for (int i = 0; i < 26; i++) {
        ggprint13(&r, 20, white, "||");
    }

    r.bot = yres*0.05;
    r.left = xres*0.38;
    r.center = yres/2;
    Shape s;
    Shape box[5];
    for (int i = 0; i < 5; i++) {
        box[i].width = 10;
        box[i].height = 3;
        box[i].center.x = r.left + 15;
        box[i].center.y = 160 - (i*8);
        box[i].center.z = 0;
        s = box[i];
        glPushMatrix();
        glColor3ub(255, 0, 255);
        glTranslatef(s.center.x, s.center.y, s.center.z);
        float w = s.width;
        float h = s.height;
        glBegin(GL_QUADS);
        glVertex2i(-w, -h);
        glVertex2i(-w, h);
        glVertex2i(w, h);
        glVertex2i(w, -h);
        glEnd();
        glPopMatrix();
    }

    r.bot = yres*0.9;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "                  Controls                    ");
    ggprint13(&r, 20, white, "==============================================");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                            Go Back a Page    ");
    ggprint13(&r, 20, white, "                                              ");

    r.bot = yres*0.68;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "                           Jump               ");
    ggprint13(&r, 20, white, "                            Navigate Up/Down  ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                            Move Left/Right   ");
    ggprint13(&r, 20, white, "                           Navigate Left/Right");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                            Shoot             ");

    r.bot = yres*0.4;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                           Select/Start/Accept");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "                             Health           ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "   __     __  __                              ");
    ggprint13(&r, 20, white, "    |    | o  __| __|        Timer/Score      ");
    ggprint13(&r, 20, white, "  |__| o |__  __|                             ");
    ggprint13(&r, 20, white, "                                              ");
    ggprint13(&r, 20, white, "==============================================");

    r.bot = yres*0.1;
    r.left = xres*0.9;
    r.center = yres/2;
    ggprint13(&r, 20, white, "2/2");

    if (gl.keys[XK_Return]) {
        gl.display_tutorialmenu2 = false;
        gl.display_startmenu = true;
        gl.keys[XK_Return] = false;
    }

    if (gl.keys[XK_Tab]) {
        if (gl.display_tutorialmenu) {
            gl.display_tutorialmenu2 = false;
            gl.display_tutorialmenu = true;
            gl.keys[XK_Tab] = false;
        }
    }
} 


void playername_menu(int xres, int yres, char player_name[], UserInput &input)
{
    //glClearColor(0.0f,0.0f,0.0f,1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_GREATER, 0.0f);
    //glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //unsigned int white = 0xffffff;
    //unsigned int black = 0x00000000;
    float w, h;

    //Namebox nb1;
    //Shape s;

    nb1.box[0].width = 100;
    nb1.box[0].height = 15;
    nb1.box[0].center.x = xres/2;
    nb1.box[0].center.y = yres/2;
    glColor3ub(0, 255, 255);
    s = &nb1.box[0];
    glPushMatrix();
    glTranslatef(s->center.x, s->center.y, 0);
    w = s->width;
    h = s->height;
    glBegin(GL_QUADS);
    glVertex2i(-w,-h);
    glVertex2i(-w,h);
    glVertex2i(w,h);
    glVertex2i(w,-h);
    glEnd();
    glPopMatrix();

    Rect r;

    r.bot = s->center.y + 50;
    r.left = s->center.x;
    r.center = s->center.y;
    ggprint13(&r, 20, white, "ENTER PLAYER NAME");
    ggprint13(&r, 20, white, "Accept with 'Enter'");

    r.bot = s->center.y - 8;
    r.left = s->center.x;
    r.center = s->center.y;
    ggprint13(&r, 20, white, "%s", input.player_name);

    /*if (gl.keys[XK_Tab])
      {
      if (!gl.display_startinggame)
      {
      gl.display_playernamemenu = false;
      gl.display_startmenu = true;
      }
      else
      {
      if (player_name[0] == '\0')
      return;
      else
      {
      gl.display_playernamemenu = false;
      gl.display_startmenu = true;
      }
      }
      }*/

    if (gl.keys[XK_Return]) {
        gl.display_playernamemenu = false;
        gl.display_characterselectionmenu = true;
        gl.keys[XK_Return] = false;
        if (player_name[0] == '\0')
            return;
    }
    
    if (gl.keys[XK_Tab]) {
        gl.display_playernamemenu = false;
        gl.display_startmenu = true;
        gl.keys[XK_Tab] = false;
    }
}

void getPlayerName(int key, UserInput &input)
{
    if (key >= XK_a && key <= XK_z){
        char keyin[2];
        keyin[0] = key;
        keyin[1] = '\0';
        strcat(input.player_name, keyin);
        return;
    }
    
    if (key == XK_BackSpace) {
        int slen = strlen(input.player_name);
        if (slen > 0) {
            input.player_name[slen-1] = '\0';
        }
        return;
    }
}

void PlayerStart(int key, char player_name[], UserInput &input)
{
    getPlayerName(key, input);
    assign_playername(player_name, input);
    /*if (gl.keys[XK_Return] && player_name[0] != '\0')
      {
      gl.display_playername = false;
      gl.display_characterselectionmenu = true;
      }*/
}

void assign_playername(char player_name[], UserInput &input)
{
    for (int i = 0; i < 15; i++)
        player_name[i] = input.player_name[i];
}

void characterselection_menu(int xres, int yres)
{
    //glClearColor(1.0,1.0,1.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1) {
        highlight_x = xres*0.22;
        highlight_y = yres*0.68;
    } else if (gl.menu_position == 2) {
        highlight_x = xres*0.5;
        highlight_y = yres*0.68;
    } else if (gl.menu_position == 3) {
        highlight_x = xres*0.78;
        highlight_y = yres*0.68;
    } else if (gl.menu_position == 4) {
        highlight_x = xres*0.22;
        highlight_y = yres*0.31;
    } else if (gl.menu_position == 5) {
        highlight_x = xres*0.5;
        highlight_y = yres*0.31;
    } else if (gl.menu_position == 6) {
        highlight_x = xres*0.78;
        highlight_y = yres*0.31;
    }

    //=================================================
    //Background Display for Character Selection=======
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.characterselectionTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Text Highlight===================================
    //=================================================
    float h = 125;
    float w = 125;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(highlight_x, highlight_y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 1 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.22, yres*0.31, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 2 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.5, yres*0.31, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 3 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.78, yres*0.31, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 4 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.22, yres*0.68, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 5 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.5, yres*0.68, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 6 Display==================================
    //=================================================
    h = 80;	
    w = 80;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.78, yres*0.68, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Char 1 Display==================================
    //=================================================
    float cy = yres*0.68;
    float cx = xres*0.22;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter1Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.maincharacterFrame % 4;
    int iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Char 2 Display===================================
    //=================================================
    cy = yres*0.68;
    cx = xres*0.5;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter2Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    ix = gl.maincharacterFrame % 4;
    iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Char 3 Display===================================
    //=================================================
    cy = yres*0.68;
    cx = xres*0.78;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter3Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    ix = gl.maincharacterFrame % 4;
    iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Char 4 Display===================================
    //=================================================
    cy = yres*0.33;
    cx = xres*0.22;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter4Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    ix = gl.maincharacterFrame % 4;
    iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Char 5 Display===================================
    //=================================================
    cy = yres*0.33;
    cx = xres*0.5;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter4Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    ix = gl.maincharacterFrame % 4;
    iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Char 6 Display===================================
    //=================================================
    cy = yres*0.33;
    cx = xres*0.78;
    h = 50.0;
    w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacter4Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    ix = gl.maincharacterFrame % 4;
    iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

	Rect r;    

    r.bot = yres/2 - 250;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "CHARACTER SELECTION");

    if (gl.keys[XK_Return]) {
        if (gl.menu_position == 1) {
            //gl.characterSelect = 1;
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 2) {
            //gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false; 
        } else if (gl.menu_position == 3) {
            //gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 4) {
            //gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 5) {
            //gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false;
        } else if (gl.menu_position == 6) {
            //gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.menu_position = 1;
            gl.keys[XK_Return] = false;
	}
    }

    if (gl.keys[XK_Tab]) {
        gl.display_characterselectionmenu = false;
        gl.display_playernamemenu = true;
        gl.menu_position = 1;
        gl.keys[XK_Tab] = false;
    }
}

void levelselection_menu(int xres, int yres)
{
    //glClearColor(0.0f,0.0f,0.0f,1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1) {
        highlight_x = xres*0.25;
        highlight_y = yres*0.5;
    } else if (gl.menu_position == 2) {
        highlight_x = xres*0.75;
        highlight_y = yres*0.5;
    }

    //=================================================
    //Background Display for Level Selection===========
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.levelselectionTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Text Highlight===================================
    //=================================================
    float h = 175;
    float w = 175;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(highlight_x, highlight_y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 1 Display==================================
    //=================================================
    h = 100;	
    w = 100;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.75, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Frame 2 Display==================================
    //=================================================
    h = 100;	
    w = 100;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.75, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Level 1 Display==================================
    //=================================================
    h = 72;	
    w = 72;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.25, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    //=================================================
    //Level 2 Display==================================
    //=================================================
    h = 72;	
    w = 72;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.75, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    Rect r;    

    r.bot = yres/2 - 250;
    r.left = xres/2;
    r.center = yres/2;
    ggprint13(&r, 20, white, "LEVEL SELECTION");

    if (gl.keys[XK_Return]) {
        if (gl.menu_position == 1) {
            gl.levelSelect = 1;
            gl.display_characterselectionmenu = false;
            gl.display_startinggame = true;
            gl.keys[XK_Return] = false;
            //gl.display_levelselectionmenu = false;
            //gl.state = GAMEPLAY;
        } else if (gl.menu_position == 2) {
            gl.levelSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_startinggame = true;
            gl.keys[XK_Return] = false;
            //gl.display_levelselectionmenu = false;
            //gl.state = GAMEPLAY;
        }
    }

    if (gl.keys[XK_Tab]) {
        gl.display_levelselectionmenu = false;
        gl.display_characterselectionmenu = true;
        gl.menu_position = 1;
        gl.keys[XK_Tab] = false;
    }
}

void credits_screen(int xres, int yres)
{
    //glClearColor(1.0,1.0,1.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_TEXTURE_2D);
    //=================================================

    shootingPoseLeft(xres); 
    shootingPoseRight(xres);

    Rect r;

    r.bot = yres/2 + 50;
    r.left = xres/2;
    r.center = yres/2;

    //unsigned int white = 0xffffff;
    ggprint13(&r, 16, white, "Developers");
    ggprint13(&r, 16, white, "=======================");
    ggprint13(&r, 16, white, "Christian Capusi");
    ggprint13(&r, 16, white, "Cesar Loya");
    ggprint13(&r, 16, white, "Rodrigo Garcia-Novoa");
    ggprint13(&r, 16, white, "Eddie Velasco");
    ggprint13(&r, 16, white, "Simran Singh");

    if (gl.keys[XK_Tab]) {
        if (gl.display_creditsmenu) {
            gl.display_creditsmenu = false;
            gl.display_startmenu = true;
        }
    }

    if (gl.keys[XK_Return]) {
        if (gl.display_creditsmenu) {
            gl.display_creditsmenu = false;
            gl.display_startmenu = true;
            gl.keys[XK_Return] = false;
        }
    }
}

void standingPose(int xres)
{
    float cy = 310;
    float cx = xres/3.5;
    float h = 40.0;
    float w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacterTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.maincharacterFrame % 4;
    int iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy       ); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy       ); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
}

void shootingPoseRight(int xres)
{
    float cy = 300;
    float cx = xres/5.0;
    float h = 150.0;
    float w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacterTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.maincharacterFrame % 4;
    int iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix + .25, iy + .666); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix      , iy + .666); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
}

void shootingPoseLeft(int xres)
{
    float cy = 300;
    float cx = xres*(4.0/5.0);
    float h = 150.0;
    float w = h * .903;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.maincharacterTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    int ix = gl.maincharacterFrame % 4;
    int iy = 3;
    glBegin(GL_QUADS);
    glTexCoord2f(ix      , iy + .666); glVertex2i(cx+w,cy-h);
    glTexCoord2f(ix + .25, iy + .666); glVertex2i(cx-w,cy-h);
    glTexCoord2f(ix + .25, iy + .333); glVertex2i(cx-w,cy+h);
    glTexCoord2f(ix      , iy + .333); glVertex2i(cx+w,cy+h);
    glEnd();
    glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
}

// Problem with PPM files not unlinking
void removePPM(void)
{
    remove("./images/mainChar1.ppm");
    remove("./images/mainChar2.ppm");
    remove("./images/mainChar3.ppm");
    remove("./images/mainChar4.ppm");
    remove("./images/OgirdorLogo.ppm");
    remove("./images/MainMenuBackground.ppm");
    remove("./images/Play.ppm");
    remove("./images/Tutorial.ppm");
    remove("./images/HighScores.ppm");
    remove("./images/Credits.ppm");
    remove("./images/Exit.ppm");
    remove("./images/TextHighlight.ppm");
    remove("./images/LevelSelection.ppm");
    remove("./images/CharacterSelection.ppm");
    remove("./images/Frame.ppm");
    remove("./images/backgroundImage.ppm");
    remove("./images/platformImage.ppm");
    remove("./images/AttackDmg.ppm");
    remove("./images/BlueEnemy.ppm");
    remove("./images/GreenEnemy.ppm");
    remove("./images/HeartAdd.ppm");
    remove("./images/RedEnemy.ppm");
    remove("./images/Shield.ppm");
    remove("./images/SpeedBoost.ppm");
    remove("./images/TabKey.ppm");
    remove("./images/LeftArrowKey.ppm");
    remove("./images/RightArrowKey.ppm");
    remove("./images/SpacebarKey.ppm");
    remove("./images/UpArrowKey.ppm");
    remove("./images/EnterKey.ppm");
    remove("./images/BlueBox.ppm");
    remove("./images/AmericaBall.ppm");
    remove("./images/MoltenBall.ppm");
    remove("./images/PurpleBall.ppm");
}

/*void view_highscores()
{
//have link to HTML page for high scores
}*/


