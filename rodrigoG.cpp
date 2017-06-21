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
extern Ppmimage *playImage;
extern Ppmimage *settingsImage;
extern Ppmimage *highscoresImage;
extern Ppmimage *creditsImage;
extern Ppmimage *exitImage;

extern GLuint logoTexture;
extern GLuint playTexture;
extern GLuint settingsTexture;
extern GLuint highscoresTexture;
extern GLuint creditsTexture;
extern GLuint exitTexture;

void start_menu(int xres, int yres)
{
        /*unsigned int blue = 0x0000ff;
        Rect r;
        r.bot = yres - 400;
        r.left = xres/2 - 55;
        r.center = 0;
        ggprint13(&r, 16, blue, "Play Game");  
        ggprint13(&r, 16, blue, "Options");
        ggprint13(&r, 16, blue, "View High Scores");
        ggprint13(&r, 16, blue, "Exit Game");
		*/

		//=================================================
		//Logo Display=====================================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.8, 0);
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
		//=================================================
		
		//=================================================
		//Play Display=====================================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.7, 0);
        glBindTexture(GL_TEXTURE_2D, playTexture);
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
		//=================================================

		//=================================================
		//Settings Display=================================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.6, 0);
        glBindTexture(GL_TEXTURE_2D, settingsTexture);
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
		//=================================================
	
		
		//=================================================
		//High Scores Display==============================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.5, 0);
        glBindTexture(GL_TEXTURE_2D, highscoresTexture);
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
		//=================================================
		
		//=================================================
		//Credits Display==================================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.4, 0);
        glBindTexture(GL_TEXTURE_2D, creditsTexture);
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
		//=================================================
		
		//=================================================
		//Exit Display=====================================
		//=================================================
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
		glTranslatef(xres/2, yres*0.3, 0);
        glBindTexture(GL_TEXTURE_2D, exitTexture);
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
		//=================================================
		
}

void convertpng2ppm(void)
{
        system("convert ./images/OgirdorLogo.png ./images/OgirdorLogo.ppm");
        system("convert ./images/Play.png ./images/Play.ppm");
        system("convert ./images/Settings.png ./images/Settings.ppm");
        system("convert ./images/HighScores.png ./images/HighScores.ppm");
        system("convert ./images/Credits.png ./images/Credits.ppm");
        system("convert ./images/Exit.png ./images/Exit.ppm");
}

void getImage(void)
{
        logoImage = ppm6GetImage("./images/OgirdorLogo.ppm");
        playImage = ppm6GetImage("./images/Play.ppm");
        settingsImage = ppm6GetImage("./images/Settings.ppm");
        highscoresImage = ppm6GetImage("./images/HighScores.ppm");
        creditsImage = ppm6GetImage("./images/Credits.ppm");
        exitImage = ppm6GetImage("./images/Exit.ppm");
}

void generateTextures(void)
{
        glGenTextures(1, &logoTexture);
        glGenTextures(1, &playTexture);
        glGenTextures(1, &settingsTexture);
        glGenTextures(1, &highscoresTexture);		
        glGenTextures(1, &creditsTexture);
        glGenTextures(1, &exitTexture);
}

/*void logo(int xres, int yres)
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
}*/

void cleanupPPM(void)
{
        remove("./images/OgirdorLogo.ppm");
        remove("./images/Play.ppm");
        remove("./images/Settings.ppm");
        remove("./images/HighScores.ppm");
        remove("./images/Credits.ppm");
        remove("./images/Exit.ppm");
}
