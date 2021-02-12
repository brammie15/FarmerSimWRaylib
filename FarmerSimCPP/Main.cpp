#include "raylib.h"
#include "raymath.h"
#include "GroundTile.h"
#include "SpriteUtils.h"


const Rectangle ZERO_REC{ 0,0,0,0 };
const Vector2 ZERO_VEC{ 0,0 };
enum ItemType {empty = 0,hoe = 1, wheatSeed = 2};
class Item {
	public:
		bool IsUseable;
		ItemType type;
		int amount;
		Item();
		Item(bool isUseable, ItemType type, int amount) {
			this->IsUseable = isUseable;
			this->type = type;
			this->amount = amount;
		}

		
};


//void Plant(PlantTypes type, int selec, GroundTile a[],Texture2D tex[]) {
//	GroundTile t = a[selec];
//	if (t.HasPlant == true) {
//		return;
//	}
//	else {
//		switch (type){
//			case Wheat:
//				t.CurrentPlant = PlantTile(Wheat, createSprite(tex[wheatSeed], Vector2{ 16,16 }, 8, 1, Vector2{ 0,0 }, 1, Vector2{ 0,0 }));
//				t.CurrentPlant.sprite.pos.y = GetScreenHeight() - (2 * 160);
//				t.CurrentPlant.sprite.pos.x = t.sprite.pos.x;
//				break;
//			case Berry:
//				break;
//			default:
//				break;
//		}
//	
//	}
//}

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
	Texture2D HoeTex = LoadTexture("Textures/diamond_hoe.png");
	Texture2D SelectionBoxTex = LoadTexture("Textures/SelectionBox.png");
	Texture2D PlantTex[] = { WheatTex };

	Item items[3];
	for (int i = 0; i < 3; i++)
	{
		items[i] = Item(false, empty, 1);
	}

	Sprite Farmer = createSprite(FarmerTex, Vector2{ 32, 32 }, 2, 1, Vector2{ 0, 0 }, 0, Vector2{ 0, screenHeight - (160 * 3) });
	Sprite SelectionBox = createSprite(SelectionTex, Vector2{ 16, 16 }, 1, 1, Vector2{ 0, 0 }, 0, Vector2{ 0, screenHeight - 160 });
	Sprite SelectionBoxItem = createSprite(SelectionBoxTex, Vector2{ 22,22 }, 1, 1, Vector2{ 0, 0 }, 0, Vector2{ 0, 0 });

	int selectionIndex = 0;
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

		GroundTiles[a] = tile;
	}
	
	SetTargetFPS(60);               
	while (!WindowShouldClose())    
	{
		//Possible TODO: add/implemnt input system (Optional)
		if (IsKeyDown(KEY_D)) {
			if (Farmer.pos.x < screenWidth - 160) {
				if (IsKeyDown(KEY_LEFT_SHIFT)) {
					Farmer.pos.x += 6.0f;
				}
				else {
					Farmer.pos.x += 4.0f;
				}
			}
			Farmer.frame = 0;
		}
		if (IsKeyDown(KEY_A)) {
			if (Farmer.pos.x > 0) {
				if (IsKeyDown(KEY_LEFT_SHIFT)) {
					Farmer.pos.x -= 6.0f;
				}
				else {
					Farmer.pos.x -= 4.0f;
				}
			}
			Farmer.frame = 1;
		}
		if (IsKeyDown(KEY_S)) {
			Selecting = true;
		}
		else {
			Selecting = false;
		}
		if (IsKeyDown(KEY_SPACE) && Selecting == true) {
			GroundTiles[selectionIndex].Plant(Wheat, PlantTex);
		}

		// Draw
		//TODO: SPRITES R LIFE
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexturePro(SkyTex, SkyRec, SkyRecScale, Vector2{ 0, 0 }, 0, RAYWHITE);
		drawSprite(&SelectionBoxItem, 0, 6, false);
		//drawSprite(&inv.CurrentItemSprite, 0, 7, false);
		drawSprite(&Farmer, 0, 10, false);
		for (int x = 0; x < 10; x++) {
			GroundTile t = GroundTiles[x];
			drawSprite(&t.sprite, 0, 10, false);
			drawSprite(&t.CurrentPlant.sprite,0,10,false);       
		}
		if (Selecting) {
			selectionIndex = round(Remap(Farmer.pos.x, 0, screenWidth, 0, 10));
			SelectionBox.pos.x = selectionIndex * 160;
			drawSprite(&SelectionBox, 0, 10, false);
		}
		//DrawFPS(10, 10);
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
	UnloadTexture(HoeTex);
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}