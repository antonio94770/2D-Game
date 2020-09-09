

#include "object.h"
#define DEB(a) {a ;}



//bool InizializzaLivello(ALLEGRO_SAMPLE_INSTANCE *songInstance, bool &flagMenu, bool &SpawnShieldIcon, bool &SpawnBulletIcon, bool &FlagHoLoScudo, bool &FlagHoLaser, bool &GoldenShield, bool &HoColliso, bool &Draw, bool &HoSparato, bool &flagRecord, SpaceShip &ship, int &dir, bool &flagEsplosione, int &frame, bool &Dead);

void InitShip(SpaceShip &ship, ALLEGRO_BITMAP *image);
void DrawMap_Text_Player(ALLEGRO_COLOR color, SpaceShip ship, ALLEGRO_FONT *font);
void SetPlayerImage(SpaceShip &ship, ALLEGRO_BITMAP *image);

void InitEnemy(Enemy &enemy, ALLEGRO_BITMAP *image);
void UpdateEnemy(Enemy &enemy, ALLEGRO_BITMAP *image);
void DrawEnemy(Enemy &enemy, int &rotazione);


void InitBullet(Bullet &bullet, SpaceShip ship, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *icona);
void DrawBulletPowerUp(Bullet &bullet);
void DrawIconaPowerUp(Bullet &bullet,bool flagholoscudo);
void UpdatePowerUp(Bullet &bullet, SpaceShip ship, bool &spawn, bool &flaghobullet, bool FlagMorto, ALLEGRO_BITMAP *image);
void UpdateBullet(Bullet &bullet, bool &hosparato, SpaceShip ship, Enemy &enemy, ALLEGRO_BITMAP *image);
void DrawBullet(Bullet bullet);


void InitSfondo(Sfondo &sfondo, float x, float  y, float velx, float vely, int width, int height, int dirx, int diry, ALLEGRO_BITMAP *image);
void UpdateSfondo(Sfondo &sfondo);
void DrawSfondo(Sfondo &sfondo);


bool Collisione(ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy, float x, float y, float ex, float ey, int width, int height);
bool CollisioneBordi(SpaceShip ship);
bool CheckPoweUpCollideShield(SpaceShip &ship, Shield &shield);
bool CheckPoweUpCollideBullet(SpaceShip &ship, Bullet &bullet);
bool CheckCollideBullet(Bullet &bullet, Enemy &enemy);


void InitShield(Shield &shield, ALLEGRO_BITMAP *image);
void DrawShield(SpaceShip &ship, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *icona);
void UpdateShield(Shield &shield, SpaceShip &ship, bool &spawnshieldicon, bool &flagholoscudo, bool FlagMorto, bool &GoldenShield);
void DrawShieldPowerUp(Shield shield);


/** ...
*
*  Vedere la documentazione della funzione 
*  
::main
 per maggiori dettagli sulle funzionalità e 
*  sulla loro implementazione.
*/


