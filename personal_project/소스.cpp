#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

SceneID scene1, scene2;

ObjectID startButton, endButton, explainButton, explain;
ObjectID moleObjects[8], animalObjects[8], gameObjects[16];
int click, mode = 0;
bool flag = false;
TimerID timer1, timer2, timer3;


void Game_ready() {
	char image1[40];
	char image2[40];
	for (int i = 0; i < 8; i++) {
		sprintf(image1, "images/두더지-%d.png", i + 1);
		moleObjects[i] = createObject(image1);
		gameObjects[i] = moleObjects[i]; //gameObjects[7}까지 사용함.(8개)
		locateObject(gameObjects[i], scene2, 100 + 100 * i, 100);
		showObject(gameObjects[i]);
	}
	for (int i = 8; i < 16; i++) {
		sprintf(image2, "images/동물-%d.png", i - 7);
		animalObjects[i - 8] = createObject(image2);
		gameObjects[i] = animalObjects[i - 8]; //gameObjects[8] ~ gameObjects[15]까지 사용함.(8개)
		locateObject(gameObjects[i], scene2, 100 + 100 * (i - 8), 300);
		showObject(gameObjects[i]);
	}
}


void startGame()
{
	enterScene(scene2);
	hideObject(startButton);
	hideObject(endButton);
	hideObject(explainButton);
	for (int i = 0; i < 16; i++) {
		hideObject(gameObjects[i]);
	}

	timer1 = createTimer(20.f);
	timer2 = createTimer(0.1f);
	timer3 = createTimer(1000.0f);
	showTimer(timer1);
	startTimer(timer1);
	startTimer(timer2);
	startTimer(timer3);
	flag = true;
}


void end_Game()
{
    showMessage("게임 종료~!\n 총 생존시간은 위의 타이머와 같습니다.");
	flag = false;
	setObjectImage(startButton, "images/restart.png");
	locateObject(startButton, scene2, 590, 70);
	locateObject(endButton, scene2, 590, 20);
	showObject(startButton);
	showObject(endButton);
	stopTimer(timer1);
	stopTimer(timer2);
	stopTimer(timer3);
	float a = getTimer(timer3);
	setTimer(timer1, 1000.f - a);
}

void random_move() {
	int m, n, o;
	m = rand() % 16;
	for (int i = 0; i < 16; i++) {
		if (m == i && flag == true) {
			n = rand() % 1180;
			o = rand() % 620;
			locateObject(gameObjects[i], scene2, n, o);
			showObject(gameObjects[i]);
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
	if (flag == true) {
		click = game_index(object);
		if (click < 8 && click >= 0) {
			increaseTimer(timer1, 0.5f);
		}
		else if (click >= 8) {
			decreaseTimer(timer1, 0.5f);
		}
	}
	else if (object == endButton) {
		endGame();
	}
	else if (object == startButton) {
		startGame();
	}
	else if (object == explainButton || object == explain) {
		if (mode % 2 == 0) {
			showObject(explain);
		}
		else if (mode % 2 == 1) {
			hideObject(explain);
		}
		mode++;
	}
}


void timerCallback(TimerID timer)
{
	random_move();
	if (timer == timer1) {
		end_Game();
	}
	else if (timer == timer2) {
		random_move();
		timer2 = createTimer(0.1f);
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

	scene1 = createScene("두더지 잡기", "images/배경-start.png");
	scene2 = createScene("두더지 잡기~", "images/땅.jpg");
	startButton = createObject("images/start.png", scene1, 590, 70, true);
	endButton = createObject("images/end.png", scene1, 590, 20, true);
	explainButton = createObject("images/설명버튼.png", scene1, 550, 120, true);
	explain = createObject("images/설명3.png", scene1, 376, 200, false);
	srand((unsigned int)time(NULL));
	Game_ready();
	startGame(scene1);
}