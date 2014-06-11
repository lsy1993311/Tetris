#include "tetris.h"
#include <conio.h>
#include <stdlib.h>

#include <time.h>
#include <fstream>
//#include <mmsystem.h>//��������ͷ�ļ�
//#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

Teris::Teris()
{
	
score=0;  //��ʼ������
level=0;  //��ʼ����Ϸ����
mscore=0;
 Num = rand() %7 ; //������һ��������
 nextNum = Num;    //������һ��������


x = 0;y = 0;  //��¼��Ϸ��ʼ���������


}
void::Teris::Init()
{
		for(int a1=0;a1!=MAPH;++a1)
	for(int b1=0;b1!=MAPW;++b1)
    map[a1][b1] = 0;
	handle=initiate();

	srand(2);//time(NULL));

	//��ʼ��������
	for(int i=0;i<20;i++)
	{
		map[i][0]=-2;
		map[i][11]=-2;
	}
	for(int i=0;i<12;i++)
	{
		map[0][i]=-1;
		map[19][i]=-1;
	}
	map[0][0]=-3;
	map[0][11]=-3;
	map[19][0]=-3;
	map[19][11]=-3;


	WORD wColors[1]={FOREGROUND_GREEN| FOREGROUND_BLUE|FOREGROUND_INTENSITY};
	textout(handle,26+dx,3+dy,wColors,1,"�÷�");
	textout(handle,26+dx,7+dy,wColors,1,"�ȼ�");
    textout(handle,26+dx,11+dy,wColors,1,"��߷�");
	textout(handle,26+dx,15+dy,wColors,1,"������");

	wColors[0]=FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY;
	DrawBlocks(&map[0][0],12,20,0,0,wColors,1);
	textout(handle,dx,dy,wColors,1,"��T�T�T�T�T�T�T�T�T�T��");

	wColors[0]=FOREGROUND_BLUE| FOREGROUND_GREEN|FOREGROUND_INTENSITY;
	textout(handle,28,10,wColors,1,"��ѡ��ȼ���0��9");

	int ch=_getch();
	textout(handle,28,10,wColors,1,"                ");
    if(ch>47&&ch<59)
		level=ch-48;  //�жϵȼ��Ƿ���0��9֮�ڣ�ȷ����ȫ
}

bool Teris::IsAvailable(int a[],int x,int y,int w,int h)
{
	for(int i=y;i<y+h;i++)
		for(int j=x;j<x+w;j++)
			if(map[i][j] && a[w*(i-y)+j-x])
				return false;
	return true;
}

void Teris::DrawBlocks(int a[],int w,int h,int x,int y,WORD wColors[],int nColors)
{
	int temp;
	
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
			if((temp=a[i*w+j])&&y+i>0)
			{
				if(temp==-3)
					textout(handle,2*(x+j)+dx,y+i+dy,wColors,nColors,"��");
				else if(temp==-2)
					textout(handle,2*(x+j)+dx,y+i+dy,wColors,nColors,"�U");
				else if(temp==-1)
					textout(handle,2*(x+j)+dx,y+i+dy,wColors,nColors,"�T");
				else if(temp>=1)
					textout(handle,2*(x+j)+dx,y+i+dy,wColors,nColors,"��");
			}
}

