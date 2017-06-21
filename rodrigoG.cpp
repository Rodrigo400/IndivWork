// Created By: Rodrigo Garcia-Novoa
// Game Project
// Date 6/15/17

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
#include "ppm.cpp"
#include "fonts.h"

using namespace std;

void start_menu(int, int);
void level_selection_menu(int, int);
int menu_position_highlight;
void convertpng2ppm(void);
void cleanupPPM(void);
void logo(int, int);

/*void controls_menu();
  void music_menu();
  void view_high_scores_menu();
  void exit_menu();

  void choose_player_menu();
  void playerName();
  void get_playerName();
  void assign_playerName();
 */

extern Ppmimage *logoImage;

extern GLuint logoTexture;

void start_menu(int xres, int yres)
{
        unsigned int blue = 0x0000ff;
        Rect r;
        r.bot = yres - 400;
        r.left = xres/2 - 55;
        r.center = 0;
        ggprint13(&r, 16, blue, "Play Game");  
        ggprint13(&r, 16, blue, "Options");
        ggprint13(&r, 16, blue, "View High Scores");
        ggprint13(&r, 16, blue, "Exit Game");

}

void convertpng2ppm(void)
{
        system("convert ./images/OgirdorLogo.png ./images/OgirdorLogo.ppm");
}

void getImage(void)
{
        logoImage = ppm6GetImage("./images/OgirdorLogo.ppm");
}

void generateTextures(void)
{
        glGenTextures(1, &logoTexture);
}

void logo(int xres, int yres)
{
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.6, 0);
        glBindTexture(GL_TEXTURE_2D, logoTexture);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glColor4ub(255,255,255,255);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2i(-200,-50);
            glTexCoord2f(0.0, 0.0); glVertex2i(-200,50);
            glTexCoord2f(1.0, 0.0); glVertex2i(200,50);
            glTexCoord2f(1.0, 1.0); glVertex2i(200,-50);
        glEnd(); 
        glPopMatrix();
}

void cleanupPPM(void)
{
        remove("./images/OgirdorLogo.ppm");
}
