#include "object.h"

void InitEnemy(Enemy &enemy, ALLEGRO_BITMAP *image){
	enemy.x = ScreenWidth / 2;
	enemy.y = rand() % 397 + 27;
	enemy.speed = 3;
	enemy.image = image;
	enemy.live = true;
}

void UpdateEnemy(Enemy &enemy, ALLEGRO_BITMAP *image){
	if (enemy.x < -(al_get_bitmap_width(enemy.image))){					//Larghezza meteorite
		enemy.x = ScreenWidth;
		enemy.y = (rand() % 16 + 1) * 30;
		enemy.live = true;
		enemy.image = image;
	}
	enemy.x = enemy.x - enemy.speed;

}

void DrawEnemy(Enemy &enemy, int &rotazione){
	int a = al_get_bitmap_width(enemy.image);
	int b = al_get_bitmap_height(enemy.image);
	if (rotazione > 360) rotazione = 0;					//Rotazione asteroidi
	rotazione++;
	//al_draw_bitmap(enemy.image, enemy.x, enemy.y, 0);
	al_draw_rotated_bitmap(enemy.image, a / 2, b / 2, enemy.x + a / 2, enemy.y + b / 2, rotazione *3.14 / 180, 0);
}