int main(){

	const float FPS = 60.0;
	SpaceShip ship;
	Bullet bullet;
	Enemy enemy;
	Shield shield;

	Sfondo background01;
	Sfondo background02;
	Sfondo background03;
	Sfondo background04;



	bool Done = false, Draw = true, Dead = false;
	int dir = DOWN;						/**< Direzione navicella spaziale */
	int frame = 0;
	int frameCount = 0;
	int frameDalay = 4;
	int rotazione = 0;
	bool flagEsplosione = 0;
	bool flagMenu = true;
	bool Inizializzato = 0;
	bool flagRecord = false;
	bool SpawnShieldIcon = false;
	bool SpawnBulletIcon = false;
	bool FlagHoLoScudo = false;
	bool FlagHoLaser = false;
	bool GoldenShield = false;
	bool HoColliso = false;				//Perchè rileva più alla volta collisioni quindi devo aspettare che enemy.live = false;
	bool HoSparato = false;



	ALLEGRO_SAMPLE *laser = NULL;
	ALLEGRO_SAMPLE *esplosione = NULL;
	ALLEGRO_SAMPLE *song = NULL;
	ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;



	if (!al_init()){
		al_show_native_message_box(NULL, NULL, NULL, "Posso far partire allegro", NULL, 0);
		return -1;
	}



	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);				//Personalizzo la finestra
	ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_position(display, 200, 100);
	al_set_window_title(display, "Gioco");


	if (!display){
		al_show_native_message_box(display, "Sample Title", "Display Settings", "Display windows was not created successfully", NULL, 0);
		return -1;
	}

	al_init_font_addon();		//Inizializzo font
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();					//Inizializzo Immagini
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();



	ALLEGRO_FONT *font24 = al_load_font("font.ttf", 24, 0);
	ALLEGRO_FONT *font36 = al_load_font("font.ttf", 36, 0);


	ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 225);			//Inizializzo nuovo colore

	ALLEGRO_PATH *pathimg = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(pathimg, "Img");
	al_change_directory(al_path_cstr(pathimg, '/'));  // change the working directory
	al_destroy_path(pathimg);


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	ALLEGRO_BITMAP *playerIdle = al_load_bitmap("spaceship_idle1.png");
	ALLEGRO_BITMAP *playerRun = al_load_bitmap("spaceship_run1.png");
	ALLEGRO_BITMAP *playerDead = al_load_bitmap("spaceship_dead.png");

	ALLEGRO_BITMAP *ShieldIcon = al_load_bitmap("powerupBlue_shield.png");
	ALLEGRO_BITMAP *ShieldGoldenIcon = al_load_bitmap("powerupYellow_shield.png");
	ALLEGRO_BITMAP *shieldimg = al_load_bitmap("shield2.png");
	ALLEGRO_BITMAP *shieldgoldenimg = al_load_bitmap("shield2golden.png");

	ALLEGRO_BITMAP *bulletimg = al_load_bitmap("laserBlue.png");
	ALLEGRO_BITMAP *bulletpowerupimg = al_load_bitmap("powerupRed_bolt.png");

	ALLEGRO_BITMAP *imgenemy = al_load_bitmap("meteor01.png");

	ALLEGRO_BITMAP *bgImage01 = NULL;
	ALLEGRO_BITMAP *bgImage02 = NULL;
	ALLEGRO_BITMAP *bgImage03 = NULL;
	ALLEGRO_BITMAP *bgImage04 = NULL;

	ALLEGRO_BITMAP *explosion[7];
	explosion[0] = al_load_bitmap("explosion00.png");
	explosion[1] = al_load_bitmap("explosion01.png");
	explosion[2] = al_load_bitmap("explosion02.png");
	explosion[3] = al_load_bitmap("explosion03.png");
	explosion[4] = al_load_bitmap("explosion04.png");
	explosion[5] = al_load_bitmap("explosion05.png");
	explosion[6] = al_load_bitmap("spaceship_dead.png");

	for (int i = 0; i < 6; i++) al_convert_mask_to_alpha(explosion[i], al_map_rgb(106, 76, 48));

	bgImage01 = al_load_bitmap("starBG.png");
	bgImage02 = al_load_bitmap("starMG2.png");
	bgImage03 = al_load_bitmap("starFG.png");
	bgImage04 = al_load_bitmap("Fog1.png");



	ALLEGRO_PATH *pathaudio = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(pathaudio, "Audio");
	al_change_directory(al_path_cstr(pathaudio, '/'));  // change the working directory
	al_destroy_path(pathaudio);


	al_reserve_samples(4);

	laser = al_load_sample("laser.ogg");
	esplosione = al_load_sample("explosion.ogg");
	song = al_load_sample("song.ogg");

	songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);

	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "");
	al_change_directory(al_path_cstr(path, '/'));  // change the working directory
	al_destroy_path(path);



	std::ifstream scorefile("score.txt");
	scorefile >> ship.bestscore;

	if (ship.bestscore < 0 || !scorefile) ship.bestscore = 0;

	scorefile.close();


	al_start_timer(timer);
	srand(time(NULL));


	while (!Done){

		if (Dead)	dir = STOP;

		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);


		if (events.type == ALLEGRO_EVENT_KEY_DOWN && !flagMenu){
			switch (events.keyboard.keycode){

			case ALLEGRO_KEY_SPACE: dir = UP;
				SetPlayerImage(ship, playerRun);
				break;

			case ALLEGRO_KEY_F:
				if (Dead == true) flagMenu = true;
				break;

			case ALLEGRO_KEY_E:
				if (FlagHoLaser) {
					HoSparato = true;
					FlagHoLaser = false;
					al_play_sample(laser,1,0,1,ALLEGRO_PLAYMODE_ONCE,0);
				}
				break;

			}
		}

		else if (events.type == ALLEGRO_EVENT_KEY_DOWN && flagMenu){
			switch (events.keyboard.keycode){
			case ALLEGRO_KEY_E: flagMenu = false;
				break;
			case ALLEGRO_KEY_ESCAPE: Done = true;
				break;
			}
		}

		if (events.type == ALLEGRO_EVENT_KEY_UP && Dead == false && !flagMenu){
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_SPACE: SetPlayerImage(ship, playerIdle);
				dir = DOWN;
				break;
			}
		}

		if (flagMenu && !Inizializzato){
			al_stop_sample_instance(songInstance);
			flagMenu = true;
			SpawnShieldIcon = false;
			SpawnBulletIcon = false;
			FlagHoLoScudo = false;
			FlagHoLaser = false;
			GoldenShield = false;
			HoColliso = false;
			Draw = true;
			HoSparato = false;
			if (flagRecord){
				flagRecord = false;
				ship.bestscore = ship.score;
			}
			InitShield(shield, ShieldIcon);
			InitShip(ship, playerIdle);
			InitEnemy(enemy, imgenemy);
			InitBullet(bullet, ship, bulletimg, bulletpowerupimg);
			InitSfondo(background01, 0, 0, 1, 0, ScreenWidth, ScreenHeight, -1, 1, bgImage01);
			InitSfondo(background02, 0, 0, 1, 0, ScreenWidth * 6, ScreenHeight, -1, 1, bgImage02);
			InitSfondo(background03, 0, 0, 4, 0, ScreenWidth, ScreenHeight, -1, 1, bgImage03);
			InitSfondo(background04, 0, 0, 1, 0, ScreenWidth * 2, ScreenHeight, -1, 1, bgImage04);
			InitBullet(bullet, ship, bulletimg, bulletpowerupimg);
			dir = DOWN;
			flagEsplosione = false;
			frame = 0;
			Dead = false;
			Inizializzato = 1;// InizializzaLivello(songInstance, flagMenu, SpawnShieldIcon, SpawnBulletIcon, FlagHoLoScudo, FlagHoLaser, GoldenShield, HoColliso, Draw, HoSparato, flagRecord, ship, dir, flagEsplosione, frame, Dead);
		}



		if (events.type == ALLEGRO_EVENT_TIMER){
			UpdateSfondo(background01);
			UpdateSfondo(background02);
			UpdateSfondo(background03);
			UpdateSfondo(background04);
			UpdateBullet(bullet, HoSparato, ship,enemy,playerDead);
			if (!flagMenu){
				al_play_sample_instance(songInstance);
				Inizializzato = 0;
				if (enemy.live && Collisione(playerIdle, imgenemy, ship.x, ship.y, enemy.x, enemy.y, 114, 87)){
					if (!FlagHoLoScudo && enemy.live && !HoColliso){
						HoColliso = true; Dead = true;
					}
					else{
						switch (GoldenShield){
						case 0:
							if (!HoColliso)	FlagHoLoScudo = false;
							break;
						case 1:
							DEB(std::cout << "Ho il golden Shield" << std::endl;);
							GoldenShield = false;
							FlagHoLoScudo = true;
							break;
						}
						HoColliso = true;
						enemy.live = false;
						enemy.image = playerDead;
					}
				}

				if (HoColliso && enemy.live) HoColliso = false;

				if ((ship.score % 500) == 0 && ship.score > 0){
					SpawnBulletIcon = true; SpawnShieldIcon = true;
				}

				switch (ship.score){
				case 0:
					enemy.speed = 4;
					break;
				case 500:
					enemy.speed = 9;
					ship.physics = 5;
					background01.velX = 2;
					background02.velX = 2;
					background03.velX = 5;
					background04.velX = 2;
					break;
				case 1000:
					enemy.speed = 11;
					ship.speed = 7;
					ship.physics = 7;
					background01.velX = 4;;
					background02.velX = 3;
					background03.velX = 7;
					background04.velX = 4;
					break;
				case 1500:
					enemy.speed = 13;
					ship.speed = 8;
					ship.physics = 8;
					background01.velX = 6;
					background02.velX = 4;
					background03.velX = 9;
					background04.velX = 6;
					break;
				case 2000:
					enemy.speed = 20;
					ship.speed = 10;
					ship.physics = 10;
					background01.velX = 8;
					background03.velX = 11;
					background04.velX = 8;
					break;
				}

				if (SpawnShieldIcon) UpdateShield(shield, ship, SpawnShieldIcon, FlagHoLoScudo, Dead, GoldenShield);
				if (SpawnBulletIcon) UpdatePowerUp(bullet, ship, SpawnBulletIcon, FlagHoLaser, Dead, bulletimg);

				if (Dead && flagEsplosione == 0){
					if (++frameCount >= frameDalay){
						if (++frame >= 7) frame = 0;
						frameCount = 0;
					}

					SetPlayerImage(ship, playerDead);

					if (frame >= 5){
						flagEsplosione = 1;
						frame = 6;
						al_play_sample(esplosione, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}

					FlagHoLoScudo = 0;
					GoldenShield = false;
					FlagHoLaser = false;
					enemy.live = false;
					enemy.image = playerDead;
				}

				else if (!Dead){
					ship.score++;
					UpdateEnemy(enemy, imgenemy);
				}

				switch (dir){
				case DOWN: ship.y += ship.physics; break;
				case UP: ship.y -= ship.speed; break;
				case STOP: break;

				}

				if (!Dead && CollisioneBordi(ship)) Dead = true;


				Draw = true;

			}

		}

		if (Draw && al_is_event_queue_empty(event_queue)){

			DrawSfondo(background02);
			DrawSfondo(background01);
			DrawSfondo(background04);

			if (GoldenShield){
				DrawShield(ship, shieldgoldenimg, ShieldGoldenIcon);
			}

			else if (FlagHoLoScudo){
				DrawShield(ship, shieldimg, ShieldIcon);

			}

			if (FlagHoLaser)DrawIconaPowerUp(bullet, FlagHoLoScudo);

			if (HoSparato)DrawBullet(bullet);

			if (SpawnShieldIcon)DrawShieldPowerUp(shield);

			if (SpawnBulletIcon)DrawBulletPowerUp(bullet);

			if (flagMenu){
				al_draw_text(font24, electricBlue, ScreenWidth / 2, ScreenHeight / 2 - 50, ALLEGRO_ALIGN_CENTER, "Premi E per iniziare.");
				al_draw_textf(font24, electricBlue, ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "RECORD DA BATTERE: %d", ship.bestscore);
			}

			if (!flagMenu){

				DrawEnemy(enemy, rotazione);
				Draw = false;

				if (Dead == true){
					al_draw_bitmap(explosion[frame], ship.x, ship.y, 0);
					al_draw_text(font24, al_map_rgb(255, 0, 0), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTER, "You Are Dead!");
					al_draw_textf(font24, al_map_rgb(255, 0, 0), ScreenWidth / 2, ScreenHeight / 2 + 50, ALLEGRO_ALIGN_CENTER, "Points: %d", ship.score);
					al_draw_text(font24, al_map_rgb(255, 0, 0), ScreenWidth / 2, ScreenHeight / 2 + 200, ALLEGRO_ALIGN_CENTER, "Premi F per ricominciare");

					if (ship.score > ship.bestscore){
						std::ofstream scorefile("score.txt");
						scorefile << ship.score;
						flagRecord = true;
						scorefile.close();
						//flagRecord = 1;
						al_draw_text(font36, al_map_rgb(255, 0, 0), ScreenWidth / 2, ScreenHeight / 2 - 200, ALLEGRO_ALIGN_CENTER, "Record!");
					}

					else{
						al_draw_text(font36, al_map_rgb(255, 0, 0), ScreenWidth / 2, ScreenHeight / 2 - 200, ALLEGRO_ALIGN_CENTER, "No Record!");
					}
				}

				else{
					DrawMap_Text_Player(electricBlue, ship, font24);
				}
			}

			DrawSfondo(background03);
			al_flip_display();		//Aggiorna quello che c'è a schermo
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_sample(song);
	al_destroy_sample(esplosione);
	al_destroy_sample(laser);
	al_destroy_sample_instance(songInstance);
	al_destroy_bitmap(playerIdle);
	al_destroy_bitmap(playerRun);
	al_destroy_bitmap(playerDead);
	al_destroy_bitmap(imgenemy);
	al_destroy_bitmap(bgImage01);
	al_destroy_bitmap(bgImage02);
	al_destroy_bitmap(bgImage03);
	al_destroy_bitmap(bgImage04);
	al_destroy_bitmap(ShieldIcon);
	al_destroy_bitmap(shieldgoldenimg);
	al_destroy_bitmap(ShieldGoldenIcon);
	al_destroy_bitmap(shieldimg);
	al_destroy_bitmap(bulletimg);
	al_destroy_bitmap(bulletpowerupimg);
	al_destroy_font(font36);
	al_destroy_font(font24);

	for (int i = 0; i < 6; i++) al_destroy_bitmap(explosion[i]);
	//al_destroy_event_queue(event_queue);


	return 0;
}


/*! 
 *  \brief     Main
 *  \details   Questo file e' il cuore di tutto il programma, che tramite le funzioni di allegro e l'input del giocatore renderizza il tutto.
 *  \author    Catanese Antonino
 *  \version   1.0
 *  \date      2015
 */

/**
 * The time class represents a moment of time.
 *
 * \author My Name
 */
