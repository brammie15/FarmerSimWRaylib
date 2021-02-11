#pragma once
#include "raylib.h"
#include "SpriteUtils.h"
#include "PlantTile.h"
class GroundTile {
    public:
        Sprite sprite;
        PlantTile CurrentPlant;
        
        void SetupRest();
        void setCurrentTex(Texture2D g);
        //Texture2D getCurrentTex();
        GroundTile();
       

};
