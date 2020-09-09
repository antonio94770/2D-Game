


struct Enemy			/** Struttura nemico */
{
	int x;
	int y;
	int speed;
	bool live;
	ALLEGRO_BITMAP *image;
};


void InitEnemy(Enemy &, ALLEGRO_BITMAP);
void UpdateEnemy(Enemy &, ALLEGRO_BITMAP);
void DrawEnemy(Enemy &, int &);
