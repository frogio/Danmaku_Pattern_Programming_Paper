#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <math.h>
#include "glut.h"
#include "Object.h"
#include "Pattern.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define PI 3.141592
#define VELOCITY 0.01
#define Z_POS -30

int width = 640;
int height = 480;
int texture_width, texture_height, nrChannels = 4;
unsigned char* _data;

void display();
void reshape(int w, int h);
void init();
void Update();

//CBullet bullet(0.f, 0.f, 1.f, 0.1f, 0, 0.875, 0  );
//CAimingBullet aming_bullet(0.f, 0.f, 1.f, 0.1f, 0, 20, 25, 0);
//CPlacedBullet placed_bullet(0.f, 0.f, 1.f, 0.1f, 0, 0, 0, 300, 180);
//CLinearPattern linear_pattern({ 0.f, 0.f }, 2.f, 0.12f);
//CCirclePattern circle_pattern({ 0.f, 0.f }, 30, 0.3f);
//CWindMillPattern windmill_parttern({ 0.f, 0.f }, 8, 0.2f, 0.03f);
//CCherryBlossomPattern cherry_blossom_pattern({ 0.f, 0.f }, 15, 2 * PI * 0.0035f);
COmiwatariPattern omiwatari_pattern(3.f, 0.5f, 0.5f);
//CBorderWvAndPar	border_wave_and_particle({0.f, 0.f}, 0.5f, 5, 1);
//CDanmakuKekkaiPart danmaku_kekkai_part1(0.1f, 0.003f, 15, 20, 20, 3, 700, 0.5f, 9);
//CDanmakuKekkaiPart danmaku_kekkai_part2(0.6f, 0.003f, 15, 20, 20, 3, 700, 0.5f, 9);
//CDanmakuKekkaiPart danmaku_kekkai_part3(0.35f, -0.003f, 17, 18, 20, 3, 700, 0.48f, 9);
//CDanmakuKekkaiPart danmaku_kekkai_part4(0.85f, -0.003f, 17, 18, 20, 3, 700, 0.48f, 9);
//
//CDanmakuKekkaiVer2 danmaku_kekkai_ver2(&danmaku_kekkai_part1, &danmaku_kekkai_part2,
//								&danmaku_kekkai_part3, &danmaku_kekkai_part4);

//CDanmakuKekkaiVer3Part danmaku_kekkai_ver3_part({-3.f, 1.f }, 15.f);

//Position _basePoint,
//float speed,
//int count, int interval)


//Position _basePoint,
//float angle, float angle_range,
//float waving_angle_range, float speed,
//int count, int interval, int cycle)

void main() {

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Danmaku");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(Update);					// 일정시간마다 계속 호출되는 함수를 정의.
	init();
	glutMainLoop();

}

void init() {

	glEnable(GL_DEPTH_TEST);

	_data = stbi_load("BlueCircleDanmaku.png", &texture_width, &texture_width, &nrChannels, 0);

	if (_data) {

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_width, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);

	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	stbi_image_free(_data);
}


void display() {
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	//bullet.Draw();
	//aming_bullet.Draw();
	//placed_bullet.Draw();

	//circle_pattern.DrawPattern();
	//windmill_parttern.DrawPattern();
	//cherry_blossom_pattern.DrawPattern();
	//aming_bullet.Draw();
	omiwatari_pattern.DrawPattern();
	//border_wave_and_particle.DrawPattern();
	//border_wave_and_particle.DrawPattern();

	glPointSize(10.f);
	glBegin(GL_POINTS);

	//glVertex3f(-20, -25, Z_POS);
	
	glEnd();
	glFlush();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {

	if (w == 0)
		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)w / h, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);

}
int prevTime = 0, curTime = 0;

void Update() {

	curTime = clock();

	if(curTime - prevTime >= 1.f / 60.f * 1000){
		prevTime = curTime;

		//cherry_blossom_pattern.UpdatePattern();
		//windmill_parttern.UpdatePattern();
		//circle_pattern.UpdatePattern();
		//aming_bullet.Update();
		omiwatari_pattern.UpdatePattern();
		//bullet.Update();
		//aming_bullet.Update();
		//placed_bullet.Update();
		//border_wave_and_particle.UpdatePattern();
		//border_wave_and_particle.UpdatePattern();
		glutPostRedisplay();
	}

}	// vector에 저장되어 있는 총알 객체들의 좌표를 Update한다. (glutIDLE함수로 지정되어 있음)