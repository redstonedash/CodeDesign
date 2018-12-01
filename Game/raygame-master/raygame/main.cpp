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

	objectPool.push_back(GameObject("resources/models/MAPPART_01.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_02.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_03.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_04.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_05.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_06.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_07.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_08.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_09.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_10.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_11.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_12.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_13.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_14.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_15.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_16.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_17.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_18.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_19.obj"));
	objectPool.push_back(GameObject("resources/models/MAPPART_20.obj"));



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
			(IsKeyDown(KEY_A) - IsKeyDown(KEY_D)),
			0,
			(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)),
		};
		acceleratePlayer(&player, wishdir);
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(WHITE);

		BeginMode3D(player.camera);

		updatePlayer(&player, mouseDelta, objectPool);

		for (int i = 0; i < objectPool.size(); i++) {
			if (objectPool.at(i).enabled) {
				objectPool.at(i).draw(player.camera);
			}
		}


		//DrawGrid(3000, 10.0f);        // Draw a grid

		EndMode3D();

		DrawFPS(0, 0);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}