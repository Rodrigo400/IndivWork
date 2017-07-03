/*===============================================
//                  Ogirdor
//===============================================
Created By:
Rodrigo Garcia-Novoa
Christian Capusi
Eddie Velasco
Cesar Loya
Simran S.

Original Framework by:
Gordon Griesel

//===============================================
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif
#include "ppm.h"
#include "fonts.h"
#include "game.h"
using namespace std;

//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt Matrix[4][4];

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

//===============================================
// Global Instance
//===============================================
Global gl;
Sprite turret, enemy1, mariEnemy;

//X Windows variables
Display *dpy;
Window win;

//function prototypes
void initXWindows(void);
void init();
void initOpengl(void);
void cleanupXWindows(void);
void checkResize(XEvent *e);
void checkKeys(XEvent *e);
void physics(void);
void render(void);

extern void logo(int,int);
extern void start_menu(int, int);
extern void characterselection_menu(int, int);
extern void levelselection_menu(int, int);
extern void playername_menu(int, int);

extern Ppmimage *characterImage(int);
extern Ppmimage *turretImage();
extern Ppmimage *enemy1image();
extern Ppmimage *mari_image();
extern void shootWalkRight(float,float,float,float,float,float);
extern void shootWalkLeft(float,float,float,float,float,float);
extern void shootStandRight(float,float,float,float,float,float);
extern void shootStandLeft(float,float,float,float,float,float);
extern void standRight(float,float,float,float,float,float);
extern void standLeft(float,float,float,float,float,float);
extern void renderMainCharacter();
extern void clearScreen();
extern void moveSpriteRight(Sprite *);
extern void moveSpriteLeft(Sprite *);
extern void csound(const char *a);
extern void showTurret();
extern void showenemy1();
extern void show_mari();
extern void renderBackground();
extern void renderPlatform();
extern void healthBar(int, int);
//-----------------------------------------------------------------------------
//Setup timers
class Timers
{
    public:
        double physicsRate;
        double oobillion;
        struct timespec timeStart, timeEnd, timeCurrent;
        struct timespec maincharacterTime;
        Timers()
        {
            physicsRate = 1.0 / 30.0;
            oobillion = 1.0 / 1e9;
        }
        double timeDiff(struct timespec *start, struct timespec *end)
        {
            return (double)(end->tv_sec - start->tv_sec ) +
                (double)(end->tv_nsec - start->tv_nsec) * oobillion;
        }
        void timeCopy(struct timespec *dest, struct timespec *source)
        {
            memcpy(dest, source, sizeof(struct timespec));
        }
        void recordTime(struct timespec *t)
        {
            clock_gettime(CLOCK_REALTIME, t);
        }
} timers;
//-----------------------------------------------------------------------------

int main(void)
{
    initXWindows();
    initOpengl();
    init();
    csound("./sound/a.wav");
    while (!gl.done) {
        while (XPending(dpy)) {
            XEvent e;
            XNextEvent(dpy, &e);
            checkResize(&e);
            //checkMouse(&e);
            checkKeys(&e);
        } 
        physics();
        render();
        glXSwapBuffers(dpy, win);
    }
    cleanupXWindows();
    cleanup_fonts();
    return 0;
}

void init()
{
    //put initial x coordinates of enemies here.
    //can be offscreen. You can also set y here
    enemy1.cx = 600;
    mariEnemy.cx = 100;
    turret.cx = 300;
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
    XStoreName(dpy, win, "3350 - Ogirdor");
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
    //load the images file into a ppm structure.
    //

    //---CHRISTIANS FUNCTION--------//
    int characterSelect = 1; //Rodrigo, when you make selection in char selection, 
    //store it in something similar

    // Convertpng2ppm
    //system("convert ./images/mainChar.png ./images/mainChar.ppm");
    system("convert ./images/OgirdorLogo.png ./images/OgirdorLogo.ppm");
    system("convert ./images/MainMenuBackground.png ./images/MainMenuBackground.ppm");
    system("convert ./images/Play.png ./images/Play.ppm");
    system("convert ./images/Settings.png ./images/Settings.ppm");
    system("convert ./images/HighScores.png ./images/HighScores.ppm");
    system("convert ./images/Credits.png ./images/Credits.ppm");
    system("convert ./images/Exit.png ./images/Exit.ppm");
    system("convert ./images/TextHighlight.png ./images/TextHighlight.ppm");
    system("convert ./images/LevelSelection.png ./images/LevelSelection.ppm");
    system("convert ./images/CharacterSelection.png ./images/CharacterSelection.ppm");
    system("convert ./images/Frame.png ./images/Frame.ppm");
    system("convert ./images/backgroundImage.png ./images/backgroundImage.ppm");
    system("convert ./images/platformImage.png ./images/platformImage.ppm");

    //===========================================================
    // Get Images	
    //===========================================================
    gl.maincharacterImage = characterImage(characterSelect);
    gl.logoImage = ppm6GetImage("./images/OgirdorLogo.ppm");
    gl.mainmenubackgroundImage = ppm6GetImage("./images/MainMenuBackground.ppm");
    gl.playImage = ppm6GetImage("./images/Play.ppm");
    gl.settingsImage = ppm6GetImage("./images/Settings.ppm");
    gl.highscoresImage = ppm6GetImage("./images/HighScores.ppm");
    gl.creditsImage = ppm6GetImage("./images/Credits.ppm");
    gl.exitImage = ppm6GetImage("./images/Exit.ppm");
    gl.texthighlightImage = ppm6GetImage("./images/TextHighlight.ppm");
    gl.levelselectionImage = ppm6GetImage("./images/LevelSelection.ppm");
    gl.characterselectionImage = ppm6GetImage("./images/CharacterSelection.ppm");
    gl.frameImage = ppm6GetImage("./images/Frame.ppm");
    gl.turretImage = turretImage();
    gl.enemy1Image = enemy1image();
    gl.mari_image = mari_image();
    gl.backgroundImage = ppm6GetImage("./images/backgroundImage.ppm");
    gl.platformImage = ppm6GetImage("./images/platformImage.ppm");
    //===========================================================

    //===========================================================
    // Generate Textures
    //===========================================================
    glGenTextures(1, &gl.maincharacterTexture);
    glGenTextures(1, &gl.mainmenubackgroundTexture);
    glGenTextures(1, &gl.turretTexture);
    glGenTextures(1, &gl.enemy1Texture);
    glGenTextures(1, &gl.mari_Texture);
    glGenTextures(1, &gl.logoTexture);
    glGenTextures(1, &gl.playTexture);
    glGenTextures(1, &gl.settingsTexture);
    glGenTextures(1, &gl.highscoresTexture);
    glGenTextures(1, &gl.creditsTexture);
    glGenTextures(1, &gl.exitTexture);
    glGenTextures(1, &gl.texthighlightTexture);
    glGenTextures(1, &gl.levelselectionTexture);
    glGenTextures(1, &gl.characterselectionTexture);
    glGenTextures(1, &gl.frameTexture);
    glGenTextures(1, &gl.backgroundTexture);
    glGenTextures(1, &gl.platformTexture);
    //===========================================================

    //==============================================
    // Main Character
    int w = gl.maincharacterImage->width;
    int h = gl.maincharacterImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.maincharacterTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *maincharacterData = buildAlphaData(gl.maincharacterImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, maincharacterData);
    free(maincharacterData);
    unlink("./images/mainChar.ppm");
    //==============================================

    //==============================================
    // Main Menu Backgoround
    w = gl.mainmenubackgroundImage->width;
    h = gl.mainmenubackgroundImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.mainmenubackgroundTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *mainmenubackgroundData = 
        buildAlphaData(gl.mainmenubackgroundImage);	
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, mainmenubackgroundData);
    free(mainmenubackgroundData);
    unlink("./images/MainMenuBackground.ppm");
    //==============================================

    //==============================================
    //TURRET
    w = gl.turretImage->width;
    h = gl.turretImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.turretTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *turretData = buildAlphaData(gl.turretImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, turretData);
    free(turretData);
    unlink("./images/Turret.ppm");
    //====================================================

    //====================================================
    //ENEMY1
    w = gl.enemy1Image->width;
    h = gl.enemy1Image->height;
    glBindTexture(GL_TEXTURE_2D, gl.enemy1Texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *enemy1Data = buildAlphaData(gl.enemy1Image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, enemy1Data);
    free(enemy1Data);
    unlink("./images/enemy1.ppm");
    //===================================================

    //===================================================
    //Maricesces
    w = gl.mari_image->width;
    h = gl.mari_image->height; 
    glBindTexture(GL_TEXTURE_2D, gl.mari_Texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *mari_pointer = buildAlphaData(gl.mari_image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, mari_pointer);
    free(mari_pointer); 
    unlink("./images/Enemy_Mariachi_3.ppm");
    //====================================================

    //===============================================================
    // Logo
    w = gl.logoImage->width;
    h = gl.logoImage->height;
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

    //===============================================================
    //Level Background
    w = gl.backgroundImage->width;
    h = gl.backgroundImage->height;	
    glBindTexture(GL_TEXTURE_2D, gl.backgroundTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *backgroundData = buildAlphaData(gl.backgroundImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, backgroundData);
    free(backgroundData);
    unlink("./images/backgroundImage.ppm");
    //===============================================================

    //===============================================================
    //Level Platform
    w = gl.platformImage->width;
    h = gl.platformImage->height;
    glBindTexture(GL_TEXTURE_2D, gl.platformTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *platformData = buildAlphaData(gl.platformImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, platformData);
    free(platformData);
    unlink("./images/platformImage.ppm");
    //===============================================================

    //--------------------------------------------------------------------
}

void checkResize(XEvent *e)
{
    //The ConfigureNotify is sent by the
    //server if the window is resized.
    if (e->type != ConfigureNotify)
        return;
    XConfigureEvent xce = e->xconfigure;
    if (xce.width != gl.xres || xce.height != gl.yres) {
        //Window size did change.
        reshapeWindow(xce.width, xce.height);
    }
}

void checkKeys(XEvent *e)
{
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyRelease) {
        gl.keys[key] = 0;
        if (key == XK_Shift_L || key == XK_Shift_R)
            return;
    }
    if (e->type == KeyPress) {
        gl.keys[key] = 1;
        if (key == XK_Shift_L || key == XK_Shift_R)
            return;
    } else { 
        return;
    }

    switch(key)
    {
        case XK_Escape:
            gl.done = 1;
            break;
        case XK_Down:
            if (gl.state == STARTMENU && gl.menu_position != 5) 
            {
                gl.menu_position++;
            }
            break;
        case XK_Up:
            if (gl.state == STARTMENU && gl.menu_position != 1) 
            {
                gl.menu_position--;
            }
            break;
        case XK_Left:
            if ((gl.state == CHARACTERSELECTIONMENU || 
                        gl.state == LEVELSELECTIONMENU) 
                    && gl.menu_position != 1) 
            {
                gl.menu_position--;
            }
        case XK_Right:
            if ((gl.state == CHARACTERSELECTIONMENU || 
                        gl.state == LEVELSELECTIONMENU) 
                    && gl.menu_position != 2) 
            {
                gl.menu_position++;
            }
        case XK_Return:
            if (gl.state == STARTMENU && gl.display_startmenu)
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

            /*if (gl.display_playernamemenu)
              {
              gl.display_playernamemenu = false;
              gl.display_characterselectionmenu = true;
              }*/

            if (gl.state == CHARACTERSELECTIONMENU && 
                    gl.display_characterselectionmenu)
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
                    gl.characterSelect = 1;     // need to change
                    gl.display_characterselectionmenu = false;
                    gl.display_levelselectionmenu = true;
                    gl.state = LEVELSELECTIONMENU;
                }
            }

            if (gl.state == LEVELSELECTIONMENU)
            {
                if (gl.menu_position == 1)
                {
                    gl.levelSelect = 1;
                    gl.display_levelselectionmenu = false;
                    gl.display_levelselectionmenu = true;
                    gl.state = GAMEPLAY;
                }
                else if (gl.menu_position == 2)
                {
                    gl.levelSelect = 1;     // need to change
                    gl.display_levelselectionmenu = false;
                    gl.display_levelselectionmenu = true;
                    gl.state = GAMEPLAY;
                }
            }
    }
}

