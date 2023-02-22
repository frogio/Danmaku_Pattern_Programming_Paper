#include "Pattern.h"


CPattern::CPattern() {}

void CPattern::UpdatePattern() {

	// ÃÑ¾Ë ¾÷µ¥ÀÌÆ®
	for (int i = 0; i < Bullets.size(); i++) {

		if (Bullets[i]->getIsAlive() == false){
			delete Bullets[i];
			Bullets.erase(Bullets.begin() + i);
		}
		else
			Bullets[i]->Update();

	}

	// ÃÑ¾Ë »ý¼º

}
void CPattern::DrawPattern() {

	for (int i = 0; i < Bullets.size(); i++)
		Bullets[i]->Draw();

}

CLinearPattern::CLinearPattern(Position _basePoint, float _bulletVelocity, float _bulletDir) :
	basePoint(_basePoint), bulletVelocity(_bulletVelocity), bulletDir(_bulletDir) {}

void CLinearPattern::UpdatePattern() {

	Bullets.push_back(new CBullet(basePoint.X, basePoint.Y, 1.f, bulletVelocity, 0, bulletDir, 0));
	CPattern::UpdatePattern();

}

void CLinearPattern::DrawPattern() {

	CPattern::DrawPattern();

}

CCirclePattern::CCirclePattern(Position _basePoint,int _bulletCount, float _bulletVelocity) :
	basePoint(_basePoint), bulletCount(_bulletCount), bulletVelocity(_bulletVelocity),Timer(180){	}


void CCirclePattern::UpdatePattern() {

	
	if(Timer == 180){
		Timer = 0;
		for (int i = 0; i < bulletCount; i++)
			Bullets.push_back(new CBullet(basePoint.X, basePoint.Y, 1.f, bulletVelocity, 0, (float)i / bulletCount, 0));
	}

	else Timer++;


	CPattern::UpdatePattern();
}
void CCirclePattern::DrawPattern() {
	CPattern::DrawPattern();
}

CWindMillPattern::CWindMillPattern(Position _basePoint, int _spiralCount, float _bulletVelocity, float _rotateVelocity) :
basePoint(_basePoint), spiralCount(_spiralCount), bulletVelocity(_bulletVelocity), rotateVelocity(_rotateVelocity), rotateAngle(0){}

void CWindMillPattern::UpdatePattern() {


	if (Timer == 20) {
		Timer = 0;
		for (int i = 0; i < spiralCount; i++)
			Bullets.push_back(new CBullet(basePoint.X, basePoint.Y, 1.f, bulletVelocity, 0, (float)i / spiralCount + rotateAngle, 0));
		
		rotateAngle += rotateVelocity;
		rotateAngle -= floor(rotateAngle);
	
	}
	else 
		Timer++;

	CPattern::UpdatePattern();
}
void CWindMillPattern::DrawPattern() {

	CPattern::DrawPattern();

}

CCherryBlossomPattern::CCherryBlossomPattern(Position _basePoint, float _blossomSize, float _radianDelta)
	: blossomSize(_blossomSize), radianDelta(_radianDelta), isMove(false),radian(0.f), basePoint(_basePoint) {}



void CCherryBlossomPattern::UpdatePattern() {

	float Xpos, Ypos, polarPosition;

	if (radian <= 2 * PI) {		// º¢²ÉÀ» ±×¸²
		isMove = false;
		polarPosition = CalculatePolarPosition(radian);

		Xpos = cosf(radian) * polarPosition;
		Ypos = sinf(radian) * polarPosition;

		Bullets.push_back(new CAimingBullet(basePoint.X + Xpos, basePoint.Y + Ypos, 1.f, 0.1f, 0, 0, 0, 0));

		radian += radianDelta;
	}
	else {						// º¢²ÉÀÌ ´Ù ±×·ÁÁ³À» °æ¿ì
		
		if (isMove == false) {
			isMove = true;

			for (int i = 0; i < Bullets.size(); i++)
				Bullets[i]->setVelocity(-0.1f);
		}
		// ÃÑ¾Ë ¾÷µ¥ÀÌÆ®
		
		CPattern::UpdatePattern();

	}


}

float CCherryBlossomPattern::CalculatePolarPosition(float theta){

	return blossomSize * cosf(1.3f + sinf(1 + cosf(5 * theta)));

}

COmiwatariPattern::COmiwatariPattern(float _waveSize, float _columnVelocity, float _waveVelocity) :
	WaveSize(_waveSize), ColumnVelocity(_columnVelocity), WaveVelocity(_waveVelocity), Timer(0),
	RadianSpeed(2 * PI * 0.005f), Radian(0), WaveBaseX(0), isEnd(false), isStart(false), Wave({0.f, MAX_Y}), Column({ 0.f, MAX_Y })
{

}

void COmiwatariPattern::UpdatePattern() {

		if (isStart == false) {
			WaveBaseX = 0;
			isStart = true;
			isEnd = false;
		}
		
		else if (isStart == true && isEnd == false) {
			Column.Y -= ColumnVelocity;
			Wave.Y -= WaveVelocity;
			Wave.X = WaveBaseX + WaveSize * sin(3.5 * Radian);
			Radian += RadianSpeed;
			// °è¼Ó °ªÀÌ ´©ÀûµÊ.

			// Åº¸· »ý¼º
			Bullets.push_back(new CBullet(Column.X, Column.Y, 1, 0.03f, 0, 0, 0));
			Bullets.push_back(new CBullet(Wave.X, Wave.Y, 1, 0.03f, 0, 0, 0));
		}
		if (Column.Y <= -MAX_Y && Wave.Y <= -MAX_Y) {
			isStart = false;
			isEnd = true;
		}

		//CPattern::UpdatePattern();
}

