#include "raylib.h"
#include "GroundTile.h"

GroundTile::GroundTile() {
    
}
void GroundTile::SetupRest() {
    //GrassRec = { 0.0f, 0.0f, (float)CurrentTex.width, (float)CurrentTex.height };
    //GrassRecScale = { 0.0f, 0.0f, (float)CurrentTex.width * 10, (float)CurrentTex.height * 10 };

}

void GroundTile::Plant(PlantTypes type, Texture2D tex[]) {
    if (this->HasPlant == true) {
        return;
    }else {
        HasPlant = true;
        PlantTile p = PlantTile();
        this->sprite.texture = LoadTexture("Textures/dirt.png");
        p.sprite = createSprite(tex[type], Vector2{ 16,16 }, 8, 1, Vector2{ 0,0 }, 2, Vector2{ 100,100 });
        p.sprite.pos.x = this->sprite.pos.x;
        p.sprite.pos.y = this->sprite.pos.y - 160;
        this->CurrentPlant = p;
    }

}

