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

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	// Define the camera to look into our 3d world
	Camera camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 120.0f;
	camera.type = CAMERA_PERSPECTIVE;


	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		RayHitInfo h = RayHitInfo();
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		DrawCube({ -4.0f, 0.0f, 2.0f }, 2.0f, 5.0f, 2.0f, RED);
		DrawCubeWires({ -4.0f, 0.0f, 2.0f }, 2.0f, 5.0f, 2.0f, GOLD);
		DrawCubeWires({ -4.0f, 0.0f, -2.0f }, 3.0f, 6.0f, 2.0f, MAROON);

		DrawSphere({ -1.0f, 0.0f, -2.0f }, 1.0f, GREEN);
		DrawSphereWires({ 1.0f, 0.0f, 2.0f }, 2.0f, 16, 16, LIME);

		DrawCylinder({ 4.0f, 0.0f, -2.0f }, 1.0f, 2.0f, 3.0f, 4, SKYBLUE);
		DrawCylinderWires({ 4.0f, 0.0f, -2.0f }, 1.0f, 2.0f, 3.0f, 4, DARKBLUE);
		DrawCylinderWires({ 4.5f, -1.0f, 2.0f }, 1.0f, 1.0f, 2.0f, 6, BROWN);

		DrawCylinder({ 1.0f, 0.0f, -4.0f }, 0.0f, 1.5f, 3.0f, 8, GOLD);
		DrawCylinderWires({ 1.0f, 0.0f, -4.0f }, 0.0f, 1.5f, 3.0f, 8, PINK);

		DrawGrid(10, 1.0f);        // Draw a grid

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