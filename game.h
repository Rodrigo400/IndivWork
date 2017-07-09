#ifndef _GAME_H_
#define _GAME_H_
#include "ppm.h"
//game.h
//Read and write PPM files. Plain format.
//#include <sys/types.h>

enum State
{
    NONE,
    STARTMENU,
    CHARACTERSELECTIONMENU,
    LEVELSELECTIONMENU,
    GAMEPLAY,
    PAUSE,
    GAMEOVER
};

extern class Global {
    public:
        int done;
        int keys[65536];
        int xres, yres;
        int initDone;
        int walk;
        int directionFlag, attackFlag;
        int maincharacterFrame;
        double delay;
        int menu_position;
        int characterSelect;
        int levelSelect;
        char p_name[100];
        State state;
        State render;

        Ppmimage *maincharacterImage;
        Ppmimage *mainmenubackgroundImage;
        Ppmimage *turretImage; 
        Ppmimage *enemy1Image;
        Ppmimage *mari_image; 
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
        Ppmimage *backgroundImage;	
        Ppmimage *platformImage;

        GLuint maincharacterTexture;
        GLuint mainmenubackgroundTexture;
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
        GLuint turretTexture; 
        GLuint enemy1Texture;
        GLuint mari_Texture;
        GLuint backgroundTexture;
        GLuint platformTexture;

        bool display_startmenu;
        bool display_settingsmenu;
        bool display_highscoresmenu;
        bool display_creditsmenu;
        bool display_characterselectionmenu;
        bool display_levelselectionmenu;
        bool display_playernamemenu;
        bool display_playername;


        Global() {
            state = STARTMENU;
            attackFlag = 0;
            directionFlag = 0;
            done=0;
            xres=800;
            yres=600;
            walk=0;
            menu_position = 1;
            characterSelect = 0;
            levelSelect = 0;
            maincharacterFrame = 0;
            delay = 0.05;
            initDone = 1;
            p_name[0] = '\0';

            maincharacterImage = NULL;
            mainmenubackgroundImage = NULL;
            turretImage = NULL; 
            enemy1Image = NULL;
            mari_image = NULL; 
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
            backgroundImage = NULL;
            platformImage = NULL;

            display_startmenu = true;
            display_settingsmenu = false;
            display_highscoresmenu = false;
            display_creditsmenu = false;
            display_characterselectionmenu = false;
            display_levelselectionmenu = false;
            display_playernamemenu = false;
            display_playername = false;

            memset(keys, 0, 65536); //
        }
} gl;

extern class UserInput
{
    public:
        int location[1];
        int size;
        char player_name[15];
        UserInput ()
        {
            location[0] = 0;
            player_name[0] = '\0';
            size = 32;
        }
} input;


extern class Sprite {
    public:
        float cx;
        float cy;
        Sprite () {
            cx = 600;
            cy = 100;
        }
} turret, enemy1, mariEnemy;

struct Vect 
{
    float x, y, z;
};

struct Shape 
{
    float width, height;
    float radius;
    Vect center;
};

struct NameBox 
{
    Shape box[1];
};

struct Game
{
    Shape box[5];
    int n;
};


#endif


