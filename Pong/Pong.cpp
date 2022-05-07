#include <Windows.h>//��� Sleep()
#include <iostream>//��� ������ �� �����
#include <conio.h>//��� ������
using namespace std;
const int sizemapy = 50;//������ �����
const int sizemapx = 100;
char map[sizemapy][sizemapx];

short int pongx = sizemapx / 2;//���������� ���� X
short int pongy = sizemapy / 2;//���������� ���� Y

bool flag_win = true;

int pongspeedx = 1;//��������. ���������� �� ������
int pongspeedy = 1;

int player1y = sizemapy / 2;//���������� Y ������� ��� ������
int player2y = sizemapy / 2;

int points1 = 0;//���� �������
int points2 = 0;

int pointsforend = 5;//������� ����� ����� ���� ��������

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//��������� ������ ��� ��������� ��������� �������
void display() {
    short int dispx = 0;//��������������� ����������
    short int dispy = 0;
    system("cls");//������ ������
    while (dispy < sizemapy) {
        while (dispx < sizemapx) {
            if (dispx == 0 || dispy == 0 || dispx == sizemapx - 1 || dispy == sizemapy - 1) {
                SetConsoleCursorPosition(hStdOut, { dispx, dispy });//��������� ��������� ������� �������
                cout << "#";//���� ����
            }
            if (dispx == pongx && dispy == pongy) {
                SetConsoleCursorPosition(hStdOut, { dispx, dispy });
                cout << "0";//���
            }
            if (map[dispy][dispx] > 0) {
                SetConsoleCursorPosition(hStdOut, { dispx, dispy });
                cout << "|";//������ ������
            }
            dispx++;
        }
        dispx = 0;
        dispy++;
    }
    if (points1 < pointsforend && points2 < pointsforend) {//���� � ����� ������� ���� ������ ���������

        SetConsoleCursorPosition(hStdOut, { sizemapx + 1, sizemapy / 2 - 1 });
        cout << "Player 1: " << points1;//���� ������ ������ 
        SetConsoleCursorPosition(hStdOut, { sizemapx + 1, sizemapy / 2 + 1 });
        cout << "Player 2: " << points2;//���� �������
    }
    else {//������
        flag_win = false;
    }
}
void update() {
    int randomspeed = 0; //��������������� ���������
    if (pongx + pongspeedx < sizemapx - 1 && pongx + pongspeedx != 0 && map[pongy][pongx + pongspeedx] == 0) {
        pongx += pongspeedx;//�������� �� �
    }
    else {

        if (pongx + pongspeedx == sizemapx - 1) {
            if (points1 < pointsforend && points2 < pointsforend) {
                points1++;//�������� �����
                pongx = sizemapx / 2;
                pongy = sizemapy / 2;
            }
        }
        if (pongx + pongspeedx == 0) {
            if (points1 < pointsforend && points2 < pointsforend) {
                points2++;
                pongx = sizemapx / 2;
                pongy = sizemapy / 2;
            }
        }

        randomspeed = rand() % 10; //���� 1 � 10

        pongspeedx = pongspeedx * -1;

        if (randomspeed == 0) {//���� ���� �������� ��  ��������
            pongspeedy = pongspeedy * -1;
        }

    }


    if (pongy + pongspeedy < sizemapy - 1 && pongy + pongspeedy != 0 && map[pongy + pongspeedy][pongx] == 0) {
        pongy += pongspeedy;
    }
    else {
        randomspeed = rand() % 10;

        pongspeedy = pongspeedy * -1;

        if (randomspeed == 0) {
            pongspeedx = pongspeedx * -1;

        }
    }
}
void clearforplayers(int x) {//�������� ����� ���� ��� ������������ �����
    int cfpy = 0;
    while (cfpy < sizemapy) {
        map[cfpy][x] = 0;
        cfpy++;
    }
}
void playersfill() {//���������� ������� ������� ������
    int pf = 0;
    while (pf < 5) {
        map[player1y + pf][3] = 1;
        pf++;
    }
    pf = 0;
    while (pf < 5) {
        map[player2y + pf][sizemapx - 4] = 1;
        pf++;
    }
}
void players() {//��������� �������
    int button = 0;
    clearforplayers(3);
    clearforplayers(sizemapx - 4);
    playersfill();
    if (_kbhit()) { //���� ������ �������
        button = _getch();
        if ((button == 87 || button == 119 || button == 230 || button == 150) && player1y > 1) {//W
            player1y--;
        }
        if ((button == 115 || button == 83 || button == 155 || button == 235) && player1y < sizemapy - 6) {//S
            player1y++;
        }

        if ((button == 73 || button == 105 || button == 152 || button == 232) && player2y > 1) {//I
            player2y--;
        }
        if ((button == 75 || button == 107 || button == 139 || button == 171) && player2y < sizemapy - 6) {//K
            player2y++;
        }
    }
}
int main() {
    while (flag_win) {
        players();//��������� �������
        update();//����
        display();//������
        Sleep(10);//�������� � 10/1000 ������� (10 ���. ���)
    }
    system("cls");
    if (points1 > points2) {

        cout << "Player 1 WIN!";
    }
    else {
        cout << "Player 2 WIN!";
    }
    return 0;
}
