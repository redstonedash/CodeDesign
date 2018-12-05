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
#include "GameObject.h"
#include <vector>

int MAX_GAME_OBJECTS = 20;

std::vector<GameObject> objectPool;

void LoadLevelOne();

int mainMenu();

Player player = Player();

int main()
{
	objectPool = std::vector<GameObject>();
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

	SetTargetFPS(120);
	//--------------------------------------------------------------------------------------

	// Main game loop
	Vector2 mouseDelta = { 0,0 };
	Vector2 mousePos = { 0,0 };

	for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
		objectPool.push_back(GameObject());
	}

	mainMenu();

	DisableCursor();

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		if (player.finished) {
			mainMenu();
			player.finished = false;
			for (int i = 0; i < MAX_GAME_OBJECTS; i++) {
				objectPool.at(i).unload();
			}
		}
		time += GetFrameTime();
		
		mouseDelta.x = mousePos.x - GetMouseX();
		mouseDelta.y = mousePos.y - GetMouseY();
		mousePos = GetMousePosition();

		// Update
		//----------------------------------------------------------------------------------
		
		Vector3 wishdir = { 
			(IsKeyDown(KEY_A) - IsKeyDown(KEY_D)),
			0,
			(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)),
		};
		acceleratePlayer(&player, wishdir);
		BeginDrawing();

		ClearBackground(WHITE);

		BeginMode3D(player.camera);

		updatePlayer(&player, mouseDelta, objectPool);

		for (int i = 0; i < objectPool.size(); i++) { //draw all game objects
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

void LoadLevelOne() {
	player.spawnPoint = { 0,16,0 };
	player.camera.position = player.spawnPoint;
	objectPool.at(0 ).enablePlatform("resources/models/MAPPART_01.obj");
	objectPool.at(1 ).enablePlatform("resources/models/MAPPART_02.obj");
	objectPool.at(2 ).enablePlatform("resources/models/MAPPART_03.obj");
	objectPool.at(3 ).enablePlatform("resources/models/MAPPART_04.obj");
	objectPool.at(4 ).enablePlatform("resources/models/MAPPART_05.obj");
	objectPool.at(5 ).enablePlatform("resources/models/MAPPART_06.obj");
	objectPool.at(6 ).enablePlatform("resources/models/MAPPART_07.obj");
	objectPool.at(7 ).enablePlatform("resources/models/MAPPART_08.obj");
	objectPool.at(8 ).enablePlatform("resources/models/MAPPART_09.obj");
	objectPool.at(9 ).enablePlatform("resources/models/MAPPART_10.obj");
	objectPool.at(10).enablePlatform("resources/models/MAPPART_11.obj");
	objectPool.at(11).enablePlatform("resources/models/MAPPART_12.obj");
	objectPool.at(12).enablePlatform("resources/models/MAPPART_13.obj");
	objectPool.at(13).enablePlatform("resources/models/MAPPART_14.obj");
	objectPool.at(14).enablePlatform("resources/models/MAPPART_15.obj");
	objectPool.at(15).enablePlatform("resources/models/MAPPART_16.obj");
	objectPool.at(16).enablePlatform("resources/models/MAPPART_17.obj");
	objectPool.at(17).enablePlatform("resources/models/MAPPART_18.obj");
	objectPool.at(18).enablePlatform("resources/models/MAPPART_19.obj");
	objectPool.at(18).goal = true;
	objectPool.at(19).enablePlatform("resources/models/MAPPART_20.obj");
	objectPool.at(19).goal = true;
}

void LoadLevelTwo() {
	player.spawnPoint = { 0,200,0 };
	player.camera.position = player.spawnPoint;
	objectPool.at(0).enablePlatform("resources/models/MAPPART_1_01.obj");
	objectPool.at(1).enablePlatform("resources/models/MAPPART_1_02.obj");
	objectPool.at(2).enablePlatform("resources/models/MAPPART_1_03.obj");
	objectPool.at(3).enablePlatform("resources/models/MAPPART_1_04.obj");
	objectPool.at(4).enablePlatform("resources/models/MAPPART_1_05.obj");
	objectPool.at(5).enablePlatform("resources/models/MAPPART_1_06.obj");
	objectPool.at(6).enablePlatform("resources/models/MAPPART_1_07.obj");
	objectPool.at(7).enablePlatform("resources/models/MAPPART_1_08.obj");
	objectPool.at(8).enablePlatform("resources/models/MAPPART_1_09.obj");
	objectPool.at(8).goal = true;
	objectPool.at(9).enablePlatform("resources/models/MAPPART_1_10.obj");
	objectPool.at(9).goal = true;
}

void ClearObjectPool() {
	for (int i = 0; i < objectPool.size(); i++) {
		if (objectPool.at(i).enabled) {
			objectPool.at(i).disable();
		}
	}
}

int mainMenu() {
	Camera menuCam;
	menuCam.up = { 0,1,0 };
	menuCam.position = { -110,0,0 };
	menuCam.target = { 0,0,0 };
	menuCam.fovy = 90.0f;
	menuCam.type = CAMERA_PERSPECTIVE;
	Model leftButton = LoadModel("resources/models/button2.obj");
	Model rightButton = LoadModel("resources/models/button1.obj");
	Model menuPlane = LoadModel("resources/models/menuPlane.obj");
	leftButton.material.shader = LoadShader("resources/shaders/glsl330/base.vs",
		"resources/shaders/glsl330/buttonShadderBlue.fs");
	rightButton.material.shader = LoadShader("resources/shaders/glsl330/base.vs",
		"resources/shaders/glsl330/buttonShadderRed.fs");
	menuPlane.material.shader = LoadShader("resources/shaders/glsl330/base.vs",
		"resources/shaders/glsl330/menu.fs");
	int leftLoc = GetShaderLocation(leftButton.material.shader, "pressed");
	int rightLoc = GetShaderLocation(rightButton.material.shader, "pressed");
	int timeLoc = GetShaderLocation(menuPlane.material.shader, "time");
	float time[] = { 0 };
	float left[] = { 1 };
	float right[] = { 1 };
	ClearObjectPool();
	EnableCursor();
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		time[0] += GetFrameTime()*4;
		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode3D(menuCam);
		DrawModel(leftButton, { -100,-2, -5.5 }, 1, WHITE);
		DrawModel(rightButton, { -100,-2, 5.5 }, 1, WHITE);
		SetShaderValue(menuPlane.material.shader, timeLoc, time, 1);
		if (GetMousePosition().x>150 && GetMousePosition().x<420 && GetMousePosition().y>350 && GetMousePosition().y<430) {
			left[0] = 1;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				DisableCursor();
				LoadLevelOne();
				break;
			}
		} else {
			left[0] = 0;
		}
		SetShaderValue(leftButton.material.shader, leftLoc, left, 1);
		if (GetMousePosition().x>540 && GetMousePosition().x<800 && GetMousePosition().y>350 && GetMousePosition().y<430) {
			right[0] = 1;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				DisableCursor();
				LoadLevelTwo();
				break;
			}
		} else {
			right[0] = 0;
		}
		SetShaderValue(rightButton.material.shader, rightLoc, right, 1);
		DrawModel(menuPlane, { 0,-5, 0 }, 1, WHITE);
		EndMode3D();
		DrawText(std::to_string(GetMousePosition().x).c_str(), 100, 100, 100, BLACK);
		EndDrawing();
	}
	return 0;
}