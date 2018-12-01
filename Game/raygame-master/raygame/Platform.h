#pragma once
#include "raylib.h"
#pragma warning(disable:4996)
struct GameObject {
	Model plat;
	Shader shader;
	int cameraLoc;
	bool enabled = false;
	float cameraPosition[3] = { 0,0,0 };
	GameObject() {

	}
	GameObject(const char* model) {
		shader = LoadShader("resources/shaders/glsl330/base.vs",
			"resources/shaders/glsl330/test.fs");
		plat = LoadModel(model);
		plat.material.shader = shader;
		enabled = true;
		cameraLoc = GetShaderLocation(plat.material.shader, "cameraPos");
	}
	void enablePlatform() {
		shader = LoadShader("resources/shaders/glsl330/base.vs",
			"resources/shaders/glsl330/test.fs");
		plat.material.shader = shader;
		enabled = true;
		cameraLoc = GetShaderLocation(plat.material.shader, "cameraPos");
	}
	void draw(Camera c) {
		cameraPosition[0] = c.position.x;
		cameraPosition[1] = c.position.y;
		cameraPosition[2] = c.position.z;
		SetShaderValue(plat.material.shader, cameraLoc, cameraPosition, 3);
		DrawModel(plat, {0,0,0}, 1, WHITE);

	}
};
