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
#include "ppm.cpp"
#include "fonts.h"

using namespace std;

void start_menu(int, int);
void characterselection_menu(int, int);
void levelselection_menu(int, int);
int menu_position_highlight;
void convertpng2ppm(void);
void cleanupPPM(void);
void settings_menu(int, int);
void view_highscores();
void credits_screen(int, int); 

extern Ppmimage *logoImage;
extern Ppmimage *playImage;
extern Ppmimage *settingsImage;
extern Ppmimage *highscoresImage;
extern Ppmimage *creditsImage;
extern Ppmimage *exitImage;
extern Ppmimage *texthighlightImage;
extern Ppmimage *levelselectionImage;
extern Ppmimage *characterselectionImage;
extern Ppmimage *frameImage;

extern GLuint logoTexture;
extern GLuint playTexture;
extern GLuint settingsTexture;
extern GLuint highscoresTexture;
extern GLuint creditsTexture;
extern GLuint exitTexture;
extern GLuint texthighlightTexture;
extern GLuint levelselectionTexture;
extern GLuint characterselectionTexture;
extern GLuint frameTexture;

extern int menu_position;
extern int keys[];
extern int done;

extern bool display_startmenu;
extern bool display_settingsmenu;
extern bool display_highscoresmenu;
extern bool display_creditsmenu;
extern bool display_characterselectionmenu;
extern bool display_levelselectionmenu;

void start_menu(int xres, int yres)
{
    display_startmenu = 1;

	int highlight_x;
	int highlight_y;

	if (menu_position == 1)
	{
		highlight_x = xres/2;
		highlight_y = yres*0.6;
	}
	else if (menu_position == 2)
	{
		highlight_x = xres/2;
		highlight_y = yres*0.5;
	}
	else if (menu_position == 3)
	{
		highlight_x = xres/2;
		highlight_y = yres*0.4;
	}
	else if (menu_position == 4)
	{
		highlight_x = xres/2;
		highlight_y = yres*0.3;
	}
	else if (menu_position == 5)
	{
		highlight_x = xres/2;
		highlight_y = yres*0.2;
	}

	
	//=================================================
	//Text Highlight===================================
	//=================================================
	float h = 10;
	float w = 240;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(highlight_x, highlight_y, 0);
	glBindTexture(GL_TEXTURE_2D, texthighlightTexture);
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
	glBindTexture(GL_TEXTURE_2D, logoTexture);
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
	glBindTexture(GL_TEXTURE_2D, playTexture);
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
	glBindTexture(GL_TEXTURE_2D, settingsTexture);
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
	glBindTexture(GL_TEXTURE_2D, highscoresTexture);
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
	glBindTexture(GL_TEXTURE_2D, creditsTexture);
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
	glBindTexture(GL_TEXTURE_2D, exitTexture);
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
	
	if (keys[XK_Return])
	{
		if (menu_position == 1)
		{
			display_startmenu = false;
			display_characterselectionmenu = true;
		}
		else if (menu_position == 2)
		{
			display_startmenu = false;
			display_settingsmenu = true;
		}
		else if (menu_position == 3)
		{
			display_startmenu = false;
			display_highscoresmenu = true;
		}
		else if (menu_position == 4)
		{
			display_startmenu = false;
			display_creditsmenu = true;
		}
		else if (menu_position == 5)
		{
			display_startmenu = false;
            done = 1;
		}
	}	
}

