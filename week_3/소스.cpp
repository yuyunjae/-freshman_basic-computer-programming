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

//찾았는지, 찾지 못했는지를 저장하는 논리형 변수 배열을 선언한다.
//찾았는지(true), 찾지 못했는지(false)
bool checked[7];

/*자료형 배열이름[배열의 크기];
자료형 배열이름[배열의 크기] = {값...};
int size[3] = { 1, 2, 3 };
size[0] = 1, size[1] = 2, size[2] = 3;*/
bool checkin(int x, int y, int cx, int cy, int r) {
	return (x > cx - r && x<cx + r && y>cy - r && y < cy + r);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == problem) {
		//wrong을 true로 초기화 한다.
		bool wrong = true;
		//반복문을 사용한다.
		for (int i = 0; i < 7; i++) {
			//(i+1)번째 틀린그림을 체크한다.
			if ((checked[i] == false) && (checkin(x, y, leftx[i], Y[i], radius[i]) || checkin(x, y, rightx[i], Y[i], radius[i]))) {
				showObject(left[i]);
				showObject(right[i]);
			    //틀린그림을 클릭한 경우
				checked[i] = true;
				wrong = false;
			}
		} 
		// 틀린그림 클릭 x 이면 게임 종료
		if (wrong == true) {
			endGame();
		}
		else {
			//모두찾았는가를 저장하는 변수 선언
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
	scene1 = createScene("틀린그림찾기", "problem.png");
	problem = createObject("problem", "problem.png");
	locateObject(problem, scene1, 0, 0);
	showObject(problem);

	for (int i = 0; i < 7; i++) {
		left[i] = createObject("체크 마크", "check.png");
		locateObject(left[i], scene1, leftx[i] - 25, Y[i] - 25);
		right[i] = createObject("체크 마크", "check.png");
		locateObject(right[i], scene1, rightx[i] - 25, Y[i] - 25);
	}

	showMessage("좌우에 틀린 곳을 찾아보세요.");

	startGame(scene1);
}