#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

SceneID scene1;
ObjectID startButton;
ObjectID Objects[8], rememberObject[8];
int stack[7][3] = { {1, 0, 0},{2, 0, 0}, {3, 0, 0}, {4, 0, 0}, {5, 0, 0}, {6, 0, 0}, {7, 0, 0} };
int a, b, c;
int linex[7] = { 160, 145, 130, 115, 100, 85, 70 }, liney[7] = { 350, 300, 250, 200, 150, 100, 50 }; //160 - 15 * i, 350 - 50 * i
TimerID timer1;
bool flag = false;

void Game_ready() {
	char image1[40];
	for (int i = 0; i < 7; i++) {
		sprintf(image1, "images/%d.png", i + 1);
		Objects[i] = createObject(image1);
		rememberObject[i] = Objects[i];
		locateObject(Objects[i], scene1, linex[i], liney[i]);
		showObject(Objects[i]);
	}
}

int game_check1(int k)//from 물체(움직일 물체)
{
	int i = 0;
	while (i < 7) {
		if (stack[i][k] != 0) {
			return (stack[i][k] - 1);
		}
		i++;
	}
}

int game_check2(int k)//to 물체 1칸 위 위치
{
	int i = 0;
	while (i < 7) {
		if (stack[i][k] != 0) {
			break;
		}
		i++;
	}
	return (i - 1);
}

void move_tower(int n, int from, int to, int temp) { // n개의 원판을 from에서 to로 temp를 이용해서 옮긴다. 최초 from->a, to->b, temp->c
	if (n == 1) {
		while (1) {
			if (from == a) {
				if (to == b) {
					locateObject(Objects[game_check1(0)], scene1, linex[game_check1(0)] + 400, liney[game_check2(1)]);

					int k = stack[game_check2(0) + 1][0];
					stack[game_check2(0) + 1][0] = stack[game_check2(1)][1];
					stack[game_check2(1)][1] = k;
					break;
				}
				else if (to == c) {
					locateObject(Objects[game_check1(0)], scene1, linex[game_check1(0)] + 800, liney[game_check2(2)]);

					int k = stack[game_check2(0) + 1][0];
					stack[game_check2(0) + 1][0] = stack[game_check2(2)][2];
					stack[game_check2(2)][2] = k;
					break;
				}
			}
			else if (from == b) {
				if (to == a) {
					locateObject(Objects[game_check1(1)], scene1, linex[game_check1(1)] - 400, liney[game_check2(0)]);

					int k = stack[game_check2(1) + 1][1];
					stack[game_check2(1) + 1][1] = stack[game_check2(0)][0];
					stack[game_check2(0)][0] = k;
					break;
				}
				else if (to == c) {
					locateObject(Objects[game_check1(1)], scene1, linex[game_check1(1)] + 400, liney[game_check2(2)]);

					int k = stack[game_check2(1) + 1][1];
					stack[game_check2(1) + 1][1] = stack[game_check2(2)][2];
					stack[game_check2(2)][2] = k;
					break;
				}
			}
			else if (from == c) {
				if (to == a) {
					locateObject(Objects[game_check1(2)], scene1, linex[game_check1(2)] - 800, liney[game_check2(0)]);

					int k = stack[game_check2(2) + 1][2];
					stack[game_check2(2) + 1][2] = stack[game_check2(0)][0];
					stack[game_check2(0)][0] = k;
					break;
				}
				else if (to == b) {
					locateObject(Objects[game_check1(2)], scene1, linex[game_check1(2)] - 400, liney[game_check2(1)]);

					int k = stack[game_check2(2) + 1][2];
					stack[game_check2(2) + 1][2] = stack[game_check2(1)][1];
					stack[game_check2(1)][1] = k;
					break;
				}
			}
		}
	}
	else {
		move_tower(n - 1, from, temp, to);
		while (1) {
			if (from == a) {
				if (to == b) {
					locateObject(Objects[game_check1(0)], scene1, linex[game_check1(0)] + 400, liney[game_check2(1)]);

					int k = stack[game_check2(0) + 1][0];
					stack[game_check2(0) + 1][0] = stack[game_check2(1)][1];
					stack[game_check2(1)][1] = k;
					break;
				}
				else if (to == c) {
					locateObject(Objects[game_check1(0)], scene1, linex[game_check1(0)] + 800, liney[game_check2(2)]);

					int k = stack[game_check2(0) + 1][0];
					stack[game_check2(0) + 1][0] = stack[game_check2(2)][2];
					stack[game_check2(2)][2] = k;
					break;
				}
			}
			else if (from == b) {
				if (to == a) {
					locateObject(Objects[game_check1(1)], scene1, linex[game_check1(1)] - 400, liney[game_check2(0)]);

					int k = stack[game_check2(1) + 1][1];
					stack[game_check2(1) + 1][1] = stack[game_check2(0)][0];
					stack[game_check2(0)][0] = k;
					break;
				}
				else if (to == c) {
					locateObject(Objects[game_check1(1)], scene1, linex[game_check1(1)] + 400, liney[game_check2(2)]);

					int k = stack[game_check2(1) + 1][1];
					stack[game_check2(1) + 1][1] = stack[game_check2(2)][2];
					stack[game_check2(2)][2] = k;
					break;
				}
			}
			else if (from == c) {
				if (to == a) {
					locateObject(Objects[game_check1(2)], scene1, linex[game_check1(2)] - 800, liney[game_check2(0)]);

					int k = stack[game_check2(2) + 1][2];
					stack[game_check2(2) + 1][2] = stack[game_check2(0)][0];
					stack[game_check2(0)][0] = k;
					break;
				}
				else if (to == b) {
					locateObject(Objects[game_check1(2)], scene1, linex[game_check1(2)] - 400, liney[game_check2(1)]);

					int k = stack[game_check2(2) + 1][2];
					stack[game_check2(2) + 1][2] = stack[game_check2(1)][1];
					stack[game_check2(1)][1] = k;
					break;
				}
			}
		}
		move_tower(n - 1, temp, to, from);
	}

}


void playGame() {
	hideObject(startButton);
	//flag = true;
	timer1 = createTimer(0.2f);
	startTimer(timer1);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		playGame();
	}
}

void timerCallback(TimerID timer) {
	if (timer == timer1) {
		//flag = true;
		move_tower(1, a, b, c);
		timer1 = createTimer(0.2f);
		startTimer(timer1);
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

	scene1 = createScene("하노이탑", "images/하노이탑 1.JPG");
	startButton = createObject("images/start.png", scene1, 570, 70, true);

	Game_ready();
	startGame(scene1);
}