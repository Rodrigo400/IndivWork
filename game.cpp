
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
//#include "rodrigoG.h"
#include "game.h"


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


Global gl;


//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void initOpengl(void);
void cleanupXWindows(void);
void checkKeys(XEvent *e);
void render(void);

extern void logo(int,int);
extern void start_menu(int, int);
extern void characterselection_menu(int, int);
extern void levelselection_menu(int, int);
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

/*class Global
{
    public:
	int done;
	int keys[65536];
	int menu_position;
	int xres, yres;

	Ppmimage *logoImage;
	Ppmimage *playImage;
	Ppmimage *settingsImage;
	Ppmimage *highscoresImage;
	Ppmimage *creditsImage;
	Ppmimage *exitImage;
	Ppmimage *texthighlightImage;
	Ppmimage *levelselectionImage;
	Ppmimage *characterselectionImage;
	Ppmimage *frameImage;
	
	GLuint logoTexture;
	GLuint playTexture;
	GLuint settingsTexture;
	GLuint highscoresTexture;
	GLuint creditsTexture;
	GLuint exitTexture;
	GLuint texthighlightTexture;
	GLuint levelselectionTexture;
	GLuint characterselectionTexture;
	GLuint frameTexture;
	
	bool display_startmenu;
	bool display_settingsmenu;
	bool display_highscoresmenu;
	bool display_creditsmenu;
	bool display_characterselectionmenu;
	bool display_levelselectionmenu;

	Global()
	{
	    xres = 800;
	    yres = 600;
	    done = 0;
	    menu_position = 1;

	        logoImage = NULL;
		playImage = NULL;
		settingsImage = NULL;
		highscoresImage = NULL;
		creditsImage = NULL;
		exitImage = NULL;
		texthighlightImage = NULL;
		levelselectionImage = NULL;
		characterselectionImage = NULL;
		frameImage = NULL;
	
		display_startmenu = false;
		display_settingsmenu = false;
		display_highscoresmenu = false;
		display_creditsmenu = false;
		display_characterselectionmenu = false;
		display_levelselectionmenu = false;
	}
} gl;*/


//---------------------------------------------------------
/*Global
Ppmimage *logoImage = NULL;
Ppmimage *playImage = NULL;
Ppmimage *settingsImage = NULL;
Ppmimage *highscoresImage = NULL;
Ppmimage *creditsImage = NULL;
Ppmimage *exitImage = NULL;
Ppmimage *texthighlightImage = NULL;
Ppmimage *levelselectionImage = NULL;
Ppmimage *characterselectionImage = NULL;
Ppmimage *frameImage = NULL;

GLuint logoTexture;
GLuint playTexture;
GLuint settingsTexture;
GLuint highscoresTexture;
GLuint creditsTexture;
GLuint exitTexture;
GLuint texthighlightTexture;
GLuint levelselectionTexture;
GLuint characterselectionTexture;
GLuint frameTexture;

int keys[65536];
int menu_position = 1;
int done = 0;
bool display_startmenu = false;
bool display_settingsmenu = false;
bool display_highscoresmenu = false;
bool display_creditsmenu = false;
bool display_characterselectionmenu = false;
bool display_levelselectionmenu = false;
*/
//---------------------------------------------------------

