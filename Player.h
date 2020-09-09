


enum Direction
{
	UP, DOWN, STOP
};

struct SpaceShip /** Struttura navicella spaziale */
{
	int ID;
	int x;
	int y;
	int speed;
	int physics;
	int score;
	int bestscore;

	ALLEGRO_BITMAP *image;
};



void InitShip(SpaceShip &, ALLEGRO_BITMAP); 	/**< Inizializzazione navicella spaziale. Adesso parlo di tutto quello di importante che questa funzione fa cioè..... */
void DrawMap_Text_Player(ALLEGRO_COLOR, SpaceShip, ALLEGRO_FONT);
void SetPlayerImage(SpaceShip &, ALLEGRO_BITMAP);
