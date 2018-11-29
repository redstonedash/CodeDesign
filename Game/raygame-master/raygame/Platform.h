#pragma once
#include "raylib.h"
struct GameObject {
	Model plat = LoadModel("resources/models/cube.obj");
	Shader shader;
	int cameraLoc;
	Vector3 position;
	bool enabled = false;
	float cameraPosition[3] = { 0,0,0 };
	GameObject() {

	}
	GameObject(Vector3 Position) {
		shader = LoadShader("resources/shaders/glsl330/base.vs",
			"resources/shaders/glsl330/test.fs");
		plat.material.shader = shader;
		position = Position;
		enabled = true;
		cameraLoc = GetShaderLocation(plat.material.shader, "cameraPos");
	}
	void enablePlatform(Vector3 Position) {
		shader = LoadShader("resources/shaders/glsl330/base.vs",
			"resources/shaders/glsl330/test.fs");
		plat.material.shader = shader;
		position = Position;
		enabled = true;
		cameraLoc = GetShaderLocation(plat.material.shader, "cameraPos");
	}
	void draw(Camera c) {
		cameraPosition[0] = c.position.x;
		cameraPosition[1] = c.position.y;
		cameraPosition[2] = c.position.z;
		SetShaderValue(plat.material.shader, cameraLoc, cameraPosition, 3);
		DrawModel(plat, position, 1, WHITE);

	}
};