void Teris::Turn(int a[][4],int w,int h,int *x,int y)
{
	int b[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	int sign=0,line=0;
	for(int i=h-1;i>=0;i--)
	{
		for(int j=0;j<w;j++)
			if(a[i][j])
			{
				b[j][line]=a[i][j];
				sign=1;
			}
		if(sign) 
		{
			line++;
			sign=0;
		}
	}
	for(int i=0;i<4;i++)
		if(IsAvailable(b[0],*x-i,y,w,h))
		{
			*x-=i;
			for(int k=0;k<h;k++)
				for(int j=0;j<w;j++)
					a[k][j]=b[k][j];
			break;
		}
}
void Teris::ClearSquare(int *a,int w,int h,int x,int y)
{
	WORD wColors[1]={0};
	for(int i=0;i<h;i++)
		for(int j=0;j<w;j++)
		{
			if(a[i*w+j]>0 && (i+y>0))
			{
				textout(handle,2*(x+j)+dx,y+i+dy,wColors,1,"  ");
			}
		}

}

void Teris::GameOver()
{
	WORD wColors[1]={FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY};
	textout(handle,7+dx,7+dy,wColors,1,"GAME OVER");
    textout(handle,4+dx,8+dy,wColors,1,"PLAY AGAIN? Y/N");
	 while(true){      //����Y��N��Ч����߰�ȫ�ԣ������ִ�Сд
     if(_getch()=='y'||_getch()=='Y')
     return;
     else
     if(_getch()=='n'||_getch()=='N')
     break;
 }
	exit(EXIT_SUCCESS);
}

void Teris::DeleteLine(int m[][MAPW],int row)
{
	WORD wColors[1]={FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY};
	textout(handle,2+dx,row+dy,wColors,1,"�k�k�k�k�k�k�k�k�k�k");
	_sleep(100);

	for(int i=row;i>1;i--)
	{
		ClearSquare(&m[i][1],MAPW-2,1,1,i);
		for(int j=1;j<MAPW-1;j++)
		{
			m[i][j]=m[i-1][j];
			if (m[i][j] == 0)
				wColors[0] = 0;
			else
				wColors[0] = SQUARE_COLOR[m[i][j]-1];
			DrawBlocks(&m[i][j],1,1,j,i,wColors,1);
		}
	}
	for(int i=1;i<MAPW-1;i++)
		m[1][i]=0;
}
void Teris::FileIn()
{   
	//int c=0;
	ifstream ifile("D:\\1.ini");  
    ifile>>mscore;
	ifile.close();
	//mscore=c;
}
void Teris::Fileout()
{  
   ofstream ofile("D:\\1.ini");
   ofile<<mscore<<endl;
   ofile.close();
}

void Teris::Play()
{
	
	while(1)
	{
		for(int i=0;i<4;i++)          //���Ʒ���
			for(int j=0;j<4;j++)
				if(a[i][j] = b[nextNum][i][j]) 
					blank=i;
		
		y = 1- blank;
		x = 4;

		//������һ������
		Num = nextNum;
		ClearSquare(b[Num][0],4,4,13,17);
		nextNum = rand() % 7 ;
		WORD wColors[1]= { SQUARE_COLOR[nextNum] };
		DrawBlocks(b[nextNum][0],4,4,13,17,wColors,1);
	
		wColors[0] = SQUARE_COLOR[Num] ;
		DrawBlocks(&a[0][0],4,4,x,y,wColors,1);

		//��ʾ������Ϣ
		char string[5];
		wColors[0]=FOREGROUND_RED| FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		textout(handle,26+dx,5+dy,wColors,1,itoa(score,string,10));
		textout(handle,26+dx,9+dy,wColors,1,itoa(level,string,10));
		textout(handle,26+dx,13+dy,wColors,1,itoa(mscore,string,10));
	    int max_delay = 100-10*level; //���㲻ͬ��Ϸ���������ʱ����
	    while(1)
		{
			int delay=0; //�ӳ���
			while(delay<max_delay)
			{
				if(_kbhit())  //��if���ⰴס��ʹ���鿨ס
				{   
		            
					int key=_getch();
					switch (key)
					{
					case KEY_UP:
						{
							ClearSquare(&a[0][0],4,4,x,y);
							Turn(a,4,4,&x,y);
							wColors[0]=SQUARE_COLOR[Num];
							DrawBlocks(&a[0][0],4,4,x,y,wColors,1);
						}
						break;
					case KEY_DOWN:
						delay=max_delay;
						break;
					case KEY_LEFT:
						{
							if(IsAvailable(&a[0][0],x-1,y,4,4))
							{
								ClearSquare(&a[0][0],4,4,x,y);
								x--;
								wColors[0]=SQUARE_COLOR[Num];
								DrawBlocks(&a[0][0],4,4,x,y,wColors,1);
							}	
						}
						break;
					case KEY_RIGHT:
						{
							if(IsAvailable(&a[0][0],x+1,y,4,4))
							{
								ClearSquare(&a[0][0],4,4,x,y);
								x++;
								wColors[0]=SQUARE_COLOR[Num];
								DrawBlocks(&a[0][0],4,4,x,y,wColors,1);
							}
						}
						break;
					case KEY_ESC:
						if(score>=mscore)
					    Fileout();  //�뿪ǰ������߷�
						exit(EXIT_SUCCESS);
						break;
					case KEY_BOARD:     
						getch();
						break;
					}
				}

				
				_sleep(8);delay++;
			}
			if(IsAvailable(&a[0][0],x,y+1,4,4)) //�Ƿ�������
			{
				ClearSquare(&a[0][0],4,4,x,y);
				y++;
				wColors[0]=SQUARE_COLOR[Num];
				DrawBlocks(&a[0][0],4,4,x,y,wColors,1);
			}
			else
			{
				if(y<=1){if(score>=mscore)
					Fileout();
				    GameOver();
				    for(y=4;y<22;++y)
                    for(x=26;x<45;++x)
					{textout(handle,x,y,wColors,1,"��");
					Sleep(5);}//��ȴ�ѺõĶ���Ч��
					system("cls");
					Init();
					break;    } //�Ƿ����,�Ƿ�����һ��
				for(int i=0;i<4;i++)     //���·��飬���¹�����
					for(int j=0;j<4;j++)
						if(a[i][j]&&((i+y)<MAPH-1)&&((j+x)<MAPW-1)) 
							map[i+y][j+x]=a[i][j];

				int full,k=0;
				for(int i=y;i<min(y+4,MAPH-1);i++)
				{
					full=1;
					for(int j=1;j<11;j++)
						if(!map[i][j]) full=0;
					if(full)   //����һ��
					{
						DeleteLine(map,i);
						k++;
						score=score+k;
						if(score>mscore)
						mscore=score;          //��ʱ��¼��߷�
						if(level<(score/30))  //��ֹ��ѡ�ȼ���ͻȻ���㼶
						level=min(score/30,9);
						max_delay=100-10*level;
					}
				}
				break; 
			}
		}
}
exit(EXIT_SUCCESS);
}
int main()
{//PlaySound(TEXT("C:\\WINDOWS\\Media\\tada.wav"),NULL, SND_LOOP );
	Teris A;
    //����Ƿ��з����ļ���û���򴴽���ʹ��ini��ʽ��ǿ������
	 fstream _file;
     _file.open("D:\\1.ini",ios::in);
     if(!_file)
     {
         ofstream ofile("D:\\1.ini");
	     ofile<<0<<endl;
      }
	 A.Init();
	 A.FileIn();
	 A.Play();
     return EXIT_SUCCESS;
}
