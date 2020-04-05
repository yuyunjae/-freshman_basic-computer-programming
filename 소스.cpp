#include<Bangtal.h>
#include<time.h>
#include<stdio.h>
#pragma comment(lib,"Bangtal.lib")

SceneID scene1, scene2;
ObjectID image1[3][3];
ObjectID startButton, endButton;
clock_t start, end;
ObjectID blank;
int imagex[3][3] = { { 400, 600, 800 },{ 400, 600, 800 },{ 400, 600, 800 } };
int imagey[3][3] = { { 520, 520, 520 }, { 320, 320, 320 }, { 120, 120, 120 } };
bool checked[3][3];
int x1, y1;

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(name, image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return object;
}

void ending() {
    end = clock();
    printf("Time:%lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    setObjectImage(startButton, "restart.png");
    showObject(startButton);
    showObject(endButton);
}


void changeObjectx(int x, int y) {
    int xx = x;
    x = imagex[2][2];
    imagex[2][2] = xx;
}

void changeObjecty(int x, int y){
    int yy = y;
    y = imagey[2][2];
    imagey[2][2] = yy;
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((object == image1[i][j]) && ((j < 2) && ((image1[i][j + 1] == image1[2][2])) || ((j > 0) && (image1[i][j - 1] == image1[2][2])) || ((i < 2) && (image1[i + 1][j] == image1[2][2])) || ((i > 0) && (image1[i - 1][j] == image1[2][2])))) {
                changeObjectx(imagex[i][j], imagey[i][j]);
                changeObjecty(imagex[i][j], imagey[i][j]);
                x1 = i; y1 = j;
            }
            locateObject(image1[x1][y1], scene2, imagex[x1][y1], imagey[x1][y1]);
            locateObject(image1[2][2], scene2, imagex[2][2], imagey[2][2]);
        }
    }



    if (object == endButton) {
        endGame();
    }
    else if (object == startButton) {
        hideObject(startButton);
        hideObject(endButton);
        enterScene(scene2);
        blank = image1[2][2];
        start = clock();
    }
}

int main() {
    scene1 = createScene("퍼즐 판1", "image1.png");
    scene2 = createScene("퍼즐 판2", "image1.png");
    startButton = createObject("시작 버튼", "start.png", scene1, 590, 70, true);
    endButton = createObject("종료 버튼", "end.png", scene1, 590, 20, true);
    image1[0][0] = createObject("이미지1", "image1_01.png", scene2, imagex[0][0], imagey[0][0], true);
    image1[0][1] = createObject("이미지2", "image1_02.png", scene2, imagex[0][1], imagey[0][1], true);
    image1[0][2] = createObject("이미지3", "image1_03.png", scene2, imagex[0][2], imagey[0][2], true);
    image1[1][0] = createObject("이미지4", "image1_04.png", scene2, imagex[1][0], imagey[1][0], true);
    image1[1][1] = createObject("이미지5", "image1_05.png", scene2, imagex[1][1], imagey[1][1], true);
    image1[1][2] = createObject("이미지6", "image1_06.png", scene2, imagex[1][2], imagey[1][2], true);
    image1[2][0] = createObject("이미지7", "image1_07.png", scene2, imagex[2][0], imagey[2][0], true);
    image1[2][1] = createObject("이미지8", "image1_08.png", scene2, imagex[2][1], imagey[2][1], true);
    image1[2][2] = createObject("이미지9", "흰색_1.png", scene2, imagex[2][2], imagey[2][2], true);
    scaleObject(image1[2][2], 0.492f);
    setMouseCallback(mouseCallback);

    startGame(scene1);
}