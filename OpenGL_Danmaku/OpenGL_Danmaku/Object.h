#include <cmath>
#include "glut.h"

//class CPattern;

#ifndef __OBJECT_H__
#define __OBJECT_H__

#define PI 3.141592

#define MAX_X 43
#define MAX_Y 32

class CVertex {

private:
	float v_x;
	float v_y;

public:

	CVertex() {}

	CVertex(float x, float y) {
		v_x = x;
		v_y = y;
	}
	
	void setX(float _v_x) { v_x = _v_x; }
	void setY(float _v_y) { v_y = _v_y; }

	float getX() { return v_x; }
	float getY() { return v_y; }

};

class CObject {
protected:
	float X;
	float Y;
	float Size;
	CVertex Vertex[4];
	
public:
	CObject(float _X, float _Y, float _Size);

	float getX() { return X; }
	float getY() { return Y; }
	float getSize() { return Size; }
	
	float setX(float _X) { X = _X; }
	float setY(float _Y) { Y = _Y; }
	virtual void Draw();
};

class CBullet : public CObject {
protected :
	float velocity;
	float acc;
	float direction;
	float angularVel;
	bool isAlive;

public:

	CBullet(float X, float Y, float Size, float _velocity, float _acc , float _dir, float _angularVel);
	virtual void Update();
	bool getIsAlive() { return isAlive; }

	void setVelocity(float _velocity) { velocity = _velocity; }
	void setDirection(float _dir) { direction = _dir; }
	float getDirection() { return direction; }
	float getVelocityX() {
		float rad = 2 * PI * direction;
		return velocity * cosf(rad);
	}
	float getVelocityY() { 
		float rad = 2 * PI * direction;
		return velocity * sinf(rad); }
};

class CAimingBullet : public CBullet 
{
protected:
	float v_x, v_y;						// ¿Ãµø ∫§≈Õ
	float norm;
	float velX, velY;

public:
	CAimingBullet(float X, float Y, float Size, float _velocity, float _acc, float X_, float Y_, float _angularVel);
	void Update();

};

class CPlacedBullet : public CBullet {
private :

	float initialVelocity;
	int MoveTime;
	int StopTime;
	int Timer;

public:
	CPlacedBullet(float _X, float _Y, float Size, float _velocity, float _acc, float _dir, float _angularVel
				,int _MoveTime, int _StopTime);

	void Update();
};

class CKekkaiVer3Bullet : public CAimingBullet {
private:
	float direction2;
	bool isMove;

public:
	CKekkaiVer3Bullet(float X, float Y, float Size, float _velocity, float _acc, float X_, float Y_, float _angularVel, float _direction2);

	void Update();
	bool isArrive();

};

#endif