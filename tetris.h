#include <windows.h>
#include "colorConsole.h"

#define KEY_BOARD   0x20
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_ESC     27
#define MAPW    12     //��ͼ�Ŀ��
#define MAPH    20     //��ͼ�ĸ߶�
int map[MAPH][MAPW]={0}; //���湤����������
WORD SQUARE_COLOR[7] ={ FOREGROUND_RED|FOREGROUND_INTENSITY,
                        FOREGROUND_GREEN|FOREGROUND_INTENSITY,
						FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
					 };		

//int map[MAPH][MAPW] = {0}; //���湤����������
HANDLE handle;
const int  dx = 24 ; //��ʼ����Ļʱ��ʼ����
const int  dy = 3;
int b[7][4][4]={	{{1},{1,1,1}},
					{{0,2},{2,2,2}},
					{{3,3},{0,3,3}},
					{{0,0,4},{4,4,4}},
					{{0,5,5},{5,5}},
                    {{6,6,6,6}},
                    {{7,7},{7,7}}
                };
int a[4][4]={0};
class Teris
{
	
int score;  //��ʼ������
int level;  //��ʼ����Ϸ����
int mscore;//���ļ���ȡ��߷�
int Num ; //������һ��������
int nextNum;    //������һ��������

int blank;  //��¼ÿ��������ʼλ��
int x ;
int y ;  //��¼��Ϸ��ʼ���������


public:
	Teris();
	void Init();//��ʼ������			
    void Turn(int a[][4],int w,int h,int *x,int y);    //����ת��
    bool IsAvailable(int a[],int x,int y,int w,int h); //�ж��Ƿ��ܷ���
    void DrawBlocks(int a[],int w,int h,int x,int y,WORD wColors[],int nColors);
    void ClearSquare(int a[],int w,int h,int x,int y);
    void GameOver();
    void DeleteLine(int m[][MAPW],int row);  //����һ��
    void FileIn();
    void Fileout();
	void create();
	void Key_read(int &delay,int &max_delay,WORD wColors[]);
	void Play();
};
