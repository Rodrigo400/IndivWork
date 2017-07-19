#ifndef _GAME_H_
#define _GAME_H_
#include "ppm.h"
//game.h
//Read and write PPM files. Plain format.
//#include <sys/types.h>
#include <time.h>
typedef double Flt;
#define rnd() (((double)rand())/(double)RAND_MAX)

struct Vec {
    double x, y, z;
};

struct Shape {
    public:
	float width, height;
	float radius;
	Vec center;
};

struct NameBox
{
    Shape box[1];
};


struct Particle
{
    float cx, cy, velocity;
    int direction;
    Particle() {
	direction = 0;
	cx = 0;
	cy = 0;
    }
};

struct Game
{
    Shape box[5];
    int n;

};


extern class Timers
{
    public:
	double physicsRate;
	double oobillion;
	struct timespec timeStart, timeEnd, timeCurrent;
	struct timespec maincharacterTime;
	struct timespec gameTime;
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

extern class Global {
    public:
	int done;
	int keys[65536];
	int xres, yres;
	int initDone;
	int walk;
	int directionFlag, attackFlag, isJumpingFlag, jumpDirectionFlag;
	int initialJumpCy, finalJumpCy;
	Particle particle[30];
	float jumpRate, jumpHeight;
	float particleVelocity;
	int particleCount;
	float particleWidth, particleHeight;
	int maincharacterFrame;
	double delay;
	int menu_position;
	int characterSelect;
	Flt movementSpeed;
	int levelSelect;
	char p_name[100];
	Flt camera[2];
	Vec box[20];
	int gameFrame;
	int gameDelay;
	int minutes;

	Ppmimage *maincharacterImage;
	Ppmimage *maincharacter1Image;
	Ppmimage *maincharacter2Image;
	Ppmimage *maincharacter3Image;
	Ppmimage *maincharacter4Image;
	Ppmimage *mainmenubackgroundImage;
	Ppmimage *turretImage; 
	Ppmimage *enemy1Image;
	Ppmimage *mari_image; 
	Ppmimage *logoImage;
	Ppmimage *playImage;
	Ppmimage *tutorialImage;
	Ppmimage *highscoresImage;
	Ppmimage *creditsImage;
	Ppmimage *exitImage;
	Ppmimage *texthighlightImage;
	Ppmimage *levelselectionImage;
	Ppmimage *characterselectionImage;
	Ppmimage *frameImage;
	Ppmimage *backgroundImage;	
	Ppmimage *platformImage;
	Ppmimage *lavaImage;
	Ppmimage *metalImage;
	Ppmimage *attackdmgImage;
	Ppmimage *blueenemyImage;
	Ppmimage *greenenemyImage;
	Ppmimage *heartaddImage;
	Ppmimage *redenemyImage;
	Ppmimage *shieldImage;
	Ppmimage *speedboostImage;
	Ppmimage *tabkeyImage;
	Ppmimage *leftarrowkeyImage;
	Ppmimage *rightarrowkeyImage;
	Ppmimage *spacebarkeyImage;
	Ppmimage *uparrowkeyImage;
	Ppmimage *enterkeyImage;
	Ppmimage *blueboxImage;
	Ppmimage *americaballImage;
	Ppmimage *moltenballImage;
	Ppmimage *purpleballImage;

	GLuint maincharacterTexture;
	GLuint maincharacter1Texture;
	GLuint maincharacter2Texture;
	GLuint maincharacter3Texture;
	GLuint maincharacter4Texture;
	GLuint mainmenubackgroundTexture;
	GLuint logoTexture;
	GLuint playTexture;
	GLuint tutorialTexture;
	GLuint highscoresTexture;
	GLuint creditsTexture;
	GLuint exitTexture;
	GLuint texthighlightTexture;
	GLuint levelselectionTexture;
	GLuint characterselectionTexture;
	GLuint frameTexture;
	GLuint turretTexture; 
	GLuint enemy1Texture;
	GLuint mari_Texture;
	GLuint backgroundTexture;
	GLuint platformTexture;
	GLuint lavaTexture;
	GLuint metalTexture;
	GLuint attackdmgTexture;
	GLuint blueenemyTexture;
	GLuint greenenemyTexture;
	GLuint heartaddTexture;
	GLuint redenemyTexture;
	GLuint shieldTexture;
	GLuint speedboostTexture;
	GLuint tabkeyTexture;
	GLuint leftarrowkeyTexture;
	GLuint uparrowkeyTexture;
	GLuint rightarrowkeyTexture;
	GLuint spacebarkeyTexture;
	GLuint enterkeyTexture;
	GLuint blueboxTexture;
	GLuint americaballTexture;
	GLuint moltenballTexture;
	GLuint purpleballTexture;

	bool display_startmenu;
	bool display_tutorialmenu;
	bool display_tutorialmenu2;
	bool display_highscoresmenu;
	bool display_creditsmenu;
	bool display_characterselectionmenu;
	bool display_levelselectionmenu;
	bool display_playernamemenu;
	bool display_playername;
	bool display_startinggame;

	bool oneOffShootFlag;
	bool shield1Flag;
	bool heart1Flag;
	bool heart2Flag;
	bool speedboost1Flag;

	Global() {
	    camera[0] = camera[1] = 0.0;
	    gameDelay = 1;
	    minutes = 0;
	    gameFrame = 0;
	    attackFlag = 0;
	    particleVelocity = 6;
	    particleCount = 0;
	    particleWidth = 5;
	    particleHeight = 5;
	    directionFlag = 0;
	    isJumpingFlag = 0;
	    jumpDirectionFlag = 0;
	    jumpRate = .06;
	    jumpHeight = 100;
	    movementSpeed = 2;
	    initialJumpCy = 0;
	    finalJumpCy = 0;
	    done=0;
	    xres=800;
	    yres=600;
	    walk=0;
	    menu_position = 1;
	    characterSelect = 0;
	    levelSelect = 0;
	    maincharacterFrame=0;
	    delay= 0.06;
	    initDone = 1;
	    p_name[0] = '\0';

	    oneOffShootFlag = false;
	    shield1Flag = 1;
	    speedboost1Flag = 1;
	    heart1Flag = 1;
	    heart2Flag = 1;

	    maincharacterImage = NULL;
	    maincharacter1Image = NULL;
	    maincharacter2Image = NULL;
	    maincharacter3Image = NULL;
	    maincharacter4Image = NULL;
	    mainmenubackgroundImage = NULL;
	    turretImage = NULL; 
	    enemy1Image = NULL;
	    mari_image = NULL; 
	    logoImage = NULL;
	    playImage = NULL;
	    tutorialImage = NULL;
	    highscoresImage = NULL;
	    creditsImage = NULL;
	    exitImage = NULL;
	    texthighlightImage = NULL;
	    levelselectionImage = NULL;
	    characterselectionImage = NULL;
	    frameImage = NULL;
	    lavaImage = NULL;
	    metalImage = NULL;
	    backgroundImage = NULL;
	    platformImage = NULL;
	    attackdmgImage = NULL;
	    blueenemyImage = NULL;
	    greenenemyImage = NULL;
	    heartaddImage = NULL;
	    redenemyImage = NULL;
	    shieldImage = NULL;
	    speedboostImage = NULL;
	    tabkeyImage = NULL;
	    leftarrowkeyImage = NULL;
	    rightarrowkeyImage = NULL;
	    spacebarkeyImage = NULL;
	    uparrowkeyImage = NULL;
	    enterkeyImage = NULL;
	    blueboxImage = NULL;
	    americaballImage = NULL;
	    moltenballImage = NULL;
	    purpleballImage = NULL;

	    display_startmenu = true;
	    display_tutorialmenu = false;
	    display_tutorialmenu2 = false;
	    display_highscoresmenu = false;
	    display_creditsmenu = false;
	    display_characterselectionmenu = false;
	    display_levelselectionmenu = false;
	    display_playernamemenu = false;
	    display_playername = false;
	    display_startinggame = false;

	    for (int i = 0; i<20; i++) {
		box[i].x = rnd() * xres;
		box[i].y = rnd() * (yres - 100) + 100;
		box[i].z = 0.0;
	    }
	    memset(keys, 0, 65536); //
	}
} gl;


extern class Level {
    public:
	unsigned char arr[21][700];
	int nrows, ncols;
	int dynamicHeight[180];
	int tilesize[2];
	Flt ftsz[2];
	Flt tile_base;
	Level() {
	    for (int i=0; i < 180; i++) {
		dynamicHeight[i] = -1;
	    }
	    //Log("Level constructor\n");
	    tilesize[0] = 32;
	    tilesize[1] = 32;
	    ftsz[0] = (Flt)tilesize[0];
	    ftsz[1] = (Flt)tilesize[1];
	    tile_base = (gl.yres/gl.yres);
	    //read level
	    FILE *fpi = fopen("level.txt","r");
	    if (fpi) {
		nrows=0;
		char line[700];
		while (fgets(line, 700, fpi) != NULL) {
		    removeCrLf(line);
		    int slen = strlen(line);
		    ncols = slen;
		    //Log("line: %s\n", line);
		    for (int j=0; j<slen; j++) {
			arr[nrows][j] = line[j];
		    }
		    ++nrows;
		}
		fclose(fpi);
		//printf("nrows of background data: %i\n", nrows);
	    }
	    //for (int i=0; i<nrows; i++) {
	    //    for (int j=0; j<ncols; j++) {
	    //        printf("%c", arr[i][j]);
	    //    }
	    //    printf("\n");
	    //}
	}
	void removeCrLf(char *str) {
	    char *p = str;
	    while (*p) {
		if (*p == 10 || *p == 13) {
		    *p = '\0';
		    break;
		}
		++p;
	    }
	}
} lev;

extern class UserInput
{
    public:
	int location[1];
	int size;
	char player_name[15];
	UserInput()
	{
	    location[0] = 0;
	    player_name[0] = '\0';
	    size = 32;
	}
} input;


extern class Sprite {
    public:
	Flt pos[2];
	Flt vel[2];
	float cx;
	float cy;
	int health;
	Sprite () {
	    health = 10;
	    cx = 600;
	    cy = 90;
	}
} heart2, heart1, speedboost1, shield1, mainChar, turret, enemy1, mariEnemy;
#endif


