#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 17
#define CONDITION 5

void CheckerBoard_Init();
void CheckerBoard_Display();
int CheckerBoard_Play();
int White_Play(int x,int y);
int Black_Play(int x,int y);

typedef struct{
	int x;
	int y;
}coordinate;

char CheckerBoard[MAX][MAX];
coordinate position;
int Step_Number;
int Victory_Flag;

int main()
{
	CheckerBoard_Init();
	CheckerBoard_Display();
	while(!Victory_Flag)
	{
		Victory_Flag=CheckerBoard_Play();
	}
	switch(Victory_Flag)
	{
		case 1:
			printf("=======================================\n");
			printf("             White Win!\n");
			printf("=======================================\n");
			break;
		case 2:
			printf("=======================================\n");
			printf("             Black Win!\n");
			printf("=======================================\n");
			break;
		case 3:
			printf("=======================================\n");
			printf("               Draw!\n");
			printf("=======================================\n");
	}
	return 0;
}

void CheckerBoard_Init()
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(i==0||i==MAX-1)
			{
				CheckerBoard[i][j]=j;
			}
			else if(j==0||j==MAX-1)
			{
				CheckerBoard[i][j]=i;
			}
			else
			{
				CheckerBoard[i][j]='.';
			}
		}
	}
}

void CheckerBoard_Display()
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(i==0||i==MAX-1)
			{
				printf("%2d",CheckerBoard[i][j]);
			}
			else if(j==0||j==MAX-1)
			{
				printf("%2d",CheckerBoard[i][j]);
			}
			else
			{
				printf(" %c",CheckerBoard[i][j]);
			}
		}
		printf("\n");
	}
}

int CheckerBoard_Play()
{
	int Flag=3;
	while(Flag==3 && Step_Number!=(MAX-2)*(MAX-2))
	{
		if(!(Step_Number%2))
		{
			printf("=======================================\n");
			printf("    Block:x    Steps:%d\n",Step_Number+1);
			printf("=======================================\n");
		}
		else
		{
			printf("=======================================\n");
			printf("               Steps:%d    White:o\n",Step_Number+1);
			printf("=======================================\n");
		}
		printf("input position x and y:");
		scanf("%d%d",&position.x,&position.y);
		scanf("%*[^\n]");
		scanf("%*c");
		if(position.x==0||position.x>=MAX-1||position.y==0||position.y>=MAX-1)
		{
			printf("=======================================\n");
			printf("          Beyond the Boundary!\n");
			printf("=======================================\n");
		}
		else if(CheckerBoard[position.x][position.y]=='.')
		{
			if(!(Step_Number % 2))
			{
				Flag=Black_Play(position.x,position.y);
			}
			else
			{
				Flag=White_Play(position.x,position.y);
			}
			Step_Number++;
		}
		else
		{
			printf("=======================================\n");
			printf("                Cover!\n");
			printf("=======================================\n");
		}
		CheckerBoard_Display();
	}
	return Flag;
}

int White_Play(int x,int y)
{
	int i,Transverse=1,Vertical=1,LeftOblique=1,RightOblique=1;
	CheckerBoard[x][y]='o';
	for(i=1;CheckerBoard[x-i][y]=='o';i++)
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x+i][y]=='o';i++)
	{
		Vertical++;
	}
	for(i=1;CheckerBoard[x][y-i]=='o';i++)
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x][y+i]=='o';i++)
	{
		Transverse++;
	}
	for(i=1;CheckerBoard[x-i][y+i]=='o';i++)
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y-i]=='o';i++)
	{
		LeftOblique++;
	}
	for(i=1;CheckerBoard[x+i][y+i]=='o';i++)
	{
		RightOblique++;
	}
	for(i=1;CheckerBoard[x-i][y-i]=='o';i++)
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
	return 0;
}

int Black_Play(int x,int y)
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
	return 0;
}
