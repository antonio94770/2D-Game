


struct Bullet		/** Struttura laser. Questa struttura contiene tutte le informazioni del missile della navicella che può essere spararato dopo aver raccolto il corrispondente superpotere. */
{
	int x;
	int y;
	int xpowerup;
	int ypowerup;
	bool live;
	int speed;
	int poweupspeed;	
	ALLEGRO_BITMAP *icona; /**< Icona del superpotere */
	ALLEGRO_BITMAP *image; /**< Immagine del laser*/
};


void InitBullet(Bullet &, SpaceShip, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *); /**< Inizializzazione della struttura laser */
void DrawBulletPowerUp(Bullet &);			/**< Stampa del superpotere */
void DrawIconaPowerUp(Bullet &, bool);			/**< Stampa dell'icona in alto a del superpotere */
void UpdatePowerUp(Bullet &, SpaceShip, bool &, bool &, bool, ALLEGRO_BITMAP *); /**< Aggiornamento del superpotere */
void UpdateBullet(Bullet &, bool &, SpaceShip, Enemy &, ALLEGRO_BITMAP *);	 /**< Aggiornamento del laser */
void DrawBullet(Bullet); 				/**< Stampa del laser */
