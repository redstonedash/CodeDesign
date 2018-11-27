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

//TODO: move to custom math class

float DotProduct(Vector3 v1, Vector3 v2) {
	return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}

float distance(Vector3 v1, Vector3 v2) {
	return sqrtf(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

//TODO: move to player manager

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
	p->direction.x += mouseDelta.x/15;
	p->direction.y += mouseDelta.y/15;
	p->camera.position.x -= p->velocity.x*GetFrameTime();
	p->camera.position.y -= p->velocity.y*GetFrameTime();
	p->camera.position.z -= p->velocity.z*GetFrameTime();
	p->camera.target.x = p->camera.position.x + sin((p->direction.x / 360)*PI * 2);
	p->camera.target.y = p->camera.position.y + tan((p->direction.y / 360)*PI * 2);
	p->camera.target.z = p->camera.position.z + cos((p->direction.x / 360)*PI * 2);
}

void acceleratePlayer(Player* p, Vector3 wishdir) {
	wishdir = { wishdir.x * cos((-p->direction.x / 360)*PI * 2) + wishdir.z * sin((p->direction.x / 360)*PI * 2), 0, wishdir.x * sin((-p->direction.x / 360)*PI * 2) + wishdir.z * cos((p->direction.x / 360)*PI * 2) };
	PM_Accelerate(p, wishdir, 100, 3.5f); //TODO: make these values constants
	//p->velocity.y += GetFrameTime();
	if (wishdir.x == 0 && wishdir.y == 0 && wishdir.z == 0) {
		p->velocity.x *= 0.8f;
		p->velocity.z *= 0.8f;
		if (distance({ 0,0,0 }, p->velocity) < 0.3f) {
			p->velocity = { 0,0,0 };
		}
	} else {
		p->velocity.x *= 0.925f;
		p->velocity.z *= 0.925f;
	}
}


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

	std::ifstream in("resources/shaders/glsl330/test.fs");
	std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
	std::cout << contents.c_str() << "\n\n";
	contents.replace(contents.find("@n"),2,std::to_string(lightCount));
	contents.replace(contents.find("@n"), 2, std::to_string(lightCount));

	std::cout << contents.c_str();
	

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
	DisableCursor();
	int lightLoc = GetShaderLocation(ramp.material.shader, "lightPos");
	float lightPos[3] = { player.camera.position.x,player.camera.position.y,player.camera.position.z };
	int cameraDirLoc = GetShaderLocation(ramp.material.shader, "cameraPos");
	float cameraPosition[3] = { player.camera.target.x-player.camera.position.x,player.camera.target.y - player.camera.position.y,player.camera.target.z - player.camera.position.z };
	
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		time += GetFrameTime();
		cameraPosition[0] = player.camera.position.x ;
		cameraPosition[1] = player.camera.position.y ;
		cameraPosition[2] = player.camera.position.z ;
		lightPos[0] = sin(time) * 20;
		lightPos[1] = 15;
		lightPos[2] = cos(time) * 20;
		SetShaderValue(ramp.material.shader, lightLoc, lightPos, 3);
		SetShaderValue(ramp.material.shader, cameraDirLoc, cameraPosition, 3);
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

		DrawModel(ramp, {-0.0f, -0.0f, 2.0f }, 1.0f, WHITE);

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