#include "object.h"
#define DEB(a) { ;}

bool Collisione(ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy, float x, float y, float ex, float ey, int width, int height){
	if (x + width < ex || x> ex + width || y + height<ey || y>ey + height) return false;
	else
	{
		int top = std::max(y, ey);
		int bottom = std::min(y + height, ey + height);
		int left = std::max(x, ex);
		int right = std::min(x + width, ex + width);

		for (int i = top; i < bottom; i++){
			for (int j = left; j < right; j++){
				al_lock_bitmap(player, al_get_bitmap_format(player), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(enemy, al_get_bitmap_format(enemy), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color = al_get_pixel(player, j - x, i - y);
				ALLEGRO_COLOR color2 = al_get_pixel(enemy, j - ex, i - ey);

				if (color.a != 0 && color2.a != 0){
					DEB(std::cout << "Ho colliso con l'asteroide." << std::endl;);
					return true;

				}

			}
		}

	}
	return false;
}

bool CollisioneBordi(SpaceShip ship){
	if (ship.y >= (ScreenHeight - 110) || ship.y <= 25){
		DEB(std::cout << "Ho colliso con i bordi." << std::endl;);
		return true;
	}
	return false;
}

bool CheckPoweUpCollideShield(SpaceShip &ship, Shield &shield){
	// AABB 1
	int x1Min = ship.x;
	int x1Max = ship.x + (al_get_bitmap_width(ship.image));
	int y1Max = ship.y + (al_get_bitmap_height(ship.image));
	int y1Min = ship.y;

	// AABB 2
	int x2Min = shield.x;
	int x2Max = shield.x + (al_get_bitmap_width(shield.image));
	int y2Max = shield.y + (al_get_bitmap_height(shield.image));
	int y2Min = shield.y;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	DEB(std::cout << "Ho preso lo scudo." << std::endl;);
	return true;
}


bool CheckPoweUpCollideBullet(SpaceShip &ship, Bullet &bullet){
	// AABB 1
	int x1Min = ship.x;
	int x1Max = ship.x + (al_get_bitmap_width(ship.image));
	int y1Max = ship.y + (al_get_bitmap_height(ship.image));
	int y1Min = ship.y;

	// AABB 2
	int x2Min = bullet.xpowerup;
	int x2Max = bullet.xpowerup + (al_get_bitmap_width(bullet.icona));
	int y2Max = bullet.ypowerup + (al_get_bitmap_height(bullet.icona));
	int y2Min = bullet.ypowerup;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	DEB(std::cout << "Ho preso il laser." << std::endl;);
	return true;
}

bool CheckCollideBullet(Bullet &bullet, Enemy &enemy){
	// AABB 1
	int x1Min = bullet.x;
	int x1Max = bullet.x + (al_get_bitmap_width(bullet.image));
	int y1Max = bullet.y + (al_get_bitmap_height(bullet.image));
	int y1Min = bullet.y;

	// AABB 2
	int x2Min = enemy.x;
	int x2Max = enemy.x + (al_get_bitmap_width(enemy.image));
	int y2Max = enemy.y + (al_get_bitmap_height(enemy.image));
	int y2Min = enemy.y;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	DEB(std::cout << "Colpito con il laser!" << std::endl;);
	return true;
}
