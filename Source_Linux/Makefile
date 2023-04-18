CC=g++
CFLAGS=-c -w -g -std=c++14 -Wall -pedantic -Wno-long-long -O0 -ggdb
CLIBS=-std=c++14 -lSDL2 -lSDL2_image

all: doc khokhole

khokhole: Bar.o Bot.o Map.o Bomb.o Game.o Unit.o Wall.o Bonus.o Flame.o DesBar.o Object.o Source.o Player1.o Player2.o Texture.o DesPlayer.o
	$(CC) Bar.o Bot.o Map.o Bomb.o Game.o Unit.o Wall.o Bonus.o Flame.o DesBar.o Object.o Source.o Player1.o Player2.o Texture.o DesPlayer.o -o "khokhole" $(CLIBS)

Bar.o: src/Bar.cpp src/Bar.h 
	$(CC) $(CFLAGS) src/Bar.cpp -o $@

Bot.o: src/Bot.cpp src/Bot.h 
	$(CC) $(CFLAGS) src/Bot.cpp -o $@

Map.o: src/Map.cpp src/Map.h src/Texture.h 
	$(CC) $(CFLAGS) src/Map.cpp -o $@

Bomb.o: src/Bomb.cpp src/Bomb.h 
	$(CC) $(CFLAGS) src/Bomb.cpp -o $@

Game.o: src/Game.cpp src/Texture.h src/Player1.h src/Player2.h src/Bonus.h src/Bot.h src/DesPlayer.h src/Bomb.h src/Flame.h src/Wall.h src/Bar.h src/DesBar.h src/Game.h 
	$(CC) $(CFLAGS) src/Game.cpp -o $@

Unit.o: src/Unit.cpp src/Unit.h 
	$(CC) $(CFLAGS) src/Unit.cpp -o $@

Wall.o: src/Wall.cpp src/Wall.h 
	$(CC) $(CFLAGS) src/Wall.cpp -o $@

Bonus.o: src/Bonus.cpp src/Bonus.h 
	$(CC) $(CFLAGS) src/Bonus.cpp -o $@

Flame.o: src/Flame.cpp src/Flame.h 
	$(CC) $(CFLAGS) src/Flame.cpp -o $@

DesBar.o: src/DesBar.cpp src/DesBar.h 
	$(CC) $(CFLAGS) src/DesBar.cpp -o $@

Object.o: src/Object.cpp src/Object.h src/Game.h 
	$(CC) $(CFLAGS) src/Object.cpp -o $@

Source.o: src/Source.cpp src/Game.h src/Object.h 
	$(CC) $(CFLAGS) src/Source.cpp -o $@

Player1.o: src/Player1.cpp src/Player1.h 
	$(CC) $(CFLAGS) src/Player1.cpp -o $@

Player2.o: src/Player2.cpp src/Player2.h 
	$(CC) $(CFLAGS) src/Player2.cpp -o $@

Texture.o: src/Texture.cpp src/Texture.h 
	$(CC) $(CFLAGS) src/Texture.cpp -o $@

DesPlayer.o: src/DesPlayer.cpp src/DesPlayer.h 
	$(CC) $(CFLAGS) src/DesPlayer.cpp -o $@

doc:
	doxygen doxygen.conf
	mv doc/html/* doc/
	rm -r doc/html

documentation: doc
	firefox doc/index.html

clean:
	rm -f *.o
	rm -f khokhole
	rm -rf doc
	rm -rf *.dSYM

compile: doc khokhole

run: doc khokhole
	./khokhole
