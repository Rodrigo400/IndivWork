CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: game

game: game.cpp
	g++ $(CFLAGS) game.cpp rodrigoG.cpp ppm.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -ogame

clean:
	rm -f game
    
