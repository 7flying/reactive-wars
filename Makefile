
PROG=reactive-wars
SRCS=main.cpp Character.cpp CharacterClass.cpp Stats.cpp Mage.cpp
LIB=/usr/local/SFML-2.3.2/lib
LINK=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:
	rm -f $(PROG)
	g++ $(SRCS) -o $(PROG) -std=c++11 -O3 -L -L$(LIB) $(LINK)

clean:
	rm -f *~

check-syntax:
	g++ -std=c++11 -o .nul -S ${CHK_SOURCES}

