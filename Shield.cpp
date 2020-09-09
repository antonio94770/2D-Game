#include "object.h"

void InitShield(Shield &shield, ALLEGRO_BITMAP *image){
	shield.x = ScreenWidth;
	shield.y = (rand() % 16 + 1) * 30;
	shield.speed = 5;
	//shield.live = false;
	shield.image = image;
}

void DrawShield(SpaceShip &ship, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *icona){
	//std::cout << "Ho lo scudo!!" << std::endl;
	al_draw_bitmap(image, ship.x + 20, ship.y - 30, 0);
	al_draw_bitmap(icona, ScreenWidth - 60, 60, 0);

}

void UpdateShield(Shield &shield, SpaceShip &ship, bool &spawnshieldicon, bool &flagholoscudo, bool FlagMorto, bool &GoldenShield){
	bool colliso = false;
	if (CheckPoweUpCollideShield(ship, shield) && !FlagMorto){
		if (flagholoscudo) { GoldenShield = true; 	/*std::cout << "Ho il GOLDEN SHIELD!" << std::endl; */ }
		flagholoscudo = true;
		colliso = true;
	}
	if (shield.x < -(al_get_bitmap_width(shield.image)) || colliso){
		//shield.live = false;
		shield.x = ScreenWidth;
		shield.y = (rand() % 16 + 1) * 30;
		spawnshieldicon = false;
		colliso = false;
	}
	shield.x = shield.x - shield.speed;
}

void DrawShieldPowerUp(Shield shield){
	al_draw_bitmap(shield.image, shield.x, shield.y, 0);
}
