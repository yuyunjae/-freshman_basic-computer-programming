#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

SceneID scene1, scene2;

ObjectID startButton, endButton, explainButton, explain;
ObjectID moleObjects[10],gameObjects[20];
int score, num;
bool flag = false;

TimerID timer1, timer2;


void startGame()
{
	enterScene(scene2);
	hideObject(startButton);
	hideObject(endButton);
	hideObject(explainButton);
	char image[100];
	for (int i = 0; i < 8; i++) {
		sprintf(image, "두더지-%d.png", i + 1);
		moleObjects[i] = createObject(image);
		gameObjects[i] = moleObjects[i]; //gameObjects[7}까지 사용함.
		locateObject(moleObjects[i], scene2, 100 + 100*i, 100);
		showObject(moleObjects[i]);
	}

	timer1 = createTimer(20.f);
	showTimer(timer1);
	startTimer(timer1);
	timer2 = createTimer(0.2f);
	startTimer(timer2);
}


void endGame(bool success)
{
	if (success) {
		showMessage("굿");
	}
	else {
		showMessage("게임 종료~!");
	}

	setObjectImage(startButton, "restart.png");
	locateObject(startButton, scene2, 590, 70);
	locateObject(endButton, scene2, 590, 20);
	locateObject(explainButton, scene2, 550, 120);
	showObject(startButton);
	showObject(endButton);
	showObject(explainButton);


	stopTimer(timer1);
}

void random_move() {
	int m, n, o, p;
	m = rand() % 8;
	for (int i = 0; i < 8; i++) {
		if (m == i) {
			n = rand() % 1180;
			o = rand() % 620;
			locateObject(moleObjects[i], scene2, n, o);
			showObject(moleObjects[i]);
		}
	}
	
}

int game_index(ObjectID a) {
	for (int i = 0; i < 16; i++) {
		if (gameObjects[i] == a) return i;
	}

	return -1;
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == endButton) {
		endGame();
	}
	else if (object == startButton) {
		startGame();
	}
	else if (object == explainButton) {
		showObject(explain);
	}
//	else if () {

//	}
}


void timerCallback(TimerID timer)
{
	random_move();
	if (timer == timer1) {
		endGame(false);
	}
	else if (timer == timer2) {
		random_move();
		timer2 = createTimer(0.2f);
		startTimer(timer2);	
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


int main()
{
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	scene1 = createScene("두더지 잡기", "배경-start.png");
	scene2 = createScene("두더지 잡기~", "땅.jpg");
	startButton = createObject("start.png", scene1, 590, 70, true);
	endButton = createObject("end.png", scene1, 590, 20, true);
	explainButton = createObject("설명버튼.png", scene1, 550, 120, true);
	srand((unsigned int)time(NULL));
	//santa = createObject("Images/santa.png", scene1, santaX, santaY, true);
	//playButton = createObject("Images/play.png", scene1, 610, 30, false);
	//showMessage("점수는 %d입니다", score);
	startGame(scene1);
}