void physics(void)
{
    if (gl.walk && gl.directionFlag == 0) {
        //man is walking...
        //when time is up, advance the frame.
        timers.recordTime(&timers.timeCurrent);
        double timeSpan =
            timers.timeDiff(&timers.maincharacterTime,
                    &timers.timeCurrent);
        if (timeSpan > gl.delay) {
            //advance
            ++gl.maincharacterFrame;

            moveSpriteLeft(&mariEnemy);
            moveSpriteLeft(&turret);
            moveSpriteLeft(&enemy1);

            if (gl.maincharacterFrame >= 8)
                gl.maincharacterFrame -= 8;
            timers.recordTime(&timers.maincharacterTime);
        }
    } else if (gl.walk && gl.directionFlag == 1) {
        //man is walking...
        //when time is up, advance the frame.
        timers.recordTime(&timers.timeCurrent);
        double timeSpan =
            timers.timeDiff(&timers.maincharacterTime,
                    &timers.timeCurrent);
        if (timeSpan > gl.delay) {
            //advance
            ++gl.maincharacterFrame;
            mariEnemy.cx++;
            moveSpriteRight(&mariEnemy);
            moveSpriteRight(&turret);
            moveSpriteRight(&enemy1);
            if (gl.maincharacterFrame >= 8)
                gl.maincharacterFrame -= 8;
            timers.recordTime(&timers.maincharacterTime);
        }
    }
    if (gl.walk || gl.keys[XK_Right]) {
        //man is walking...
        //when time is up, advance the frame.
        moveSpriteLeft(&mariEnemy);
        moveSpriteLeft(&turret);
        moveSpriteLeft(&enemy1);
        timers.recordTime(&timers.timeCurrent);
        double timeSpan =
            timers.timeDiff(&timers.maincharacterTime,
                    &timers.timeCurrent);
        if (timeSpan > gl.delay) {
            //advance
            ++gl.maincharacterFrame;
            if (gl.maincharacterFrame >= 8)
                gl.maincharacterFrame -= 8;
            timers.recordTime(&timers.maincharacterTime);
        }
    }
    if (gl.walk || gl.keys[XK_Left]) {
        //man is walking...
        //when time is up, advance the frame.
        moveSpriteRight(&mariEnemy);
        moveSpriteRight(&turret);
        moveSpriteRight(&enemy1);
        timers.recordTime(&timers.timeCurrent);
        double timeSpan =
            timers.timeDiff(&timers.maincharacterTime,
                    &timers.timeCurrent);
        if (timeSpan > gl.delay) {
            //advance
            ++gl.maincharacterFrame;
            if (gl.maincharacterFrame >= 8)
                gl.maincharacterFrame -= 8;
            timers.recordTime(&timers.maincharacterTime);
        }
    }
}

