#ifndef _GAME_H_
#define _GAME_H_
//game.h
//Read and write PPM files. Plain format.
//#include <sys/types.h>
extern class Global {
    public:
	int done;
	int keys[65536];
	int xres, yres;
	int walk;
	int flag, attackFlag;
	int walkFrame;
	double delay;
	int menu_position;

	Ppmimage *walkImage;
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

	GLuint walkTexture;
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


	Global() {
	    attackFlag = 0;
	    flag = 0;
	    done=0;
	    xres=800;
	    yres=600;
	    walk=0;
	    menu_position = 1;
	    walkFrame=0;

	    walkImage=NULL;
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

	    memset(keys, 0, 65536); //
	}
} gl;
#endif


