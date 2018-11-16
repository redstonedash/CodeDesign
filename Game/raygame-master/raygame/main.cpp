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

struct Player { //Player is handled diferently than every other object in the game
	Camera camera = { 0 };
	Player() {
		camera.position = { 0.0f, 0.0f, 10.0f };
		camera.target = { 0.0f, 0.0f, 0.0f };
		camera.up = { 0.0f, 1.0f, 0.0f };
		camera.fovy = 45.0f;
		camera.type = CAMERA_PERSPECTIVE;
	}
	Vector3 velocity = { 0,0,0 };
};

void updatePlayer(Player* p) {
	p->camera.position.x += p->velocity.x*GetFrameTime();
	p->camera.position.y += p->velocity.y*GetFrameTime();
	p->camera.position.z += p->velocity.z*GetFrameTime();
}

void acceleratePlayer(Player* p, Vector3 wishdir) { //TODO: make quakey
	p->velocity.x += wishdir.x;
	p->velocity.y += wishdir.y;
	p->velocity.z += wishdir.z;
}

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	// Define the camera to look into our 3d world
	


	SetTargetFPS(60);
	Player player = Player();
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		RayHitInfo h = RayHitInfo();
		// Update
		//----------------------------------------------------------------------------------
		Vector3 wishdir = { 
			(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)),
			0,
			(IsKeyDown(KEY_A) - IsKeyDown(KEY_D)),
		};
		acceleratePlayer(&player, wishdir);
		updatePlayer(&player);
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(player.camera);

		DrawCube({ -0.0f, 0.0f, 5.0f }, 5.0f, 5.0f, 5.0f, RED);

		DrawGrid(1000, 1.0f);        // Draw a grid

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