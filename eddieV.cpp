//Modified by: Eddie Velasco
//Date: June 20, 2017
//Purpose: Group Project source code
//
// Source code for generating level from 
// background, tiles, and foreground. Also
// will include functionality for offscreen
// death falls, power-ups, health bar display
// and end of level completion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "ppm.h"
#include "fonts.h"
#include "eddieV.h"
#include "game.h"

void renderBackground()
{
//render background for level
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2i(0,0);
		glTexCoord2f(0.0, 0.0); glVertex2i(0, 600);
		glTexCoord2f(1.0, 0.0); glVertex2i(800, 600);
		glTexCoord2f(1.0, 1.0); glVertex2i(800, 0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void renderPlatform()
{
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, gl.platformTexture);
	float x = gl.xres;
	float y = 100;
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2i(-x,-y);
		glTexCoord2f(0.0, 0.0); glVertex2i(-x, y);
		glTexCoord2f(1.0, 0.0); glVertex2i(x, y);
		glTexCoord2f(1.0, 1.0); glVertex2i(x,-y);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void deathPit()
{
//Check for offscreen falling into pit which will kill and restart player
}
void powerUp()
{
//power ups
}
void healthBar(int xres, int yres)
{
//generate a healthbar on top left of the screen
	Rect r;
	unsigned int c = 0x002d88d8;
	r.bot = yres-20;
	r.left = (xres/xres) + 10;
	r.center = 0;
	ggprint8b(&r, 16, c, "HEALTH BAR");
	Shape s;
	Shape box[5];
	for (int i = 0; i < 5; i++) {
		box[i].width = 10;
		box[i].height = 3;
		box[i].center.x = r.left + 25;
		box[i].center.y = 570 - (i*8);
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
}
void levelCompletion ()
{
//reach the end of level will head to next level or credits
}
