#pragma once
#include "raylib.h"

struct Player { //Player is handled diferently than every other object in the game
	Camera camera = { 0 };
	Vector3 velocity = { 0,0,0 };
	Vector2 direction = { 0,0 };
	Vector3 previousPosition = {0,0,0};
	Player() {
		camera.position = { 0.0f, 16.0f, 0.0f };
		camera.target = { 0.0f, 0.0f, 0.0f };
		camera.up = { 0.0f, 1.0f, 0.0f };
		camera.fovy = 45.0f;
		camera.type = CAMERA_PERSPECTIVE;
	}
};

void sourceAccelerate(Player *p, Vector3 wishdir, float wishspeed, float accel);
void updatePlayer(Player* p, Vector2 mouseDelta);
void acceleratePlayer(Player* p, Vector3 wishdir);
bool playerDetectColision(Player* p, Model *m);