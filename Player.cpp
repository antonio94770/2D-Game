#include "object.h"


void InitShip(SpaceShip &ship, ALLEGRO_BITMAP *image)
{
	ship.x = 20;
	ship.y = ScreenHeight / 2;
	ship.speed = 5;
	ship.physics = 3;
	ship.score = 0;
	ship.image = image;
}

void DrawMap_Text_Player(ALLEGRO_COLOR color, SpaceShip ship, ALLEGRO_FONT *font)
{
	al_draw_line(0, ScreenHeight - 10, ScreenWidth, ScreenHeight - 10, color, 30.0);		//Riga Sotto
	al_draw_line(0, 10, ScreenWidth, 10, color, 30.0);									//Riga Sopra
	al_draw_textf(font, al_map_rgb(44, 177, 255), 0, 50, ALLEGRO_ALIGN_LEFT, "Points: %d", ship.score);
	al_draw_bitmap(ship.image, ship.x, ship.y, 0);
}

void SetPlayerImage(SpaceShip &ship, ALLEGRO_BITMAP *image){
	if (image != ship.image)
		ship.image = image;
}
