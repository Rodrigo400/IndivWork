// Main Function of Game


// Declare GLuint Textures


// Declare PPM Images


// Removing PPM Images


// Converting PPM Images


// Getting PPM Images


// Generating Textures 


// Use functions to BindTextures and Display


// Core Functions such as check_keys, render


//modified by: Rodrigo Garcia-Novoa
//date modified: 6/12/17
//Purpose: Add explosion and animation in both directions with moving back
//
//3350
//program: walk.cpp
//author:  Gordon Griesel
//date:    summer 2017
//
//Walk cycle using a sprite sheet.
//images courtesy: http://games.ucla.edu/resource/walk-cycles/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
#include "ppm.h"
#include "fonts.h"
#include "rodrigoG.h"


//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
							 (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define ALPHA 1

//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void initOpengl(void);
void cleanupXWindows(void);
//void checkKeys(XEvent *e);
void render(void);

extern void logo(int,int);
extern void start_menu(int, int);
extern void convertpng2ppm(void);
extern void getImage(void);
extern void generateTextures(void);


//-----------------------------------------------------------------------------
//Setup timers
class Timers {
	public:
		double physicsRate;
		double oobillion;
		struct timespec timeStart, timeEnd, timeCurrent;
		struct timespec walkTime, explosionTime;
		Timers() {
			physicsRate = 1.0 / 30.0;
			oobillion = 1.0 / 1e9;
		}
		double timeDiff(struct timespec *start, struct timespec *end) {
			return (double)(end->tv_sec - start->tv_sec ) +
				(double)(end->tv_nsec - start->tv_nsec) * oobillion;
		}
		void timeCopy(struct timespec *dest, struct timespec *source) {
			memcpy(dest, source, sizeof(struct timespec));
		}
		void recordTime(struct timespec *t) {
			clock_gettime(CLOCK_REALTIME, t);
		}
} timers;
//-----------------------------------------------------------------------------

class Global
{
	public:
		int xres, yres;
		int done;
		Global()
		{
			xres = 800;
			yres = 600;
			done = 0;
		}
} gl;


//---------------------------------------------------------
//Global
//int xres = 800;
//int yres = 600;
//int done = 0;
//---------------------------------------------------------

Ppmimage *logoImage = NULL;
Ppmimage *playImage = NULL;
Ppmimage *settingsImage = NULL;
Ppmimage *highscoresImage = NULL;
Ppmimage *creditsImage = NULL;
Ppmimage *exitImage = NULL;

GLuint logoTexture;
GLuint playTexture;
GLuint settingsTexture;
GLuint highscoresTexture;
GLuint creditsTexture;
GLuint exitTexture;

int main(void)
{
	initXWindows();
	initOpengl();
	while (!gl.done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			//checkKeys(&e);
		}
		render();
		glXSwapBuffers(dpy, win);
	}
	cleanupXWindows();
	cleanup_fonts();
	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void setTitle(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "3350 - Walk Cycle");
}

void setupScreenRes(const int w, const int h)
{
	gl.xres = w;
	gl.yres = h;
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;
	setupScreenRes(gl.xres, gl.yres);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
			vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa);
	GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	setTitle();
}

void reshapeWindow(int width, int height)
{
	//window has been resized.
	setupScreenRes(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
	setTitle();
}

unsigned char *buildAlphaData(Ppmimage *img)
{
	//add 4th component to RGB stream...
	int i;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	unsigned char a,b,c;
	//use the first pixel in the image as the transparent color.
	unsigned char t0 = *(data+0);
	unsigned char t1 = *(data+1);
	unsigned char t2 = *(data+2);
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		*(ptr+3) = 1;
		if (a==t0 && b==t1 && c==t2)
			*(ptr+3) = 0;
		//-----------------------------------------------
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void initOpengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, gl.xres, gl.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, gl.xres, 0, gl.yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	//
	//
	//
	//Load logo
	//system("convert ./images/OgirdorLogo.png ./images/OgirdorLogo.ppm");

	convertpng2ppm();

	getImage();

	generateTextures();

	//===============================================================
	// Logo
	int w = logoImage->width;
	int h = logoImage->height;	
	glBindTexture(GL_TEXTURE_2D, logoTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *logoData = buildAlphaData(logoImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, logoData);
	free(logoData);
	unlink("./images/OgirdorLogo.ppm");
	//===============================================================

	//===============================================================
	// Play
	w = playImage->width;
	h = playImage->height;	
	glBindTexture(GL_TEXTURE_2D, playTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *playData = buildAlphaData(playImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, playData);
	free(playData);
	unlink("./images/Play.ppm");
	//===============================================================

	//===============================================================
	// Settings
	w = settingsImage->width;
	h = settingsImage->height;	
	glBindTexture(GL_TEXTURE_2D, settingsTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *settingsData = buildAlphaData(settingsImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, settingsData);
	free(settingsData);
	unlink("./images/Settings.ppm");

	//===============================================================

	//===============================================================
	// High Scores
	w = highscoresImage->width;
	h = highscoresImage->height;	
	glBindTexture(GL_TEXTURE_2D, highscoresTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *highscoresData = buildAlphaData(highscoresImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, highscoresData);
	free(highscoresData);
	unlink("./images/HighScores.ppm");
	//===============================================================

	//===============================================================
	// Credits
	w = creditsImage->width;
	h = creditsImage->height;	
	glBindTexture(GL_TEXTURE_2D, creditsTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *creditsData = buildAlphaData(creditsImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, creditsData);
	free(creditsData);
	unlink("./images/Credits.ppm");
	//===============================================================

	//===============================================================
	// Exit
	w = exitImage->width;
	h = exitImage->height;	
	glBindTexture(GL_TEXTURE_2D, exitTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *exitData = buildAlphaData(exitImage);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, exitData);
	free(exitData);
	unlink("./images/Exit.ppm");
	//===============================================================
	//-------------------------------------------------------------------------
}

Flt VecNormalize(Vec vec)
{
	Flt len, tlen;
	Flt xlen = vec[0];
	Flt ylen = vec[1];
	Flt zlen = vec[2];
	len = xlen*xlen + ylen*ylen + zlen*zlen;
	if (len == 0.0) {
		MakeVector(0.0,0.0,1.0,vec);
		return 1.0;
	}
	len = sqrt(len);
	tlen = 1.0 / len;
	vec[0] = xlen * tlen;
	vec[1] = ylen * tlen;
	vec[2] = zlen * tlen;
	return(len);
}

void render(void)
{
	//Clear the screen
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//float cx = gl.xres/2.0;
	//float cy = gl.yres/2.0;

	//=================================================
	//Logo Display=====================================
	//=================================================
	float h = 100;
	float w = 275;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(gl.xres/2, gl.yres*0.8, 0);
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
	glTranslatef(gl.xres/2, gl.yres*0.6, 0);
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
	glTranslatef(gl.xres/2, gl.yres*0.5, 0);
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
	glTranslatef(gl.xres/2, gl.yres*0.4, 0);
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
	glTranslatef(gl.xres/2, gl.yres*0.3, 0);
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
	glTranslatef(gl.xres/2, gl.yres*0.2, 0);
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






	//start_menu(gl.xres, gl.yres);

	//logo(gl.xres, gl.yres);

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_ALPHA_TEST);	
}


