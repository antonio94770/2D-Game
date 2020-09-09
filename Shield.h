


struct Shield			/** Struttura scudo */
{
	int x;
	int y;
	bool live;
	int speed;
	ALLEGRO_BITMAP *icona;
	ALLEGRO_BITMAP *image;
};

void InitShield(Shield &, ALLEGRO_BITMAP);
void DrawShield(SpaceShip &, ALLEGRO_BITMAP, ALLEGRO_BITMAP);
void UpdateShield(Shield &, SpaceShip &, bool &, bool &, bool, bool &);
void DrawShieldPowerUp(Shield);
