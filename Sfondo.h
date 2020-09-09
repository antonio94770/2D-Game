


struct Sfondo			/** Struttura sfondo */
{	
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
};


void InitSfondo(Sfondo &, float, float, float, float, int, int, int, int, ALLEGRO_BITMAP);
void UpdateSfondo(Sfondo &);
void DrawSfondo(Sfondo &);
