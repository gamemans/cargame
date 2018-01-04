#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "CServer.h"

/*
struct SCard
{
	int id;
	int num;
	bool bUse;
	SCard()
	{
		bUse = false;
	}

	bool operator==(SCard &other)
	{
		if(this->num == other.num)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(int num)
	{
		return this->num == num;
	}

	int operator-(int num)
	{
		return this->num - num;
	}
	int operator+(int num)
	{
		return this->num + num;
	}
};

SCard g_Cards[136];

bool iske(SCard * data)
{
	if(data[0] == data[1] && data[0] == data[2])	
	{
		return true;
	}

	return false;

}

bool isshun(SCard * data)
{
	if(data[0] == data[1] - 1 && data[0] == data[2] - 2)
	{
		return true;
	}
	return false;
}
bool isdui(SCard * data)
{
	return data[0] == data[1];
}

int flag[14] = {0};

#define GetData(n) \
	if(data[n].bUse == true)\
continue;\
tmp[tmpnum++] = data[n];\
data[n].bUse = true;

bool hu(SCard * data, int num)
{

	if(num == 0)
	{
		return true;
	}

	if(num == 2)
	{
		return isdui(data);
	}

	SCard tmp[14];
	int tmpnum = 0;
	for(int i = 0; i < num - 2; i++)
	{
		GetData(i)
			for(int j = i + 1; j < num - 1; j++)
			{
				GetData(j);
				for(int k = j + 1; k < num; k++)
				{		
					GetData(k);

					if(iske(tmp)||isshun(tmp))
					{
						SCard ttt[14];
						int f = 0;
						for(int t = 0; t < num; t++)
						{
							if(data[t].bUse == false)
							{
								ttt[f++] = data[t];
							}
						}
						if(hu(ttt, f))
						{
							return true;
						}
						else
						{
							data[k].bUse = false;
							tmpnum--;
						}

					}
					else
					{
						data[k].bUse = false;
						tmpnum--;

					}

				}

				data[j].bUse = false;
				tmpnum--;

			}

		data[i].bUse = false;
		tmpnum--;

	}

	return false;
}
void sort(SCard * data, int num)
{
	int k = 0;
	for(int i = 0; i < num - 1; i++)
	{
		k = i;
		for(int j = i; j < num; j++)
		{
			if(data[k].num > data[j].num)
			{
				k = j;
			}
		}

		if(k != i)
		{
			SCard t = data[k];
			data[k] = data[i];
			data[i] = t;
		}
	}
}

void PrintCards()
{
	printf("==============build card==========================\n");
	for(int i = 0; i < 136; i++)
	{   
		if(i % 4 == 0)
		{   
			printf("\n");
		}   
		printf("id:%3d,num:%2d\t", g_Cards[i].id, g_Cards[i].num);
	}    


	printf("\n");
}


void InitCard()
{
	for(int i = 0; i < 136; i++)
	{
		g_Cards[i].id = i;
		g_Cards[i].num = (i / 4 % 9 + 1) + i / 36 * 10;
	}
	///==================================================

	PrintCards();
}

void FlushCard()
{
	printf("==============flush card===========================\n");


	for(int i = 0; i < 136; i++)
	{
		int n = rand() % 136;
		int m = rand() % 136;

		if(m != n)
		{
			SCard t = g_Cards[m];
			g_Cards[m] = g_Cards[n];
			g_Cards[n] = t;
		}
	}


	PrintCards();

}
void FaPai()
{

}

int MoPai()
{

}
*/
#include "time.h"
#include "CMJGame.h"
int main(int argc, char ** argv)
{

	   srand((int)time(0));
	/*


	rand(time(NULL));

	InitCard();

	FlushCard();

	printf("===================================\n");
	SCard data[14];

	data[0].num = 1;
	data[1].num = 1;
	data[2].num = 1;

	data[3].num = 1;
	data[4].num = 2;
	data[5].num = 2;

	data[6].num = 2;
	data[7].num = 2;
	data[8].num = 3;

	data[9].num = 3;
	data[10].num = 3;
	data[11].num = 3;

	data[12].num = 4;
	data[13].num = 5;


	sort(data, 14);
	bool b = hu(data, 14);


	printf("%d\n", b);
*/
	CMJGame g_Game;

	if(g_Server.Init())
	{
		g_Server.Start(argc, argv);
	}


	return 0;
}
