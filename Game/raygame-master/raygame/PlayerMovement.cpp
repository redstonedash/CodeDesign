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
Vector3 operator*(float f1, Vector3 v1) {
	return { v1.x * f1, v1.y * f1, v1.z * f1 };
}
Vector3 operator+(float f1, Vector3 v1) {
	return { v1.x + f1, v1.y + f1, v1.z + f1 };
}
Vector3 operator*(Vector3 v1, float f1) {
	return { v1.x * f1, v1.y * f1, v1.z * f1 };
}


void sourceAccelerate(Player *p, Vector3 wishdir, float wishspeed, float accel) {
	// q2 style
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

void sourceClipVelocity(Player* p, Vector3 normal, float overbounce) {
	float backoff = DotProduct(p->velocity, normal);
	if (backoff < 0) {
		backoff *= overbounce;
	} else {
		backoff /= overbounce;
	}
	Vector3 change = normal * backoff;
	p->velocity = p->velocity - change;

}

void updatePlayer(Player* p, Vector2 mouseDelta, std::vector<GameObject> collisionArray) {
	p->direction.x += mouseDelta.x / 15;
	p->direction.y += mouseDelta.y / 15;
	if (IsKeyDown(KEY_SPACE) && p->Grounded == true) {
		p->Grounded = false;
		p->velocity.y += 75;
	}
	p->camera.position.x += p->velocity.x*GetFrameTime();
	p->camera.position.y += p->velocity.y*GetFrameTime();
	p->camera.position.z += p->velocity.z*GetFrameTime();
	for (int i = 0; i < collisionArray.size(); i++) {
		if (playerDetectColision(p, &collisionArray.at(i))) {
			p->camera.position.x += p->velocity.x*GetFrameTime();
			p->camera.position.y += p->velocity.y*GetFrameTime();
			p->camera.position.z += p->velocity.z*GetFrameTime();
		}
	}
	p->camera.target.x = p->camera.position.x + sin((p->direction.x / 360)*PI * 2);
	p->camera.target.y = p->camera.position.y + tan((p->direction.y / 360)*PI * 2);
	p->camera.target.z = p->camera.position.z + cos((p->direction.x / 360)*PI * 2);
}

float clamp(float a, float b, float c) {
	return (a<b) ? (b) : ((a>c) ? (c) : (a));
}



Vector3 nearestPointOnTriangle(Vector3 point0, Vector3 point1, Vector3 point2, Vector3 target) {
	Vector3 edge0 = point1 - point0;
	Vector3 edge1 = point2 - point0;
	Vector3 v0 = point0 - target;

	float a = DotProduct(edge0, edge0);
	float b = DotProduct(edge1, edge0);
	float c = DotProduct(edge1, edge1);
	float d = DotProduct(v0, edge0);
	float e = DotProduct(v0, edge1);

	float det = a * c - b * b;
	float s = b * e - c * d;
	float t = b * d - a * e;

	if (s + t < det)
	{
		if (s < 0.0f)
		{
			if (t < 0.0f)
			{
				if (d < 0.0f)
				{
					s = clamp(-d / a, 0.0f, 1.0f);
					t = 0.0f;
				}
				else
				{
					s = 0.0f;
					t = clamp(-e / c, 0.0f, 1.0f);
				}
			}
			else
			{
				s = 0.0f;
				t = clamp(-e / c, 0.0f, 1.0f);
			}
		}
		else if (t < 0.0f)
		{
			s = clamp(-d / a, 0.0f, 1.0f);
			t = 0.0f;
		}
		else
		{
			float invDet = 1.0f / det;
			s *= invDet;
			t *= invDet;
		}
	}
	else
	{
		if (s < 0.0f)
		{
			float tmp0 = b + d;
			float tmp1 = c + e;
			if (tmp1 > tmp0)
			{
				float numer = tmp1 - tmp0;
				float denom = a - 2 * b + c;
				s = clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			}
			else
			{
				t = clamp(-e / c, 0.0f, 1.0f);
				s = 0.0f;
			}
		}
		else if (t < 0.0f)
		{
			if (a + d > b + e)
			{
				float numer = c + e - b - d;
				float denom = a - 2 * b + c;
				s = clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			}
			else
			{
				s = clamp(-e / c, 0.0f, 1.0f);
				t = 0.0f;
			}
		}
		else
		{
			float numer = c + e - b - d;
			float denom = a - 2 * b + c;
			s = clamp(numer / denom, 0.0f, 1.0f);
			t = 1.0f - s;
		}
	}
	return point0 + s * edge0 + t * edge1;
}

bool playerDetectColision(Player* p, GameObject *m) {
	bool negativeEncountered = false;
	Vector3 ClosestPoint;
	Vector3 ClosestPointNormal;
	Vector3 offset = { 0,-15,0 };
	offset = offset;
	float ClosestDistance = -1;
	for (int i = 0; i < m->plat.mesh.vertexCount*3; i++) {
		if (i % 3 == 2) {
			Ray ray;
			ray.position = { m->plat.mesh.vertices[i-2],m->plat.mesh.vertices[i-1],m->plat.mesh.vertices[i]};
			ray.direction = {-m->plat.mesh.normals[i - 2],-m->plat.mesh.normals[i - 1],-m->plat.mesh.normals[i]};

			if (DotProduct(normalize(p->camera.position + offset - ray.position), ray.direction) >= 0) {
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
		if (i % 9 == 8) { //this is called once we are on the last point of a triangle
			Vector3 point0 = { m->plat.mesh.vertices[i - 2] ,m->plat.mesh.vertices[i - 1] ,m->plat.mesh.vertices[i]    };
			Vector3 point1 = { m->plat.mesh.vertices[i - 5] ,m->plat.mesh.vertices[i - 4] ,m->plat.mesh.vertices[i - 3]};
			Vector3 point2 = { m->plat.mesh.vertices[i - 8] ,m->plat.mesh.vertices[i - 7] ,m->plat.mesh.vertices[i - 6]};
			
			//DrawLine3D(point0, point1, BLUE);
			//DrawLine3D(point1, point2, BLUE);
			//DrawLine3D(point0, point2, BLUE);

			Vector3 nearestPointOnTri = nearestPointOnTriangle(point0, point1, point2, p->camera.position+offset);
			Ray ray;
			ray.position = nearestPointOnTri;
			ray.direction = normalize(CrossProduct(point2 - point0, point2 - point1));
			//DrawCircle3D(ray.position, 0.5, { 0,1,0 }, 0, GREEN);
			if (ClosestDistance == -1 || ClosestDistance > distance(nearestPointOnTri, p->camera.position+offset)) {
				ClosestDistance = distance(nearestPointOnTri, p->camera.position + offset);
				ClosestPoint = nearestPointOnTri;
				ClosestPointNormal = ray.direction;
			}
		}
	}
	if (!negativeEncountered) {
		if (DotProduct({ 0,-1,0 }, ClosestPointNormal) > 0.5) {
			p->Grounded = true;
		} else {
			p->Grounded = false;
		}
		//std::cout << DotProduct({ 0,1,0 }, ClosestPointNormal) << "\n";
		p->camera.position = ClosestPoint-offset;
		sourceClipVelocity(p, ClosestPointNormal, 1);
		//DrawCircle3D(ClosestPoint, 1, { 1,0,0 }, 90, RED);
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
	if (p->Grounded) {
		sourceAccelerate(p, wishdir, 150, 3.5f); //TODO: make these values constants
	} else {
		sourceAccelerate(p, wishdir, 80, 5.0f); //TODO: make these values constants
	}
										  //p->velocity.y += GetFrameTime();
	if (wishdir.x == 0 && wishdir.y == 0 && wishdir.z == 0) {
		if (p->Grounded) {
			p->velocity.x *= 0.8f;
			p->velocity.z *= 0.8f;
			if (distance({ 0,0,0 }, { p->velocity.x,0,p->velocity.z }) < 0.3f) {
				p->velocity = { 0,p->velocity.y,0 };
			}
		}
	}
	else {
		if (p->Grounded) {
			p->velocity.x *= 0.925f;
			p->velocity.z *= 0.925f;
		}
	}
	p->velocity.y -= GetFrameTime()*130.0f;
}
void applyFriction(Player* p) {

}