
PROG=reactive-wars
SRCS=main.cpp Character.cpp CharacterClass.cpp Else.cpp FontManager.cpp \
	PerlinNoise.cpp \
	TextureManager.cpp AnimationHandler.cpp Tile.cpp Map.cpp \
	Game.cpp GameStateInit.cpp GameStateLevel.cpp Mage.cpp Stats.cpp
LIB=/usr/local/SFML-2.3.2/lib
LINK=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
ARGS_DEBUG=-std=c++11
ARGS_RELEASE=-std=c++11

all:
	rm -f $(PROG)
	g++ $(SRCS) -o $(PROG) $(ARGS_DEBUG) -L -L$(LIB) $(LINK)

release:
	rm -f $(PROG)
	g++ $(SRCS) -o $(PROG) $(ARGS_RELEASE) -L -L$(LIB) $(LINK)

clean:
	rm -f *~

check-syntax:
	g++ -std=c++11 -o .nul -S ${CHK_SOURCES}

