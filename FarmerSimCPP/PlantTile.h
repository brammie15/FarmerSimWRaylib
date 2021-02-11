#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
enum PlantTypes { Wheat = 0, Berry = 1 };
class PlantTile {
public:
	Sprite sprite;
	int growStage;
	PlantTypes type;
	PlantTile(PlantTypes p);
};
