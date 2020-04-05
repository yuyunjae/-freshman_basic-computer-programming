#include<Bangtal.h>
#pragma comment(lib, "Bangtal.lib")


SceneID scene1;
ObjectID problem;
ObjectID left[7];
ObjectID right[7];
//left1, left2, left3, left4, left5, left6, left7;
// right1, right2, right3, right4, right5, right6, right7;
int leftx[7] = { 546, 77, 361, 379, 39, 570, 298 };
int rightx[7] = { 1164, 695, 979, 997, 657, 1188, 916 };
int Y[7] = { 542,499,430,106,203,369,65 };
int radius[7] = { 54,17,16,27,36,35,13 };

//ã�Ҵ���, ã�� ���ߴ����� �����ϴ� ���� ���� �迭�� �����Ѵ�.
//ã�Ҵ���(true), ã�� ���ߴ���(false)
bool checked[7];

/*�ڷ��� �迭�̸�[�迭�� ũ��];
�ڷ��� �迭�̸�[�迭�� ũ��] = {��...};
int size[3] = { 1, 2, 3 };
size[0] = 1, size[1] = 2, size[2] = 3;*/
bool checkin(int x, int y, int cx, int cy, int r) {
	return (x > cx - r && x<cx + r && y>cy - r && y < cy + r);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == problem) {
		//wrong�� true�� �ʱ�ȭ �Ѵ�.
		bool wrong = true;
		//�ݺ����� ����Ѵ�.
		for (int i = 0; i < 7; i++) {
			//(i+1)��° Ʋ���׸��� üũ�Ѵ�.
			if ((checked[i] == false) && (checkin(x, y, leftx[i], Y[i], radius[i]) || checkin(x, y, rightx[i], Y[i], radius[i]))) {
				showObject(left[i]);
				showObject(right[i]);
			    //Ʋ���׸��� Ŭ���� ���
				checked[i] = true;
				wrong = false;
			}
		} 
		// Ʋ���׸� Ŭ�� x �̸� ���� ����
		if (wrong == true) {
			endGame();
		}
		else {
			//���ã�Ҵ°��� �����ϴ� ���� ����
			bool completed = true;
			for (int i = 0; i < 7; i++) {
				if (checked[i] == false) {
					completed = false;
				}
			}
			if (completed == true) {
				endGame();
			}
		}
	}
}

int main() {
	setMouseCallback(mouseCallback);
	scene1 = createScene("Ʋ���׸�ã��", "problem.png");
	problem = createObject("problem", "problem.png");
	locateObject(problem, scene1, 0, 0);
	showObject(problem);

	for (int i = 0; i < 7; i++) {
		left[i] = createObject("üũ ��ũ", "check.png");
		locateObject(left[i], scene1, leftx[i] - 25, Y[i] - 25);
		right[i] = createObject("üũ ��ũ", "check.png");
		locateObject(right[i], scene1, rightx[i] - 25, Y[i] - 25);
	}

	showMessage("�¿쿡 Ʋ�� ���� ã�ƺ�����.");

	startGame(scene1);
}