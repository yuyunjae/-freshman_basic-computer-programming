#include <bangtal.h>

SceneID scene1, scene2;

ObjectID startButton, endButton, mole1, mole2, mole3, mole4;
ObjectID santa;

int santaX = 0, santaY = 500;

TimerID timer1;


void startGame()
{
	enterScene(scene2);
	hideObject(startButton);
	hideObject(endButton);

	timer1 = createTimer(20.f);
	showTimer(timer1);
	startTimer(timer1);
}


// ���� ���Ḧ ó���� �Լ��� �����Ѵ�.
// ������ ��쿡 success�� true�� �����Ѵ�. ���д� false.
void endGame(bool success)
{
	if (success) {
		showMessage("���� ��� ����~~~");
	}
	else {
		showMessage("��, ���� ��� ����!!!");
	}



	setObjectImage(startButton, "Images/restart.png");
	showObject(startButton);
	showObject(endButton);

	santaX = 0;
	locateObject(santa, scene1, santaX, santaY);

	stopTimer(timer1);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == endButton) {
		endGame();
	}
	else if (object == startButton) {
		startGame();

	}
	
}

void timerCallback(TimerID timer)
{
	if (timer == timer1) {
		endGame(false);
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

	scene1 = createScene("�δ��� ���", "���-start.png");
	scene2 = createScene("�δ��� ���~", "��.jpg");
	startButton = createObject("start.png", scene1, 590, 70, true);
	endButton = createObject("end.png", scene1, 590, 20, true);
	mole1 = createObject("end.png", scene1, 590, 20, true);
	endButton = createObject("end.png", scene1, 590, 20, true);
	endButton = createObject("end.png", scene1, 590, 20, true);
	endButton = createObject("end.png", scene1, 590, 20, true);
	endButton = createObject("end.png", scene1, 590, 20, true);

	//santa = createObject("Images/santa.png", scene1, santaX, santaY, true);
	//playButton = createObject("Images/play.png", scene1, 610, 30, false);

	startGame(scene1);
}