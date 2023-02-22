#pragma once
#include <deque>
#include "Object.h"

#ifndef __PATTERN_H__
#define __PATTERN_H__

using namespace std;




typedef struct Position {
	float X;
	float Y;
} Position;

class CPattern {
protected:
	deque<CBullet *> Bullets;

public:

	CPattern();

	virtual void UpdatePattern();
	virtual void DrawPattern();

};

class CLinearPattern : CPattern{

private:
	Position basePoint;
	float bulletVelocity;
	float bulletDir;

public:

	CLinearPattern(Position _basePoint, float _bulletVelocity, float _bulletDir);
	void UpdatePattern();
	void DrawPattern();

};

class CCirclePattern : CPattern {
private:
	Position basePoint;
	int bulletCount;
	float bulletVelocity;
	int Timer;

public:
	CCirclePattern(Position basePoint,int _bulletCount, float _bulletVelocity);
	void UpdatePattern();
	void DrawPattern();
};


class CWindMillPattern : CPattern {
private:
	Position basePoint;
	int spiralCount;
	float bulletVelocity;
	const float rotateVelocity;
	float rotateAngle;
	int Timer;

public:
	CWindMillPattern(Position _basePoint, int _spiralCount, float _bulletVelocity, float _rotateVelocity);
	void UpdatePattern();
	void DrawPattern();

};


class CCherryBlossomPattern : public CPattern {
private:

	Position basePoint;
	float blossomSize;
	const float radianDelta;	// 라디안 변화량.
	float radian;				// 탄의 방향
	bool isMove;					// 모양 완성 여부

public:

	CCherryBlossomPattern(Position _basePoint,
		float _blossomSize,
		float _radianDelta
		);

	void UpdatePattern();
	float CalculatePolarPosition(float theta);
};


class COmiwatariPattern : public CPattern {

private:
	Position Wave;
	Position Column;

	const float ColumnVelocity;
	const float WaveVelocity;
	const float WaveSize;
	float WaveBaseX;
	
	float RadianSpeed;
	float Radian;

	int Timer;

	bool isEnd;			// 탄막 기둥이 끝에 도달했는가?
	bool isStart;		// 탄막 기둥이 시작되는가?

public:
	COmiwatariPattern(float _waveSize, float _columnVelocity, float _waveVelocity);
	void UpdatePattern();
};

class CBorderWvAndPar : public CPattern{
private :

	Position basePoint;
	float ShotSpeed;
	float AngleDelta;
	float RotateSpeed;
	int ShotCount;
	int Interval;
	int Time;

public:
	CBorderWvAndPar(
		Position _basePoint,
		 float speed,
		int count, int interval);

	void UpdatePattern();
	
};

class CDanmakuKekkaiPart : public CPattern {
private:
	Position ShotPos;

	float OrbitAngle;
	float OrbitAngleRate;
	float OrbitRadius;
	int ShotTime;
	int WaitTime;
	int Interval;
	int Cycle;
	int Time;
	float BulletSpeed;
	int GroupCount;

public:
	CDanmakuKekkaiPart(
		float orbit_angle, float orbit_angle_rate, float orbit_radius,
		int shot_time, int wait_time, int interval, int cycle,
		float bullet_speed, int group_count);

	void UpdatePattern();
};

class CDanmakuKekkaiVer1 : public CPattern {

private : 
	CDanmakuKekkaiPart* part1;
	CDanmakuKekkaiPart* part2;

public:

	CDanmakuKekkaiVer1(CDanmakuKekkaiPart* _part1, CDanmakuKekkaiPart* _part2) : part1(_part1), part2(_part2) {}
	void UpdatePattern();
	void DrawPattern();
};

class CDanmakuKekkaiVer2 : public CPattern {
private:
	CDanmakuKekkaiPart* part1;
	CDanmakuKekkaiPart* part2;
	CDanmakuKekkaiPart* part3;
	CDanmakuKekkaiPart* part4;

public:

	CDanmakuKekkaiVer2(CDanmakuKekkaiPart* _part1, CDanmakuKekkaiPart* _part2, CDanmakuKekkaiPart* _part3, CDanmakuKekkaiPart* _part4) : 
		part1(_part1), part2(_part2), part3(_part3), part4(_part4) {}
	
	void UpdatePattern();
	void DrawPattern();

};

class CDanmakuKekkaiVer3Part : public CPattern{
private:
	Position basePoint;
	Position ShotPos;

	float KekkaiSize;
	const float radianDelta;	// 라디안 변화량.
	float radian;				// 탄의 방향
	bool isMove;					// 모양 완성 여부

	float OrbitAngle;
	float OrbitAngleRate;
	float OrbitRadius;

public:

	CDanmakuKekkaiVer3Part(Position _basePosition, float _KekkaiSize);
	void UpdatePattern();
	float CalculatePolarPosition(float theta);

};

#endif