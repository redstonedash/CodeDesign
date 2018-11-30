#include "PlayerMovement.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "Platform.h"

Vector3 CrossProduct(Vector3 v1, Vector3 v2) {
	return {
		(v1.y*v2.z) - (v1.z*v2.y) ,
		(v1.z*v2.x) - (v1.x*v2.z) ,
		(v1.x*v2.y) - (v1.y*v2.x) };
}

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

Vector3 operator*(Vector3 v1, int i1) {
	return { v1.x * i1, v1.y * i1, v1.z * i1};
}

Vector3 operator/(Vector3 v1, int i1) {
	return { v1.x / i1, v1.y / i1, v1.z / i1 };
}

Vector3 operator/(Vector3 v1, float f1) {
	return { v1.x / f1, v1.y / f1, v1.z / f1 };
}

Vector3 operator-(Vector3 v1, float f1) {
	return { v1.x - f1, v1.y - f1, v1.z - f1 };
}

Vector3 operator*(Vector3 v1, float f1) {
	return { v1.x * f1, v1.y * f1, v1.z * f1 };
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
void updatePlayer(Player* p, Vector2 mouseDelta, std::vector<GameObject> collisionArray) {
	p->direction.x += mouseDelta.x / 15;
	p->direction.y += mouseDelta.y / 15;
	p->camera.position.x += p->velocity.x*GetFrameTime();
	p->camera.position.y += p->velocity.y*GetFrameTime();
	p->camera.position.z += p->velocity.z*GetFrameTime();
	for (int i = 0; i < collisionArray.size(); i++) {
		playerDetectColision(p, &collisionArray.at(i).plat);
	}
	p->camera.target.x = p->camera.position.x + sin((p->direction.x / 360)*PI * 2);
	p->camera.target.y = p->camera.position.y + tan((p->direction.y / 360)*PI * 2);
	p->camera.target.z = p->camera.position.z + cos((p->direction.x / 360)*PI * 2);
}


bool playerDetectColision(Player* p, Model *m) {
	bool negativeEncountered = false;
	Vector3 ClosestPoint;
	float ClosestDistance = -1;
	for (int i = 0; i < m->mesh.vertexCount*3; i++) {
		if (i % 9 == 8) { // ind nearest point on tri
			Vector3 point1 = { m->mesh.vertices[i - 2] ,m->mesh.vertices[i - 1] ,m->mesh.vertices[i] };
			Vector3 point2 = { m->mesh.vertices[i - 5] ,m->mesh.vertices[i - 4] ,m->mesh.vertices[i - 3] };
			Vector3 point3 = { m->mesh.vertices[i - 8] ,m->mesh.vertices[i - 7] ,m->mesh.vertices[i - 6] };
			Vector3 avgPoint12 = (point1 + point2)/2;
			Vector3 avgPoint13 = (point1 + point3)/2;
			Vector3 avgPoint23 = (point2 + point3)/2;
			//DrawLine3D(point1, point2, BLUE);
			//DrawLine3D(point3, point2, BLUE);
			//DrawLine3D(point1, point3, BLUE);
			Ray ray;
			ray.direction = normalize(CrossProduct(point3 - point1, point3 - point2));
			ray.position = (point1 + point2 + point3) / 3;
			//DrawLine3D(ray.position, ray.position + ray.direction*(5),GREEN);

			Vector3 orgin = {5,-2,2.5};//p->camera.position;
			Vector3 v = orgin - ray.position;
			float scalarDist = DotProduct(v, normalize(ray.direction));
			Vector3 projectedPoint = orgin - ray.direction * scalarDist;
			float inBounds1 = DotProduct(normalize(ray.position - avgPoint12), (avgPoint12 - projectedPoint));
			float inBounds2 = DotProduct(normalize(ray.position - avgPoint13), (avgPoint13 - projectedPoint));
			float inBounds3 = DotProduct(normalize(ray.position - avgPoint23), (avgPoint23 - projectedPoint));
			DrawLine3D(projectedPoint, ray.position, RED);
			
			if (true) {
				std::cout << inBounds1 << " " << inBounds2 << " " << inBounds3 << "\n";
				std::cout << i << "\n";
				DrawLine3D(avgPoint12, avgPoint12 + (normalize(avgPoint12 - ray.position)*inBounds1), PURPLE);
				DrawLine3D(avgPoint13, avgPoint13 + (normalize(avgPoint13 - ray.position)*inBounds2), PURPLE);
				DrawLine3D(avgPoint23, avgPoint23 + (normalize(avgPoint23 - ray.position)*inBounds3), PURPLE);
				DrawLine3D(point1, point2, BLUE);
				DrawLine3D(point1, point3, BLUE);
				DrawLine3D(point3, point2, BLUE);
			}
		}
		if (i % 3 == 2) {
			Ray ray;
			ray.position = { m->mesh.vertices[i-2] ,m->mesh.vertices[i-1] ,m->mesh.vertices[i] };
			ray.direction = {- m->mesh.normals[i - 2] ,- m->mesh.normals[i - 1] ,- m->mesh.normals[i] };

			if (DotProduct(normalize(p->camera.position - ray.position), ray.direction) >= 0) {
				//DrawLine3D(ray.position, ray.position + ray.direction*(5), { 255,0,0,255 });
			}
			else {
				negativeEncountered = true;
				//break;
			}
		}
		Ray ray;
		ray.position = { 0,0,0 };
		ray.direction = { 0,100,0 };
	}
	if (!negativeEncountered) {
		//DrawCircle3D({ 0,0,0 }, 10, { 1,0,0 }, 90, RED);
	}
	/*
	Ray ray;
	Vector3 playerFootOffset = { 0,-15,0 };
	ray.position = p->camera.position-p->velocity + playerFootOffset + (normalize(p->camera.position + p->velocity));
	ray.direction = ray.position - p->camera.position;
	RayHitInfo hit = GetCollisionRayModel(ray, m);
	if (hit.hit) {
		if (hit.distance < distance(p->velocity,{0,0,0})) {
			p->camera.position = (hit.position - (normalize(ray.direction)))-playerFootOffset;
			std::cout << hit.position.x << " " << hit.position.y << " " << hit.position.z << "\n";
			return true;
		}
	}*/
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
		if (distance({ 0,0,0 }, { p->velocity.x,0,p->velocity.z }) < 0.3f) {
			p->velocity = { 0,p->velocity.y,0 };
		}
	}
	else {
		p->velocity.x *= 0.925f;
		p->velocity.z *= 0.925f;
	}
	//p->velocity.y -= GetFrameTime()*1.0f;
}
void applyFriction(Player* p) {

}