CBorderWvAndPar::CBorderWvAndPar(
	Position _basePoint,
	 float speed,
	int count, int interval)
	:
	basePoint(_basePoint),
	AngleDelta(0),
	RotateSpeed(0),
	ShotSpeed(speed),
	ShotCount(count),
	Interval(interval),
	Time(0)
{}


void CBorderWvAndPar::UpdatePattern() {

	if (Time % Interval == 0) {

		for (int i = 0; i < ShotCount; i++) {
			Bullets.push_back(new CBullet(basePoint.X, basePoint.Y, 1.f, ShotSpeed, 0.f, 
				(float)i / ShotCount + RotateSpeed ,
				0.f));
		}

		RotateSpeed += AngleDelta;
		RotateSpeed -= floor(RotateSpeed);
		AngleDelta += 0.0001;

	}
	Time = (Time + 1) % Interval;

	CPattern::UpdatePattern();
}

CDanmakuKekkaiPart::CDanmakuKekkaiPart(
	float orbit_angle, float orbit_angle_rate, float orbit_radius,
	int shot_time, int wait_time, int interval, int cycle,
	 float bullet_speed, int group_count)
	:
	OrbitAngle(orbit_angle), OrbitAngleRate(orbit_angle_rate), OrbitRadius(orbit_radius),
	ShotTime(shot_time), WaitTime(wait_time), Interval(interval), Cycle(cycle), Time(0),
	BulletSpeed(bullet_speed),
	GroupCount(group_count)
{
	float rad = OrbitAngle * PI * 2;
	ShotPos.X = cosf(rad) * OrbitRadius;
	ShotPos.Y = sinf(rad) * OrbitRadius;
}

void CDanmakuKekkaiPart::UpdatePattern() {

	float rad = 2 * PI * OrbitAngle;
	ShotPos.X = cosf(rad) * OrbitRadius;
	ShotPos.Y = sinf(rad) * OrbitRadius;

	OrbitAngle += OrbitAngleRate;
	OrbitAngle -= floor(OrbitAngle);

	if(Time % (Interval - 1)  == 0)
		Bullets.push_back(new CBullet(ShotPos.X, ShotPos.Y, 1, BulletSpeed * 0.1, 0, OrbitAngle, 0));
	
	int count = Time / (ShotTime + WaitTime);
	int time = Time % (ShotTime + WaitTime);
	float base_time = OrbitRadius / BulletSpeed;


	if (count < GroupCount) {
		if (time < ShotTime && time % Interval == 0) {
			Bullets.push_back(
				new CPlacedBullet(ShotPos.X, ShotPos.Y,
						1.f, BulletSpeed, 0,
						 OrbitAngle + 0.5f, 0,
						(int)(base_time * count / GroupCount), (int)(base_time + (ShotTime + WaitTime) * (GroupCount - count)))
			);
		}
	
	}
	Time = (Time + 1) % Cycle;

	CPattern::UpdatePattern();

}

void CDanmakuKekkaiVer1::UpdatePattern() {

	part1->UpdatePattern();
	part2->UpdatePattern();

}

void CDanmakuKekkaiVer1::DrawPattern() {

	part1->DrawPattern();
	part2->DrawPattern();

}

void CDanmakuKekkaiVer2::UpdatePattern() {
	part1->UpdatePattern();
	part2->UpdatePattern();
	part3->UpdatePattern();
	part4->UpdatePattern();

}
void CDanmakuKekkaiVer2::DrawPattern() {

	part1->DrawPattern();
	part2->DrawPattern();
	part3->DrawPattern();
	part4->DrawPattern();


}

CDanmakuKekkaiVer3Part::CDanmakuKekkaiVer3Part(Position _basePosition, float _KekkaiSize) :
basePoint(_basePosition), KekkaiSize(_KekkaiSize), radian(5 * PI), radianDelta(0.03f),
OrbitAngle(0.0f), OrbitAngleRate(0.003f), OrbitRadius(15)
{

}

void CDanmakuKekkaiVer3Part::UpdatePattern() {

	if(radian > 0 ){

		float rad = 2 * PI * OrbitAngle;

		ShotPos.X = cosf(rad) * OrbitRadius;
		ShotPos.Y = sinf(rad) * OrbitRadius;

		Bullets.push_back(new CBullet(ShotPos.X, ShotPos.Y, 1, 0.5f * 0.1, 0, OrbitAngle, 0));

		float polarPosition = CalculatePolarPosition(radian);

		float X = cosf(radian) * polarPosition + basePoint.X;
		float Y = sinf(radian) * polarPosition + basePoint.Y;

		Bullets.push_back(
			new CKekkaiVer3Bullet(ShotPos.X, ShotPos.Y, 1.f, 0.1f, 0, X, Y, 0, 0)
		/*new CBullet(X, Y, 1.f, 0.f, 0.f, 0.f, 0.f)*/
		/*new CAimingBullet(ShotPos.X, ShotPos.Y, 1.f, 0.1f, 0, X, Y, 0)*/);

		Bullets.push_back(new CBullet(X, Y, 1.f, 0.f, 0.f, 0.f, 0.f));

		radian -= radianDelta;
		OrbitAngle += OrbitAngleRate;
		OrbitAngle -= floor(OrbitAngle);

	}

	CPattern::UpdatePattern();

}
float CDanmakuKekkaiVer3Part::CalculatePolarPosition(float theta) {
	return KekkaiSize * (1 - 0.01f * theta * theta);

}