void render(void)
{
    if (gl.state == STARTMENU && gl.display_startmenu)
    {
        start_menu(gl.xres, gl.yres);
    }

    //if (gl.state == CHARACTERSELECTIONMENU && gl.display_characterselectionmenu)
    if (gl.state == GAMEPLAY)
    {
        characterselection_menu(gl.xres, gl.yres);
    }

    if (gl.state == LEVELSELECTIONMENU && gl.display_levelselectionmenu)
    {
        levelselection_menu(gl.xres, gl.yres);
    }

    if (gl.state == GAMEPLAY)
    {
        clearScreen();	
        renderBackground();
        renderPlatform();
        renderMainCharacter();
        showTurret();
        showenemy1();
        show_mari();
        healthBar(gl.xres, gl.yres);
    }

    /*switch (gl.state)
      {
      case STARTMENU:
      start_menu(gl.xres, gl.yres);
      break;
      case CHARACTERSELECTIONMENU:
      characterselection_menu(gl.xres, gl.yres);
      break;
      case LEVELSELECTIONMENU:
      levelselection_menu(gl.xres, gl.yres);
      break;
      case GAMEPLAY:
      clearScreen();	
      renderBackground();
      renderPlatform();
      renderMainCharacter();
      showTurret();
      showenemy1();
      show_mari();
      healthBar(gl.xres, gl.yres);
      break;
      default:
      break;
      }*/
}





// Automatically show start menu
/*if (gl.display_startmenu)
  {
  start_menu(gl.xres, gl.yres);
  if (gl.display_startmenu && gl.menu_position == 1)
  {
  characterselection_menu(gl.xres, gl.yres);
  if (gl.display_levelselectionmenu)
  {
  levelselection_menu(gl.xres, gl.yres);
  if (gl.levelSelect == 1)
  {
  clearScreen();	
  renderBackground();
  renderPlatform();
  renderMainCharacter();
  showTurret();
  showenemy1();
  show_mari();
  healthBar(gl.xres, gl.yres);
  }
  }
  }
  }*/

/*if (gl.display_playernamemenu) 
  {
  playername_menu(gl.xres, gl.yres);
  }

  if (gl.display_characterselectionmenu)
  {
  characterselection_menu(gl.xres, gl.yres);
  }    

  if (gl.display_levelselectionmenu)
  {
  levelselection_menu(gl.xres, gl.yres);
  }

  if (gl.levelSelect == 1)
  {
  clearScreen();	
  renderBackground();
  renderPlatform();
  renderMainCharacter();
  showTurret();
  showenemy1();
  show_mari();
  healthBar(gl.xres, gl.yres);
  }
  }*/
