//Simran Preet Singh
//06/24/17
//What does this code do?
//This code makes sound using audio files the library is used to do this
//is openal and this code displays two enemies using ppm images
//The enemies do not do much but they show up on the screen.
#include <iostream>
#include <stdio.h>
#include <cstdlib>
//#include <string>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <time.h>
#include "game.h"
#include "ppm.h"
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

//This flag is used for checking if the dsound fuction is called
//if it is called then it will delete the source and buffer
bool h = false;

//This function plays sound using openal's function alSource Play(...)

void Playsound(ALuint tum) 
{
    alSourcePlay(tum);
}

//This function creates sound and checks if the libraries are found
//This function also deletes the buffer and source of sound if 
//the boolean value is true
void csound(const char *a) 
{

#ifdef USE_OPENAL_SOUND
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
	printf(" There is an error  in alutInit()\n");
	return;
    }

    alGetError();

    float termoil[6] = {0.0, 0.0, 1.0, 0.0, 1.0, 0.0};
    alListener3f(AL_POSITION, 0.0, 0.0, 0.0);
    alListenerfv(AL_ORIENTATION, termoil);
    alListenerf(AL_GAIN, 1.0);

    ALuint toom;
    toom = alutCreateBufferFromFile(a); 

    ALuint tum;
    
    alGenSources(1, &tum);
    alSourcei(tum, AL_BUFFER, toom);

    alSourcef(tum, AL_GAIN, 0.35);
    alSourcef(tum, AL_PITCH, 2.5);
    alSourcei(tum, AL_LOOPING, 1);

    if (alGetError() != AL_NO_ERROR) {
	printf("cannot set the source\n");
	return;
    }
    Playsound(tum);
    if(h == true) {
	alDeleteSources(1, &tum);
	alDeleteBuffers(1, &toom);
    }
#endif
}

//this function closes and destroyes the sound
void dsound()
{ 
#ifdef USE_OPENAL_SOUND
    h = true;

    ALCcontext *stuff = alcGetCurrentContext();
    ALCdevice *yantar = alcGetContextsDevice(stuff);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(stuff);
    alcCloseDevice(yantar);

#endif
}

//This function converts a png image to a ppm image
Ppmimage *turretImage() 
{
    system ("convert ./images/Turret.png ./images/Turret.ppm");
    return ppm6GetImage("./images/Turret.ppm");
}

//This function displays a turret on to the screen
void showTurret() 
{
    //glClearColor(0.1,0.1,0.1,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    //float x = gl.xres/1.5;
    float y = 100;
    float ht = 20.0;
    float w = ht*2;
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.turretTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 4.0;
    float ty = (float)ay;
    
    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+.5); glVertex2i(turret.cx+w, y-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(turret.cx+w, y+ht);
    glTexCoord2f(tx+.5, ty);    glVertex2i(turret.cx-w, y+ht);
    glTexCoord2f(tx+.5, ty+.5); glVertex2i(turret.cx-w, y-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}

//This function converts a png image to a ppm image
Ppmimage *enemy1image()
{
    system ("convert ./images/enemy1.png ./images/enemy1.ppm");
    return ppm6GetImage("./images/enemy1.ppm");
}

//this function displays an enemy
//curretly the enemey has srounded the hero
void showenemy1() 
{
    //float x = gl.xres/2.0;
    float y = 100;
    float ht = 30.0;
    float w = ht*2;

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, gl.enemy1Texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);

    int ax = 1;
    int ay = 1;
    if (1 >= 1)
	ay = 0;
    float tx = (float)ax / 4.0;
    float ty = (float)ay;

    glBegin(GL_QUADS);
    glTexCoord2f(tx,      ty+.5); glVertex2i(enemy1.cx+w, y-ht);
    glTexCoord2f(tx,      ty);    glVertex2i(enemy1.cx+w, y+ht);
    glTexCoord2f(tx+.5, ty);    glVertex2i(enemy1.cx-w, y+ht);
    glTexCoord2f(tx+.5, ty+.5); glVertex2i(enemy1.cx-w, y-ht);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_ALPHA_TEST);
}
