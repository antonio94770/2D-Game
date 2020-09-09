



bool Collisione(ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy, float x, float y, float ex, float ey, int width, int height);
bool CollisioneBordi(SpaceShip);
bool CheckPoweUpCollideShield(SpaceShip &, Shield &);
bool CheckPoweUpCollideBullet(SpaceShip &, Bullet &);
bool CheckCollideBullet(Bullet &, Enemy &);