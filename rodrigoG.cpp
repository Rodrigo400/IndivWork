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
void playername_menu(int, int);
void characterselection_menu(int, int);
void levelselection_menu(int, int);
void settings_menu(int, int);
void view_highscores();
void credits_screen(int, int); 
int menu_position_highlight;


void start_menu(int xres, int yres)
{
    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1)
    {
        highlight_x = xres/2;
        highlight_y = yres*0.6;
    }
    else if (gl.menu_position == 2)
    {
        highlight_x = xres/2;
        highlight_y = yres*0.5;
    }
    else if (gl.menu_position == 3)
    {
        highlight_x = xres/2;
        highlight_y = yres*0.4;
    }
    else if (gl.menu_position == 4)
    {
        highlight_x = xres/2;
        highlight_y = yres*0.3;
    }
    else if (gl.menu_position == 5)
    {
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
    float h = 10;
    float w = 240;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(highlight_x, highlight_y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Settings Display=================================
    //=================================================
    h = 50;
    w = 150;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.settingsTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //High Scores Display==============================
    //=================================================
    h = 50;
    w = 200;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres/2, yres*0.4, 0);
    glBindTexture(GL_TEXTURE_2D, gl.highscoresTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //=================================================

    if (gl.keys[XK_Return])
    {
        if (gl.menu_position == 1)
        {
            gl.display_startmenu = false;
            gl.display_characterselectionmenu = true;
            //gl.display_playernamemenu = true;
            gl.state = CHARACTERSELECTIONMENU;
        }
        else if (gl.menu_position == 2)
        {
            gl.display_startmenu = false;
            gl.display_settingsmenu = true;
            gl.menu_position = 1;
        }
        else if (gl.menu_position == 3)
        {
            gl.display_startmenu = false;
            gl.display_highscoresmenu = true;
        }
        else if (gl.menu_position == 4)
        {
            gl.display_startmenu = false;
            gl.display_creditsmenu = true;
        }
        else if (gl.menu_position == 5)
        {
            gl.display_startmenu = false;
            gl.done = 1;
        }
    }	
}

void playername_menu(int xres, int yres)
{
    //=================================================
    //Main Menu Background=============================
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    //glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    //unsigned int white = 0xffffff00;
    unsigned int black = 0x00000000;
    float w, h;

    //Namebox nb1;
    //Shape s;

    nb1.box[0].width = 100;
    nb1.box[0].height = 15;
    nb1.box[0].center.x = xres/2;
    nb1.box[0].center.y = yres/2;
    glColor3ub(252, 246, 179);
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

    r.bot = s->center.y + 30;
    r.left = s->center.x;
    r.center = s->center.y;
    ggprint13(&r, 20, black, "%s");

    if (gl.keys[XK_Return])
    {
        gl.display_playernamemenu = false;
        gl.display_characterselectionmenu = true;
    }
}

void characterselection_menu(int xres, int yres)
{
    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1)
    {
        highlight_x = xres*0.25;
        highlight_y = yres*0.5;
    }
    else if (gl.menu_position == 2)
    {
        highlight_x = xres*0.75;
        highlight_y = yres*0.5;
    }

    //=================================================
    //Background Display for Character Selection=======
    //=================================================
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.characterselectionTexture);
    //glEnable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Frame 1 Display==================================
    //=================================================
    h = 100;	
    w = 100;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(xres*0.25, yres*0.5, 0);
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    //glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    if (gl.keys[XK_Return])
    {
        if (gl.menu_position == 1)
        {
            gl.characterSelect = 1;
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.state = LEVELSELECTIONMENU;
        }
        else if (gl.menu_position == 2)
        {
            gl.characterSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            gl.display_levelselectionmenu = true;
            gl.state = LEVELSELECTIONMENU;
        }
    }
}

void levelselection_menu(int xres, int yres)
{
    int highlight_x;
    int highlight_y;

    if (gl.menu_position == 1)
    {
        highlight_x = xres*0.25;
        highlight_y = yres*0.5;
    }
    else if (gl.menu_position == 2)
    {
        highlight_x = xres*0.75;
        highlight_y = yres*0.5;
    }

    //=================================================
    //Background Display for Level Selection===========
    //=================================================
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, gl.levelselectionTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
    glTexCoord2f(0.0, 0.0); glVertex2i(0,yres);
    glTexCoord2f(1.0, 0.0); glVertex2i(xres,yres);
    glTexCoord2f(1.0, 1.0); glVertex2i(xres,0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
    //=================================================

    //=================================================
    //Text Highlight===================================
    //=================================================
    float h = 150;
    float w = 150;
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(highlight_x, highlight_y, 0);
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
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
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0); glVertex2i(-w,-h);
    glTexCoord2f(0.0, 0.0); glVertex2i(-w,h);
    glTexCoord2f(1.0, 0.0); glVertex2i(w,h);
    glTexCoord2f(1.0, 1.0); glVertex2i(w,-h);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_ALPHA_TEST);
    //=================================================

    if (gl.keys[XK_Return])
    {
        if (gl.menu_position == 1)
        {
            gl.levelSelect = 1;
            gl.display_characterselectionmenu = false;
            //gl.display_levelselectionmenu = false;
            gl.state = GAMEPLAY;
        }
        else if (gl.menu_position == 2)
        {
            gl.levelSelect = 1;        // need to change later
            gl.display_characterselectionmenu = false;
            //gl.display_levelselectionmenu = false;
            gl.state = GAMEPLAY;
        }
    }


}


/*void settings_menu(int xres, int yres)
  {
//whatever setting ideas here, like music or something
}

void view_highscores()
{
//have link to HTML page for high scores
}

void credits_screen(int xres, int yres)
{
//display credits here, developers names
}
*/

