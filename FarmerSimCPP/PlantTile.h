#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
enum PlantTypes { Wheat = 0, potato = 1 };
class PlantTile {
public:
	Sprite sprite;
	int growStage;
	PlantTypes type;
	PlantTile();
	PlantTile(PlantTypes p,Sprite tex);
};
