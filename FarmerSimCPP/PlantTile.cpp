#include "raylib.h"
#include "PlantTile.h"

PlantTile::PlantTile(PlantTypes p, Sprite tex) {
	this->type = p;
	this->sprite = tex;
}
PlantTile::PlantTile() {}


