#include <windows.h>
#include "colorConsole.h"

#define KEY_BOARD   0x20
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_ESC     27
#define MAPW    12     //地图的宽度
#define MAPH    20     //地图的高度
int map[MAPH][MAPW]={0}; //保存工作区的区域
WORD SQUARE_COLOR[7] ={ FOREGROUND_RED|FOREGROUND_INTENSITY,
                        FOREGROUND_GREEN|FOREGROUND_INTENSITY,
						FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
						FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
					 };		

//int map[MAPH][MAPW] = {0}; //保存工作区的区域
HANDLE handle;
const int  dx = 24 ; //初始化屏幕时起始坐标
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
	
int score;  //初始化分数
int level;  //初始化游戏级别
int mscore;//从文件读取最高分
int Num ; //创建第一个方块编号
int nextNum;    //保存下一个方块编号

int blank;  //记录每个方块起始位置
int x ;
int y ;  //记录游戏开始的相对坐标


public:
	Teris();
	void Init();//初始化工作			
    void Turn(int a[][4],int w,int h,int *x,int y);    //方块转动
    bool IsAvailable(int a[],int x,int y,int w,int h); //判定是否能放下
    void DrawBlocks(int a[],int w,int h,int x,int y,WORD wColors[],int nColors);
    void ClearSquare(int a[],int w,int h,int x,int y);
    void GameOver();
    void DeleteLine(int m[][MAPW],int row);  //消除一行
    void FileIn();
    void Fileout();
	void create();
	void Key_read(int &delay,int &max_delay,WORD wColors[]);
	void Play();
};
