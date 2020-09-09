#include "object.h"

void InitSfondo(Sfondo &sfondo, float x, float  y, float velx, float vely, int width, int height, int dirx, int diry, ALLEGRO_BITMAP *image){
	sfondo.x = x;
	sfondo.y = y;
	sfondo.velX = velx;
	sfondo.velY = vely;
	sfondo.width = width;
	sfondo.height = height;
	sfondo.dirX = dirx;
	sfondo.y = diry;
	sfondo.image = image;
}

void UpdateSfondo(Sfondo &sfondo){
	sfondo.x = sfondo.x + sfondo.velX * sfondo.dirX;
	if (sfondo.x + sfondo.width <= 0)
		sfondo.x = 0;
}

void DrawSfondo(Sfondo &sfondo){
	al_draw_bitmap(sfondo.image, sfondo.x, sfondo.y, 0);
	if (sfondo.x + sfondo.width < ScreenWidth)
		al_draw_bitmap(sfondo.image, sfondo.x + sfondo.width, sfondo.y, 0);
}