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

struct Player { //Player is handled diferently than every other object in the game
	Camera camera = { 0 };
	Vector3 velocity = { 0,0,0 };
	Vector2 direction = { 0,0 };
	Player() {
		camera.position = { 0.0f, 15.0f, -50.0f };
		camera.target = { 0.0f, 0.0f, 0.0f };
		camera.up = { 0.0f, 1.0f, 0.0f };
		camera.fovy = 45.0f;
		camera.type = CAMERA_PERSPECTIVE;
	}
};

float DotProduct(Vector3 v1, Vector3 v2) {
	return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}

void PM_Accelerate(Player *p, Vector3 wishdir, float wishspeed, float accel) {
	// q2 style
	int			i;
	float		addspeed, accelspeed, currentspeed;

	currentspeed = DotProduct(p->velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0) {
		return;
	}
	accelspeed = accel * GetFrameTime()*wishspeed;
	if (accelspeed > addspeed) {
		accelspeed = addspeed;
	}
	p->velocity.x += accelspeed * wishdir.x;
	p->velocity.y += accelspeed * wishdir.y;
	p->velocity.z += accelspeed * wishdir.z;
}
  
void updatePlayer(Player* p, Vector2 mouseDelta) {
	p->direction.x += mouseDelta.x/40;
	p->direction.y += mouseDelta.y/40;
	p->camera.position.x -= p->velocity.x*GetFrameTime();
	p->camera.position.y -= p->velocity.y*GetFrameTime();
	p->camera.position.z -= p->velocity.z*GetFrameTime();
	p->camera.target.x = p->camera.position.x + sin((p->direction.x / 360)*PI * 2);
	p->camera.target.y = p->camera.position.y + tan((p->direction.y / 360)*PI * 2);
	p->camera.target.z = p->camera.position.z + cos((p->direction.x / 360)*PI * 2);
}

void acceleratePlayer(Player* p, Vector3 wishdir) { //TODO: make quakey
	wishdir = { wishdir.x * cos((-p->direction.x / 360)*PI * 2) + wishdir.z * sin((p->direction.x / 360)*PI * 2), 0, wishdir.x * sin((-p->direction.x / 360)*PI * 2) + wishdir.z * cos((p->direction.x / 360)*PI * 2) };
	PM_Accelerate(p, wishdir, 75, 2.5f);
	p->velocity.x *= 0.93f;
	p->velocity.y *= 0.93f;
	p->velocity.z *= 0.93f;
}

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	SetConfigFlags(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Model ramp = LoadModel("resources/models/cube.obj");
	Shader shader = LoadShader("resources/shaders/glsl330/base.vs",
		"resources/shaders/glsl330/test.fs");
	ramp.material.shader = shader;

	SetTargetFPS(60);
	Player player = Player();
	//--------------------------------------------------------------------------------------

	// Main game loop
	DisableCursor();
	Vector2 mouseDelta = { 0,0 };
	Vector2 mousePos = { 0,0 };
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		DisableCursor();
		mouseDelta.x = mousePos.x - GetMouseX();
		mouseDelta.y = mousePos.y - GetMouseY();
		mousePos = GetMousePosition();
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

		ClearBackground(RAYWHITE);

		BeginMode3D(player.camera);

		DrawModel(ramp, { -0.0f, 0.0f, 5.0f }, 10.0f, WHITE);

		//DrawCube({ -0.0f, 0.0f, 5.0f }, 5.0f, 5.0f, 5.0f, RED);

		DrawGrid(4000, 10.0f);        // Draw a grid

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