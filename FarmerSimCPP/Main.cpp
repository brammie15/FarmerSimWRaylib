#include "raylib.h"
#include "raymath.h"
#include "GroundTile.h"
#include "SpriteUtils.h"
//#include "PlantTile.h"

const Rectangle ZERO_REC{ 0,0,0,0 };
const Vector2 ZERO_VEC{ 0,0 };
enum ItemType { empty = 0, wheatSeed = 1 };
//enum PlantTypes { Wheat = 0, Berry = 1 };





int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1600;

	const int screenHeight = 800;
	InitWindow(screenWidth, screenHeight, "Farmer Sim");
	Texture2D FarmerTex = LoadTexture("Textures/Farmer.png");
	Texture2D SkyTex = LoadTexture("Textures/sky.png");
	Texture2D GrassTex = LoadTexture("Textures/Grass.png");
	Texture2D SelectionTex = LoadTexture("Textures/Selection.png");
	Texture2D DirtTex = LoadTexture("Textures/dirt.png");
	Texture2D WheatTex = LoadTexture("Textures/Wheat.png");
	Texture2D EmptyTex = LoadTexture("Textures/Empty.png");
	Texture2D BackgroundUITex = LoadTexture("Textures/background.png");
	int selectionIndex;

	Sprite Farmer = createSprite(FarmerTex, Vector2{ 32, 32 }, 2, 1, Vector2{ 0, 0 }, 0, Vector2{ 0, screenHeight - (160 * 3) });
	Sprite SelectionBox = createSprite(SelectionTex, Vector2{ 16, 16 }, 1, 1, Vector2{ 0, 0 }, 0, Vector2{ 0, screenHeight - 160 });

	bool Facing = false;
	bool Selecting = false;

	Rectangle SkyRec = { 0, 0, (float)SkyTex.width, (float)SkyTex.height };
	Rectangle SkyRecScale = { 0, 0, 1600, 800 + 160 };
	//TODO: Improve ground System ALOT
	GroundTile GroundTiles[10];
	for (int a = 0; a < 10; a++) {
		GroundTile tile = GroundTile();
		tile.sprite.texture = GrassTex;
		tile.sprite.pos.x = a * 160;
		tile.sprite.pos.y = screenHeight - 160;
		tile.sprite.frame = 1;
		tile.sprite.frameSize = Vector2{ 16,16 };
		tile.sprite.maxFrame = 1;
		tile.sprite.origin = Vector2{ 0,0 };


		//PlantTile plant = PlantTile(Wheat);
		//plant.sprite.pos.x = a*160;
		//plant.sprite.pos.y = screenHeight - (160*2);
		//tile.CurrentPlant = plant;
		//tile.CurrentPlant.tile.frame = GetRandomValue(0,8);
		GroundTiles[a] = tile;
	}

	SetTargetFPS(60);               
	while (!WindowShouldClose())    
	{
		//Possible TODO: add/implemnt input system (Optional)
		if (IsKeyDown(KEY_D)) {
			if (Farmer.pos.x < screenWidth - 160) {
				Farmer.pos.x += 4.0f;
			}
			Facing = false;
		}
		if (IsKeyDown(KEY_A)) {
			if (Farmer.pos.x > 0) {
				Farmer.pos.x -= 4.0f;
			}
			Facing = true;
		}
		if (IsKeyDown(KEY_S)) {
			Selecting = true;
		}
		else {
			Selecting = false;
		}
		if (Facing) {
			Farmer.frame = 1;
		}
		else {
			Farmer.frame = 0;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		//TODO: SPRITES R LIFE
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexturePro(SkyTex, SkyRec, SkyRecScale, Vector2{ 0, 0 }, 0, RAYWHITE);
		drawSprite(&Farmer, 0, 10, false);

		for (int x = 0; x < 10; x++) {
			GroundTile t = GroundTiles[x];
			drawSprite(&t.sprite, 0, 10, false);
			//drawSprite(&t.CurrentPlant.tile,0,10,false);       
		}

		if (Selecting) {
			selectionIndex = round(Remap(Farmer.pos.x, 0, screenWidth, 0, 10));
			SelectionBox.pos.x = selectionIndex * 160;

			drawSprite(&SelectionBox, 0, 10, false);

		}

		DrawFPS(10, 10);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(SelectionTex);
	UnloadTexture(SkyTex);
	UnloadTexture(GrassTex);
	UnloadTexture(FarmerTex);
	UnloadTexture(DirtTex);
	UnloadTexture(EmptyTex);
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}