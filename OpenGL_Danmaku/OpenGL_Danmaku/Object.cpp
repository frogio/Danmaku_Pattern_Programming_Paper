#include <stdio.h>
#include "Object.h"


CObject::CObject(float _X, float _Y, float _Size):
X(_X), Y(_Y), Size(_Size)
{
	/*
	X = _X;
	Y = _Y;
	Size = _Size;*/

	Vertex[0].setX(X - Size);
	Vertex[0].setY(Y + Size);

	Vertex[1].setX(X - Size);
	Vertex[1].setY(Y - Size);

	Vertex[2].setX(X + Size);
	Vertex[2].setY(Y - Size);

	Vertex[3].setX(X + Size);
	Vertex[3].setY(Y + Size);

	// 버텍스 좌표는 반드시 반시계 방향으로 해야 오류가 발생하지 않는다.
}

void CObject::Draw() {
	//glPointSize(20.f);


	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);

	glVertex3f(X + Vertex[0].getX(),
		Y + Vertex[0].getY(),
		-30.f);
	glTexCoord2f(0, 1);

	//system("pause");
	glVertex3f(X + Vertex[1].getX(),
		Y + Vertex[1].getY(),
		-30.f);
	glTexCoord2f(1, 1);

	//system("pause");
	glVertex3f(X + Vertex[2].getX(),
		Y + Vertex[2].getY(),
		-30.f);
	glTexCoord2f(1, 0);

	//system("pause");
	glVertex3f(X + Vertex[3].getX(),
		Y + Vertex[3].getY(),
		-30.f);
	glTexCoord2f(0, 0);
	
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

CBullet::CBullet(float X, float Y, float Size, float _velocity, float _acc, float _dir, float _angularVel) :
	CObject(X, Y, Size), velocity(_velocity), acc(_acc), direction(_dir), angularVel(_angularVel), isAlive(true) {}

void CBullet::Update() {
	
	float rad = 2 * PI * direction;

	X += velocity * cosf(rad);
	Y += velocity * sinf(rad);

	velocity += acc;
	direction += angularVel;

	//printf("CBullet\n");

	if (abs(X) >= MAX_X + Size || abs(Y) >= MAX_Y + Size)
		isAlive = false;

}

CAimingBullet::CAimingBullet(float X, float Y, float Size, float _velocity, float _acc, float X_, float Y_, float _angularVel):
	CBullet(X,Y,Size,_velocity, _acc, 0, _angularVel) {

	v_x = X - X_;
	v_y = Y - Y_;
	norm = 1 / sqrt(v_x * v_x + v_y * v_y);

}

void CAimingBullet::Update() {

	float x = norm * v_x * -velocity;
	float y = norm * v_y * -velocity;

	X += x;
	Y += y;

	velocity += acc;
	direction += angularVel;

	if (abs(X) >= MAX_X || abs(Y) >= MAX_Y)
		isAlive = false;
	
}


CPlacedBullet::CPlacedBullet(float _X, float _Y, float Size, float _velocity, float _acc, float _dir, float _angularVel
	, int _MoveTime, int _StopTime) :
	CBullet(_X, _Y, Size, _velocity, _acc, _dir, _angularVel)
	,MoveTime(_MoveTime), StopTime(_StopTime),Timer(0), initialVelocity(_velocity)
{ }

void CPlacedBullet::Update() {

	if (Timer == MoveTime)
		velocity = 0;

	if (Timer == MoveTime + StopTime)
		velocity = initialVelocity;

	Timer++;
	
	float rad = 2 * PI * direction;

	X += velocity * cosf(rad);
	Y += velocity * sinf(rad);

	if (abs(X) >= MAX_X + 20 || abs(Y) >= MAX_Y  + 20)
		isAlive = false;


}
CKekkaiVer3Bullet::CKekkaiVer3Bullet(float X, float Y, float Size, float _velocity, float _acc, float X_, float Y_, float _angularVel,float _direction2):
CAimingBullet(X, Y, Size, _velocity, _acc, X_, Y_, _angularVel ),
direction2(_direction2), isMove(false)
{
	//printf("ShotPos X, Y : %f, %f\n", X, Y);
	//printf("DestPos X, Y : %f, %f\n", X_, Y_);
	printf("vectorSize X, Y : %f, %f\n", X - X_, Y - Y_);

}

void CKekkaiVer3Bullet::Update() {

	if (isArrive() == false) {
		//printf("length : %f\n", 1 / norm);
		
		CAimingBullet::Update();
	}

}
bool CKekkaiVer3Bullet::isArrive() {

	return 1 / norm <= 0;

}