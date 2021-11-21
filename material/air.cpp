#include<stdio.h>
#include<conio.h>
#include<graphics.h>//要安装的，图形库头文件easyx
#include<mmsystem.h>//win32 多媒体设备接口
//微信公众号：C语言Plus
#pragma comment(lib,"winmm.lib")
#define WIN_WIDTH 591
#define WIN_HEIGHT 864     
#define BULLET_NUM 15//最大子弹数量
#define ENEMYPLANE_NUM 10

struct Image
{
	IMAGE bakcGround;//背景图片
	IMAGE player[4];
	IMAGE bullet[2];
	IMAGE enemy[4];
}image;
//结构体三兄弟，结构体，枚举，联合
enum TYPE
{
	SMALL,
	BIG,
};
struct Plane //我，敌机，子弹
{
	int x;
	int y;
	bool flag;//是否存活  true flase
	union
	{
		int type;//敌机独有属性
		int score;//玩家独有属性
	}un;
	int hp;//血量
}player, bullet[BULLET_NUM], enemy[ENEMYPLANE_NUM];
DWORD t1, t2, t3, t4;
int a[3] = { 1,2,3 };//播放哪个音乐
DWORD WINAPI PlayGun(LPVOID lparamter);
//分模块处理，专门的事情，专门的函数做
//确定飞机的类型
void EnemyHP(int i)
{
	if (rand() % 10 == 0) //十分之一的概率产生一个大飞机
	{
		enemy[i].un.type = BIG;
		enemy[i].hp = 3;
	}
	else
	{
		enemy[i].un.type = SMALL;
		enemy[i].hp = 1;
	}
}
//加载图片
void GameInit()
{
	//设置随机数种子
	srand(GetTickCount());
	t1 = t2 = t3 = t4 = GetTickCount();//获取系统开机到当前所经过的毫秒数
	//播放音乐
	mciSendString("open ./images/game_music.mp3 alias BGM", 0, 0, 0);//向多媒体设备接口发送字符串 media device interface 
	mciSendString("play BGM repeat", 0, 0, 0);
	//加载背景图片
	loadimage(&image.bakcGround, "./images/background.jpg");//把图片加载并保存
	loadimage(&image.player[0], "./images/planeNormal_1.jpg");
	loadimage(&image.player[1], "./images/planeNormal_2.jpg");
	loadimage(&image.player[2], "./images/boom_1.jpg");
	loadimage(&image.player[3], "./images/boom_2.jpg");
	loadimage(&image.bullet[0], "./images/bullet1.jpg");
	loadimage(&image.bullet[1], "./images/bullet2.jpg");
	loadimage(&image.enemy[0], "./images/enemy_1.jpg");
	loadimage(&image.enemy[1], "./images/enemy_2.jpg");
	loadimage(&image.enemy[2], "./images/enemyPlane1.jpg");
	loadimage(&image.enemy[3], "./images/enemyPlane2.jpg");

	//初始化玩家数据
	player.x = WIN_WIDTH / 2;
	player.y = WIN_HEIGHT - 120;
	player.flag = true;
	player.hp = 999;
	player.un.score = 0;
	//初始化子弹数据
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].flag = false;
	}
	//初始化敌机
	for (int i = 0; i < ENEMYPLANE_NUM; i++)
	{
		enemy[i].flag = false;
		EnemyHP(i);
	}
}
//游戏界面绘制
void Gamedraw()
{
	//绘制背景
	putimage(0, 0, &image.bakcGround);
	//绘制玩家
	if (player.flag == true)
	{
		putimage(player.x, player.y, &image.player[0], NOTSRCERASE);
		putimage(player.x, player.y, &image.player[1], SRCINVERT);
	}
	else//玩家死亡，游戏结束
	{
		settextcolor(RED);
		settextstyle(50, 0, "黑体");
		char arr[] = "游戏结束~";
		int tsize = WIN_WIDTH / 2-textwidth(arr)/2;
		outtextxy(tsize, WIN_HEIGHT / 3,arr);
		putimage(player.x, player.y, &image.player[2], NOTSRCERASE);
		putimage(player.x, player.y, &image.player[3], SRCINVERT);
	}

	//绘制子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
		{
			putimage(bullet[i].x, bullet[i].y, &image.bullet[0], NOTSRCERASE);
			putimage(bullet[i].x, bullet[i].y, &image.bullet[1], SRCINVERT);
		}
	}
	for (int i = 0; i < ENEMYPLANE_NUM; i++)
	{
		if (enemy[i].flag)
		{
			if (enemy[i].un.type == TYPE::SMALL)
			{
				putimage(enemy[i].x, enemy[i].y, &image.enemy[0], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &image.enemy[1], SRCINVERT);
			}
			else if (enemy[i].un.type == TYPE::BIG)
			{

				putimage(enemy[i].x, enemy[i].y, &image.enemy[2], NOTSRCERASE);
				putimage(enemy[i].x, enemy[i].y, &image.enemy[3], SRCINVERT);
			}
		}
	}
	//显示分数
	char score[10];
	settextcolor(BLACK);
	settextstyle(20, 0, "黑体");
	sprintf(score, "分数：%d", player.un.score);
	setbkmode(TRANSPARENT);
	outtextxy(10, 10, score);
}
//产生一颗子弹
void CreateBullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == false)
		{
			bullet[i].flag = true;
			bullet[i].x = player.x + 45;
			bullet[i].y = player.y;
			break;
		}
	}
}
//子弹移动
void BulletMove(int speed)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
		{
			bullet[i].y -= speed;
			if (bullet[i].y <= 0)
			{
				bullet[i].flag = false;
			}
		}
	}
}
//产生敌机
void CreateEnemy()
{
	for (int i = 0; i < ENEMYPLANE_NUM; i++)
	{
		if (enemy[i].flag == 0)
		{
			enemy[i].flag = true;
			enemy[i].x = rand() % (WIN_WIDTH - 100);
			enemy[i].y = 0;
			EnemyHP(i);
			break;
		}
	}
}
//敌机移动
void EnemyMove(int speed)
{
	for (int i = 0; i < ENEMYPLANE_NUM; i++)
	{
		if (enemy[i].flag)
		{
			enemy[i].y += speed;
			if (enemy[i].y >= WIN_HEIGHT)
			{
				enemy[i].flag = false;
			}
		}
	}
}
//游戏控制
void GameControl(int speed)
{
	//_getch();GetAnsyncKeyState();
	if (GetAsyncKeyState(VK_UP) && player.y >= 0)
	{
		player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN) && player.y + 120 <= WIN_HEIGHT)
	{
		player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT) && player.x + 50 >= 0)
	{
		player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT) && player.x + 55 <= WIN_WIDTH)
	{
		player.x += speed;
	}
	//发射子弹
	if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 200)
	{
		CreateBullet();
		HANDLE threadID = CreateThread(NULL, 0, PlayGun, a, 0, 0);
		CloseHandle(threadID);
		t1 = t2;
	}
	t2 = GetTickCount();
	if (t4 - t3 > rand() % 500 + 500)
	{
		CreateEnemy();
		t3 = t4;
	}
	t4 = GetTickCount();
	EnemyMove(1);
	BulletMove(1);
}
void PlayEnemyP()
{
	//1，遍历敌机数组  判断是否存活
	for (int i = 0; i < ENEMYPLANE_NUM; i++)
	{
		if (enemy[i].flag == 0)
		{
			continue;
		}
		//计算敌机的宽度和高度
		int width = 0, height = 0;
		if (enemy[i].un.type == BIG)
		{
			width = 100;
			height = 130;
		}
		else if (enemy[i].un.type == TYPE::SMALL)
		{
			width = 50;
			height = 30;
		}
		//退出，写在前面是为了让，死亡画面和文字显示（让程序在运行一次）
		if (player.flag == false)
		{
			MessageBox(GetHWnd(), "你死了`", "Over", MB_OKCANCEL);
			exit(666);
		}
		//玩家和敌机是否相撞
		if (player.x + 50 >= enemy[i].x && player.x + 50 <= enemy[i].x + width
			&& player.y > enemy[i].y && player.y < enemy[i].y + height)
		{
			player.flag = false;
		}
		//2，遍历子弹数组
		for (int k = 0; k < BULLET_NUM; k++)
		{
			if (bullet[k].flag == 0)
			{
				continue;
			}

			//3，判断子弹是否击中敌机
			if (bullet[k].x > enemy[i].x && bullet[k].x<enemy[i].x + width
				&& bullet[k].y>enemy[i].y && bullet[k].y < enemy[i].y + height)
			{
				//4,达到了，属性改变，血量--，存活状态，玩家分数++，
				enemy[i].hp--;
				bullet[k].flag = 0;
				player.un.score++;
				if (player.un.score > 0 && player.un.score % 5 == 0 && player.un.score % 2 != 0)
				{

					HANDLE threadID = CreateThread(NULL, 0, PlayGun, a + 1, 0, 0);
					CloseHandle(threadID);
				}
				if (player.un.score % 10 == 0)
				{
					HANDLE threadID = CreateThread(NULL, 0, PlayGun, a + 2, 0, 0);
					CloseHandle(threadID);
				}
			}
			//5，如果血量为0，敌机死亡
			if (enemy[i].hp <= 0)
			{
				enemy[i].flag = 0;
			}
		}
	}
}
int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);//创建一个图形窗口
	GameInit();
	BeginBatchDraw();//开启双款冲绘图，现在内存里面画好，在现实给你看
	while (1)
	{
		Gamedraw();
		FlushBatchDraw();//我想看了
		GameControl(1);
		PlayEnemyP();
	}
	EndBatchDraw();//结束
	return 0;
}
//播放音乐
DWORD WINAPI PlayGun(LPVOID lparamter)
{
	int* choose = (int*)lparamter;
	printf("%d  \n", *choose);
	if (*choose == 1)
	{
		mciSendString("close f_gun", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open ./images/f_gun.mp3 alias f_gun", NULL, 0, NULL);//打开背景音乐
		mciSendString("play f_gun", NULL, 0, NULL);  // 循环播放
	}
	else if (*choose == 2)
	{
		mciSendString("close 5music", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open ./images/5.mp3 alias 5music", NULL, 0, NULL); // 打开音乐
		mciSendString("play 5music", NULL, 0, NULL); // 仅播放一次
	}
	else if (*choose == 3)
	{
		mciSendString("close 10music", NULL, 0, NULL); // 先把前面一次的音乐关闭
		mciSendString("open ./images/10.mp3 alias 10music", NULL, 0, NULL); // 打开音乐
		mciSendString("play 10music", NULL, 0, NULL); // 仅播放一次
	}

	return 0;
}