int main(void)
{
    initXWindows();
    initOpengl();
    while (!gl.done) {
	while (XPending(dpy)) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    checkKeys(&e);
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

    convertpng2ppm();

    getImage();

    generateTextures();

    //===============================================================
    // Logo
    int w = gl.logoImage->width;
    int h = gl.logoImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.logoTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *logoData = buildAlphaData(gl.logoImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, logoData);
    free(logoData);
    unlink("./images/OgirdorLogo.ppm");
    //===============================================================

    //===============================================================
    // Play
    w = gl.playImage->width;
    h = gl.playImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.playTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *playData = buildAlphaData(gl.playImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, playData);
    free(playData);
    unlink("./images/Play.ppm");
    //===============================================================

    //===============================================================
    // Settings
    w = gl.settingsImage->width;
    h = gl.settingsImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.settingsTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *settingsData = buildAlphaData(gl.settingsImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, settingsData);
    free(settingsData);
    unlink("./images/Settings.ppm");
    //===============================================================

    //===============================================================
    // High Scores
    w = gl.highscoresImage->width;
    h = gl.highscoresImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.highscoresTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *highscoresData = buildAlphaData(gl.highscoresImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, highscoresData);
    free(highscoresData);
    unlink("./images/HighScores.ppm");
    //===============================================================

    //===============================================================
    // Credits
    w = gl.creditsImage->width;
    h = gl.creditsImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.creditsTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *creditsData = buildAlphaData(gl.creditsImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, creditsData);
    free(creditsData);
    unlink("./images/Credits.ppm");
    //===============================================================

    //===============================================================
    // Exit
    w = gl.exitImage->width;
    h = gl.exitImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.exitTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *exitData = buildAlphaData(gl.exitImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, exitData);
    free(exitData);
    unlink("./images/Exit.ppm");
    //===============================================================

    //===============================================================
    // Highlight
    w = gl.texthighlightImage->width;
    h = gl.texthighlightImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.texthighlightTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *texthighlightData = buildAlphaData(gl.texthighlightImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, texthighlightData);
    free(exitData);
    unlink("./images/TextHighlight.ppm");
    //===============================================================

    //===============================================================
    // Level Selection Background
    w = gl.levelselectionImage->width;
    h = gl.levelselectionImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.levelselectionTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *levelselectionData = buildAlphaData(gl.levelselectionImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, levelselectionData);
    free(levelselectionData);
    unlink("./images/LevelSelection.ppm");
    //===============================================================

    //===============================================================
    // Character Selection Background
    w = gl.characterselectionImage->width;
    h = gl.characterselectionImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.characterselectionTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *characterselectionData = buildAlphaData(gl.characterselectionImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, characterselectionData);
    free(characterselectionData);
    unlink("./images/CharacterSelection.ppm");
    //===============================================================

    //===============================================================
    // Frame Background
    w = gl.frameImage->width;
    h = gl.frameImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.frameTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *frameData = buildAlphaData(gl.frameImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, frameData);
    free(frameData);
    unlink("./images/Frame.ppm");
    //===============================================================

    //-------------------------------------------------------------------------
}

void checkKeys(XEvent *e)
{
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyRelease)
    {
	gl.keys[key] = 0;
	if (key == XK_Shift_L || key == XK_Shift_R)
	    return;
    }
    if (e->type == KeyPress)
    {
	gl.keys[key] = 1;
	if (key == XK_Shift_L || key == XK_Shift_R)
	    return;
    }
    else
	return;

    switch(key)
    {
	case XK_Escape:
	    gl.done = 1;
	    break;
	case XK_Down:
	    if (gl.display_startmenu 
		    && !gl.display_characterselectionmenu
		    && gl.menu_position != 5)
		gl.menu_position++;
	    else if (gl.display_characterselectionmenu 
		    && !gl.display_startmenu 
		    && gl.menu_position != 2)
		gl.menu_position++;
	    break;
	case XK_Up:
	    if (gl.display_startmenu 
		    && !gl.display_characterselectionmenu
		    && gl.menu_position != 1)
		gl.menu_position--;
	    else if (gl.display_characterselectionmenu 
		    && !gl.display_startmenu
		    && gl.menu_position != 1)
		gl.menu_position--;
	    break;
	    //case XK_Return:
	    //	if (menu_position == 1)
	    //	{


    }
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

	start_menu(gl.xres, gl.yres);

	if (gl.display_characterselectionmenu)
	{
	    characterselection_menu(gl.xres, gl.yres);
	    /*if (display_characterselectionmenu && display_levelselectionmenu == true)
	      levelselection_menu(gl.xres, gl.yres);
	      */
	}

    }



