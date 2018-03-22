#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 17		//棋盘大小，15*15有两行数字标识
#define CONDITION 5		//胜利条件：五子连珠

void CheckerBoard_Init();			//棋盘初始化函数
void CheckerBoard_Display();			//棋盘显示函数
int CheckerBoard_Play();				//对局开始函数
int White_Play(int x,int y);			//白子落子期间
int Black_Play(int x,int y);			//黑子落子期间

typedef struct{
	int x;
	int y;
}coordinate;		//坐标结构体

char CheckerBoard[MAX][MAX];		//地图二维数组
coordinate position;				//用来接收用户输入的坐标
int Step_Number;					//用来计算步数
int Victory_Flag;					//胜利结果

int main()
{
	CheckerBoard_Init();		//棋盘初始化
	CheckerBoard_Display();		//棋盘显示
	while(!Victory_Flag)		//当有结果时跳出循环
	{
		Victory_Flag=CheckerBoard_Play();	//用来接收对局结果
	}
	switch(Victory_Flag)
	{
		case 1:			//如果接收为1，则白棋胜利
			printf("=======================================\n");
			printf("		  White Win! Steps:%d\n",Step_Number);
			printf("=======================================\n");
			break;
		case 2:			//如果接收为2，则黑旗胜利
			printf("=======================================\n");
			printf("          Black Win! Steps:%d\n",Step_Number);
			printf("=======================================\n");
			break;
		case 3:			//如果接收为3，则平局
			printf("=======================================\n");
			printf("              Draw! Steps:%d\n",Step_Number);
			printf("=======================================\n");
	}
	return 0;
}

void CheckerBoard_Init()		//棋盘初始化函数
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(i==0||i==MAX-1)			//如果是棋盘边缘则赋给他对应坐标
			{
				CheckerBoard[i][j]=j;
			}
			else if(j==0||j==MAX-1)
			{
				CheckerBoard[i][j]=i;
			}
			else						//如果不是棋盘边缘则赋给他'.'
			{
				CheckerBoard[i][j]='.';
			}
		}
	}
}

void CheckerBoard_Display()				//显示棋盘函数
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(i==0||i==MAX-1)			//如果是棋盘边缘则用打印数字
			{
				printf("%2d",CheckerBoard[i][j]);
			}
			else if(j==0||j==MAX-1)
			{
				printf("%2d",CheckerBoard[i][j]);
			}
			else				//如果不是棋盘边缘则打印字符
			{
				printf(" %c",CheckerBoard[i][j]);
			}
		}
		printf("\n");
	}
}

int CheckerBoard_Play()			//对局期间函数
{
	int Flag=3;
	while(Flag==3 && Step_Number!=(MAX-2)*(MAX-2))
	{
		if(!(Step_Number%2))		//如果步数为单数则黑旗落子阶段，如果为双数则白棋落子阶段
		{
			printf("=======================================\n");
			printf("    Black:x    Steps:%d\n",Step_Number+1);
			printf("=======================================\n");
		}
		else
		{
			printf("=======================================\n");
			printf("               Steps:%d    White:o\n",Step_Number+1);
			printf("=======================================\n");
		}
		printf("input position x and y:");
		scanf("%d%d",&position.x,&position.y);		//接收用户的坐标
		scanf("%*[^\n]");			//清空输入缓存区
		scanf("%*c");
		if(position.x==0||position.x>=MAX-1||position.y==0||position.y>=MAX-1)	//如果落子落在棋盘外则提示超出边界
		{
			printf("=======================================\n");
			printf("         Beyond the Boundary!\n");
			printf("=======================================\n");
		}
		else if(CheckerBoard[position.x][position.y]=='.')			//如果没有落在棋盘外并且此位置没有被别的棋子占领就执行落子程序
		{
			if(!(Step_Number % 2))
			{
				Flag=Black_Play(position.x,position.y);		//步数为单执行黑子落子程序
			}
			else
			{
				Flag=White_Play(position.x,position.y);		//步数为双执行白子落子程序
			}
			Step_Number++;		//步数加一
		}
		else			//如果落子位置已经存在别的棋子，则提示覆盖错误
		{
			printf("=======================================\n");
			printf("                Cover!\n");
			printf("=======================================\n");
		}
		CheckerBoard_Display();	//打印棋盘
	}
	return Flag;
}

int White_Play(int x,int y)		//白棋落子程序
{
	int i,Transverse=1,Vertical=1,LeftOblique=1,RightOblique=1;	//三个变量用来计算横竖，左斜右斜的连珠数量，如果达到5颗则白棋判胜
	CheckerBoard[x][y]='o';						//把用户输入的落子位置改成'o'
	for(i=1;CheckerBoard[x-i][y]=='o';i++)		//计算落子位置竖向上边连珠的个数
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x+i][y]=='o';i++)		//计算落子位置竖向下边连珠的个数
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x][y-i]=='o';i++)		//计算落子位置横向左边连珠的个数
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x][y+i]=='o';i++)		//计算落子位置横向右边连珠的个数
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x-i][y+i]=='o';i++)	//计算落子位置左斜向右上边连珠的个数
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y-i]=='o';i++)	//计算落子位置左斜向左下边连珠的个数
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y+i]=='o';i++)	//计算落子位置右斜向右下边连珠的个数
	{
		RightOblique++;
	}
	for(i=1;CheckerBoard[x-i][y-i]=='o';i++)	//计算落子位置右斜向左上边连珠的个数
	{
		RightOblique++;
	}
	if( Vertical==CONDITION || 
		Transverse==CONDITION ||
		LeftOblique==CONDITION ||
		RightOblique==CONDITION)		//如果连珠的个数达到判胜条件则返回1
	{
		return 1;
	}
	return 3;		//如果没有达到则返回3，继续循环
}

int Black_Play(int x,int y)		//黑子落子阶段，代码和白棋一样，黑旗达到胜利条件返回2
{
	int i,Transverse=1,Vertical=1,LeftOblique=1,RightOblique=1;
	CheckerBoard[x][y]='x';
	for(i=1;CheckerBoard[x-i][y]=='x';i++)
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x+i][y]=='x';i++)
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x][y-i]=='x';i++)
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x][y+i]=='x';i++)
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x-i][y+i]=='x';i++)
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y-i]=='x';i++)
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y+i]=='x';i++)
	{
		RightOblique++;
	}
	for(i=1;CheckerBoard[x-i][y-i]=='x';i++)
	{
		RightOblique++;
	}
	if( Vertical==CONDITION || 
		Transverse==CONDITION ||
		LeftOblique==CONDITION ||
		RightOblique==CONDITION)
	{
		return 2;
	}
	return 3;
}
