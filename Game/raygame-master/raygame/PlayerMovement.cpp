#include "PlayerMovement.h"
#include <math.h>
#include <vector>
#include <iostream>

float DotProduct(Vector3 v1, Vector3 v2) {
	return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}

float distance(Vector3 v1, Vector3 v2) {
	return sqrtf(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
}

Vector3 normalize(Vector3 v1) {
	float length = distance({ 0,0,0 }, v1);
	return { v1.x / length,v1.y / length,v1.z / length };
}

Vector3 operator-(Vector3 v1, Vector3 v2) {
	return { v1.x - v2.x, v1.y-v2.y, v1.z-v2.z };
}

Vector3 operator+(Vector3 v1, Vector3 v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

void sourceAccelerate(Player *p, Vector3 wishdir, float wishspeed, float accel) {
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
	p->velocity.z += accelspeed * wishdir.z;
}
void updatePlayer(Player* p, Vector2 mouseDelta) {
	p->previousPosition = p->camera.position;
	p->direction.x += mouseDelta.x / 15;
	p->direction.y += mouseDelta.y / 15;
	p->camera.position.x -= p->velocity.x*GetFrameTime();
	p->camera.position.y -= p->velocity.y*GetFrameTime();
	p->camera.position.z -= p->velocity.z*GetFrameTime();
	p->camera.target.x = p->camera.position.x + sin((p->direction.x / 360)*PI * 2);
	p->camera.target.y = p->camera.position.y + tan((p->direction.y / 360)*PI * 2);
	p->camera.target.z = p->camera.position.z + cos((p->direction.x / 360)*PI * 2);
}

bool playerDetectColision(Player* p, Model *m) {
	Ray ray;
	ray.position = { p->previousPosition.x, p->previousPosition.y, p->previousPosition.z };
	ray.direction = p->camera.position - p->previousPosition;
	RayHitInfo hit = GetCollisionRayModel(ray, m);
	if (hit.hit) {
		p->camera.position = hit.position - normalize(ray.direction);
		std::cout << hit.position.x << " " << hit.position.y << " " << hit.position.z << "\n";
		return true;
	}
	return false;
}

void acceleratePlayer(Player* p, Vector3 wishdir) {
	wishdir = { (float) (wishdir.x * cos((-p->direction.x / 360)*PI * 2) + wishdir.z * sin((p->direction.x / 360)*PI * 2)),
	0,
	(float) (wishdir.x * sin((-p->direction.x / 360)*PI * 2) + wishdir.z * cos((p->direction.x / 360)*PI * 2) )};
	sourceAccelerate(p, wishdir, 100, 3.5f); //TODO: make these values constants
										  //p->velocity.y += GetFrameTime();
	if (wishdir.x == 0 && wishdir.y == 0 && wishdir.z == 0) {
		p->velocity.x *= 0.8f;
		p->velocity.z *= 0.8f;
		if (distance({ 0,0,0 }, p->velocity) < 0.3f) {
			p->velocity = { 0,0,0 };
		}
	}
	else {
		p->velocity.x *= 0.925f;
		p->velocity.z *= 0.925f;
	}
	if (p->camera.position.y <= 0) {
		p->camera.position.y = 0;
	}
	p->velocity.y += GetFrameTime()*10;
}
void applyFriction(Player* p) {

}