#all:
#	g++ Main.cpp Bullet.cpp Collisione.cpp Enemy.cpp Gioco.cpp Player.cpp Sfondo.cpp Shield.cpp -o hello `pkg-config --libs allegro-5.0 allegro_dialog-5.0 allegro_acodec-5.0 allegro_color-5.0 #allegro_font-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

OBJ = Main.o Bullet.o Collisione.o Enemy.o Gioco.o Player.o Sfondo.o Shield.o


all: Progetto
	

Progetto: $(OBJ)
	g++ $(OBJ) -o ProgettoMake `pkg-config --libs allegro-5.0 allegro_dialog-5.0 allegro_acodec-5.0 allegro_color-5.0 allegro_font-5.0 allegro_image-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

Main.o: Main.cpp
	g++ -c Main.cpp

Bullet.o: Bullet.cpp
	g++ -c Bullet.cpp

Collisione.o: Collisione.cpp
	g++ -c Collisione.cpp

Enemy.o: Enemy.cpp
	g++ -c Enemy.cpp

Gioco.o: Gioco.cpp
	g++ -c Gioco.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Sfondo.o: Sfondo.cpp
	g++ -c Sfondo.cpp

Shield.o: Shield.cpp
	g++ -c Shield.cpp

.PHONY: clean cleanall

clean:
	rm -f *.o
cleanall:
	rm -f Progetto *.o *~
