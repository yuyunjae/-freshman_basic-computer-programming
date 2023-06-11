#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1
#include <stdio.h>
#include <stdlib.h>
#include<bangtal.h>
#include<time.h>

SceneID scene1, scene2, scene3, scene4;
TimerID timer1;
ObjectID startButton, endButton, block[10][10], bomb, adv;
int linex[10];
int liney[10] = { 590, 530, 470, 410, 350, 290, 230, 170, 110, 50 };
clock_t start, end;

void Game_ready() {
	for (int k = 0; k < 10; k++) {
		linex[k] = 890 - (60 * k);
		liney[k] = 590 - (60 * k);
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			block[i][j] = createObject("images/블럭3.PNG");
			locateObject(block[i][j], scene2, linex[9 - i], liney[j]);
			showObject(block[i][j]);
		}
	}
}

void Game_start() {
	hideObject(startButton);
	hideObject(endButton);
	enterScene(scene2);
	timer1 = createTimer(30.0f);
	startTimer(timer1);
	showTimer(timer1);
	start = clock();
}


void ending() {
	end = clock();
	char time[100];
	sprintf(time, "걸린 시간은 %0.1lf 초 입니다.",(double)(end - start) / CLOCKS_PER_SEC);
	showMessage(time);
	setObjectImage(startButton, "images/restart.PNG");
	showObject(startButton);
	showObject(endButton);
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == endButton) {
		endGame();
	}
	else if (object == startButton) {
		Game_start();
	}

}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		enterScene(scene3);
		locateObject(startButton, scene3, 500, 250);
		locateObject(endButton, scene3, 650, 250);
		ending();
	}
}

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}

	return object;
}

int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("지뢰 찾기!", "images/지뢰찾기1.PNG");
	scene2 = createScene("게임화면", "images/게임화면1.JPG");
	scene3 = createScene("실패..", "images/실패.JPG");
	scene4 = createScene("성공..", "images/성공.JPG");
	startButton = createObject("images/start.PNG", scene1, 600, 100, true);
	endButton = createObject("images/end.PNG", scene1, 600, 50, true);
	bomb = createObject("images/폭탄이요~.JPG", scene2, 80, 530, true);
	adv = createObject("images/광고1.PNG", scene2, 1020, 100, true);
	Game_ready();
	startGame(scene1);
}