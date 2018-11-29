/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <iostream>
#include <math.h>
#include "PlayerMovement.h"
#include <fstream>
#include <string> 
#include "Platform.h"
#include <vector>

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 960;
	int screenHeight = 640;
	int lightCount = 2;
	double time = 0;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	/*std::ifstream in("resources/shaders/glsl330/test.fs");
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	std::cout << contents.c_str() << "\n\n";
	contents.replace(contents.find("@n"),2,std::to_string(lightCount));
	contents.replace(contents.find("@n"), 2, std::to_string(lightCount));

	std::cout << contents.c_str();*/

	SetTargetFPS(60);
	Player player = Player();
	//--------------------------------------------------------------------------------------

	// Main game loop
	DisableCursor();
	Vector2 mouseDelta = { 0,0 };
	Vector2 mousePos = { 0,0 };
	DisableCursor();
	
	std::vector<GameObject> objectPool = std::vector<GameObject>();

	objectPool.push_back(GameObject({ 0, 0, 0 }));

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		time += GetFrameTime();
		
		mouseDelta.x = mousePos.x - GetMouseX();
		mouseDelta.y = mousePos.y - GetMouseY();
		mousePos = GetMousePosition();
		//std::cout << player.camera.position.x << " " << player.camera.position.y << " " << player.camera.position.z << "\n";
		//std::cout << mouseDelta.x << "\n";
		RayHitInfo h = RayHitInfo();
		// Update
		//----------------------------------------------------------------------------------
		
		Vector3 wishdir = { 
			(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
			0,
			(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)),
		};
		acceleratePlayer(&player, wishdir);
		updatePlayer(&player, mouseDelta);
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(WHITE);

		BeginMode3D(player.camera);

		for (int i = 0; i < objectPool.size(); i++) {
			if (objectPool.at(i).enabled) {
				playerDetectColision(&player, &objectPool.at(i).plat);
				objectPool.at(i).draw(player.camera);
			}
		}


		//DrawGrid(4000, 10.0f);        // Draw a grid

		EndMode3D();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}