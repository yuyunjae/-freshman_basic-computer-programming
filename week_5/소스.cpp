#include<Bangtal.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#pragma comment(lib,"Bangtal.lib")

SceneID scene1, scene2;
ObjectID startButton, endButton;
clock_t start, end;
ObjectID image01, image02, image03, image04, image05, image06, image07, image08, image09, blank;
ObjectID image1[3][3] = { {image01, image02, image03},{image04, image05, image06},{image07,image08,blank} };
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

void Swap(ObjectID a, ObjectID b)
{
    ObjectID r = a;
    a = b;
    b = r;
}

void SwapX(int x1, int x2) {
    int q = x1;
    x1 = x2;
    x2 = q;
}

void SwapY(int y1, int y2) {
    int p = y1;
    y1 = y2;
    y2 = p;
}

void random()
{
    int num[3][3];
    srand(time(NULL));

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            num[i][j] = (rand() % 9) + 1;
            //사용법을 모르겠음,
        }
    }
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    if (object == endButton) {
        endGame();
    }
    else if (object == startButton) {
        hideObject(startButton);
        hideObject(endButton);
        enterScene(scene2);
        blank = image1[2][2];
        start = clock();
        // random();
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((object == image1[i][j]) && (object != blank)) {
                if ((i < 2) && (image1[i + 1][j] == blank)) {
                    Swap(image1[i][j], imagex[i + 1][j]);
                    SwapX(imagex[i][j], imagex[i + 1][j]);
                    SwapY(imagey[i][j], imagey[i + 1][j]);
                    locateObject(image1[i][j], scene2, imagex[i + 1][j], imagey[i + 1][j]);
                    locateObject(image1[i + 1][j], scene2, imagex[i][j], imagey[i][j]);
                    blank = image1[i][j];
                }

                else if ((i > 0) && (image1[i - 1][j] == blank)) {
                    Swap(image1[i][j], imagey[i - 1][j]);
                    SwapX(imagex[i][j], imagex[i - 1][j]);
                    SwapY(imagey[i][j], imagey[i - 1][j]);
                    locateObject(image1[i][j], scene2, imagex[i - 1][j], imagey[i - 1][j]);
                    locateObject(image1[i - 1][j], scene2, imagex[i][j], imagey[i][j]);
                    blank = image1[i][j];
                }

                else if ((j < 2) && (image1[i][j + 1] == blank)){
                    Swap(image1[i][j], image1[i][j + 1]);
                    SwapX(imagex[i][j], imagex[i][j + 1]);
                    SwapY(imagey[i][j], imagey[i][j + 1]);
                    locateObject(image1[i][j], scene2, imagex[i][j + 1], imagey[i][j + 1]);
                    locateObject(image1[i][j + 1], scene2, imagex[i][j], imagey[i][j]);
                    blank = image1[i][j];

                }

                else if ((j > 0) && (image1[i][j - 1] == blank)) {
                    Swap(image1[i][j], imagex[i][j - 1]);
                    SwapX(imagex[i][j], imagex[i][j - 1]);
                    SwapY(imagey[i][j], imagey[i][j - 1]);
                    locateObject(image1[i][j], scene2, imagex[i][j - 1], imagey[i][j - 1]);
                    locateObject(image1[i][j - 1], scene2, imagex[i][j], imagey[i][j]);
                    blank = image1[i][j];
                }

            }

        }

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