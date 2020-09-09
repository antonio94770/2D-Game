#include "object.h"

bool InizializzaLivello(ALLEGRO_SAMPLE_INSTANCE *songInstance, bool &flagMenu, bool &SpawnShieldIcon, bool &SpawnBulletIcon, bool &FlagHoLoScudo, bool &FlagHoLaser, bool &GoldenShield, bool &HoColliso, bool &Draw, bool &HoSparato, bool &flagRecord, SpaceShip &ship, int &dir, bool &flagEsplosione, int &frame, bool &Dead){
	al_stop_sample_instance(songInstance);
	flagMenu = true;
	SpawnShieldIcon = false;
	SpawnBulletIcon = false;
	FlagHoLoScudo = false;
	FlagHoLaser = false;
	GoldenShield = false;
	HoColliso = false;
	Draw = true;
	HoSparato = false;
	if (flagRecord){
		flagRecord = false;
		ship.bestscore = ship.score;
	}
	dir = DOWN;
	flagEsplosione = false;
	frame = 0;
	Dead = false;
	return true;
}