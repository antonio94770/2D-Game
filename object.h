#include<allegro5/allegro.h>					//Libreria Allegro
#include<allegro5/allegro_native_dialog.h>		//Libreria messagebox
#include<iostream>
#include<fstream>
#include<ctime>
#include<math.h>
#include<allegro5/allegro_ttf.h>				//Libreria font
#include<allegro5/allegro_font.h>				//Libreria font
#include<allegro5/allegro_primitives.h>			//Libreria primitive
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include "Player.h"
#include "Enemy.h"
#include "Shield.h"
#include "Sfondo.h"
#include "Bullet.h"
#include "Collisione.h"

#define ScreenWidth 800
#define ScreenHeight 600

bool InizializzaLivello(ALLEGRO_SAMPLE_INSTANCE, bool &, bool &, bool &, bool &, bool &, bool &, bool &, bool &, bool &, bool &, SpaceShip &, int &, bool &, int &, bool &);