void characterselection_menu(int xres, int yres)
{
    display_startmenu = false;

	int highlight_x;
	int highlight_y;

	if (menu_position == 1)
	{
		highlight_x = xres*0.25;
		highlight_y = yres*0.5;
	}
	else if (menu_position == 2)
	{
		highlight_x = xres*0.75;
		highlight_y = yres*0.5;
	}

	//=================================================
	//Background Display for Character Selection=======
	//=================================================
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, characterselectionTexture);
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
	
	//=================================================
	//Text Highlight===================================
	//=================================================
	float h = 175;
	float w = 175;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(highlight_x, highlight_y, 0);
	glBindTexture(GL_TEXTURE_2D, texthighlightTexture);
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
	glBindTexture(GL_TEXTURE_2D, frameTexture);
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
	glBindTexture(GL_TEXTURE_2D, frameTexture);
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
	
	/*if (keys[XK_Return])
	{
		if (menu_position == 1)
		{
			display_characterselectionmenu = false;
			display_levelselectionmenu = true;
		}
		else if (menu_position == 2)
		{
			display_characterselectionmenu = false;
			display_levelselectionmenu = true;
		}
	}*/
}

void levelselection_menu(int xres, int yres)
{
	int highlight_x;
	int highlight_y;

	if (menu_position == 1)
	{
		highlight_x = xres*0.25;
		highlight_y = yres*0.5;
	}
	else if (menu_position == 2)
	{
		highlight_x = xres*0.75;
		highlight_y = yres*0.5;
	}

	//=================================================
	//Background Display for Level Selection===========
	//=================================================
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, levelselectionTexture);
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
	glBindTexture(GL_TEXTURE_2D, texthighlightTexture);
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
	glBindTexture(GL_TEXTURE_2D, frameTexture);
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
	glBindTexture(GL_TEXTURE_2D, frameTexture);
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


void convertpng2ppm(void)
{
	system("convert ./images/OgirdorLogo.png ./images/OgirdorLogo.ppm");
	system("convert ./images/Play.png ./images/Play.ppm");
	system("convert ./images/Settings.png ./images/Settings.ppm");
	system("convert ./images/HighScores.png ./images/HighScores.ppm");
	system("convert ./images/Credits.png ./images/Credits.ppm");
	system("convert ./images/Exit.png ./images/Exit.ppm");
	system("convert ./images/TextHighlight.png ./images/TextHighlight.ppm");
	system("convert ./images/LevelSelection.png ./images/LevelSelection.ppm");
	system("convert ./images/CharacterSelection.png ./images/CharacterSelection.ppm");
	system("convert ./images/Frame.png ./images/Frame.ppm");	
}

void getImage(void)
{
	logoImage = ppm6GetImage("./images/OgirdorLogo.ppm");
	playImage = ppm6GetImage("./images/Play.ppm");
	settingsImage = ppm6GetImage("./images/Settings.ppm");
	highscoresImage = ppm6GetImage("./images/HighScores.ppm");
	creditsImage = ppm6GetImage("./images/Credits.ppm");
	exitImage = ppm6GetImage("./images/Exit.ppm");
	texthighlightImage = ppm6GetImage("./images/TextHighlight.ppm");
	levelselectionImage = ppm6GetImage("./images/LevelSelection.ppm");
	characterselectionImage = ppm6GetImage("./images/CharacterSelection.ppm");
	frameImage = ppm6GetImage("./images/Frame.ppm");
}

void generateTextures(void)
{
	glGenTextures(1, &logoTexture);
	glGenTextures(1, &playTexture);
	glGenTextures(1, &settingsTexture);
	glGenTextures(1, &highscoresTexture);		
	glGenTextures(1, &creditsTexture);
	glGenTextures(1, &exitTexture);
	glGenTextures(1, &texthighlightTexture);
	glGenTextures(1, &levelselectionTexture);
	glGenTextures(1, &characterselectionTexture);
	glGenTextures(1, &frameTexture);
}

void cleanupPPM(void)
{
	remove("./images/OgirdorLogo.ppm");
	remove("./images/Play.ppm");
	remove("./images/Settings.ppm");
	remove("./images/HighScores.ppm");
	remove("./images/Credits.ppm");
	remove("./images/Exit.ppm");
	remove("./images/TextHighlight.ppm");
	remove("./images/LevelSelection.ppm");
	remove("./images/CharacterSelection.ppm");
	remove("./images/Frame.ppm");
}
