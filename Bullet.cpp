#include "object.h"



void InitBullet(Bullet &bullet, SpaceShip ship, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *icona)
{
	bullet.x = 0;
	bullet.y = 0;
	bullet.xpowerup = ScreenWidth;
	bullet.ypowerup = (rand() % 16 + 1) * 30;
	bullet.speed = 10;
	bullet.poweupspeed = 5;
	bullet.image = image;
	bullet.icona = icona;
}

void DrawBulletPowerUp(Bullet &bullet)
{
	al_draw_bitmap(bullet.icona, bullet.xpowerup, bullet.ypowerup, 0);
}

void DrawIconaPowerUp(Bullet &bullet, bool flagholoscudo)
{
	int x = 60;
	if (flagholoscudo) x = 110;
	al_draw_bitmap(bullet.icona, ScreenWidth - x, 60, 0);
}


void UpdatePowerUp(Bullet &bullet, SpaceShip ship, bool &spawn, bool &flagholaser, bool FlagMorto, ALLEGRO_BITMAP *image)
{
	bool colliso = false;
	if (CheckPoweUpCollideBullet(ship, bullet) && !FlagMorto){
		flagholaser = true;
		colliso = true;
	}
	if (bullet.xpowerup < -(al_get_bitmap_width(bullet.icona)) || colliso){
		bullet.xpowerup = ScreenWidth;
		bullet.ypowerup = (rand() % 16 + 1) * 30;
		spawn = false;
		colliso = false;
	}
	bullet.xpowerup = bullet.xpowerup - bullet.poweupspeed;
}

void UpdateBullet(Bullet &bullet, bool &hosparato, SpaceShip ship, Enemy &enemy, ALLEGRO_BITMAP *image)
{
	if(hosparato)bullet.x = bullet.x + bullet.speed;
	else bullet.y = ship.y + al_get_bitmap_height(ship.image);
	if (bullet.x > ScreenWidth){
		hosparato = false;
		bullet.x = ship.x + al_get_bitmap_width(ship.image);
	}
	else if (hosparato && CheckCollideBullet(bullet, enemy)){
		enemy.live = false;
		enemy.image = image;
		hosparato = false;
		bullet.x = ship.x + al_get_bitmap_width(ship.image);
	}
}


void DrawBullet(Bullet bullet)
{
	al_draw_bitmap(bullet.image, bullet.x, bullet.y, 0);

}
