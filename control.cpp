#include <graphics.h>
#include "control.h"
#include "image.h"
#include "bullet.h"
#include "key.h"

int state;
bool playbgmusic;

void startgame() {
	clearbullet();
	bullet_time1 = bullet_time2 = clock();
	role[0].lives = 5;
	role[1].lives = 5;
	role[0].direction = leftdire;
	role[1].direction = rightdire;
	reborn(role[0]);
	reborn(role[1]);
}

void initgame() {
	initbullet();
	initimagelinks();
	hpwidth = gameimage.hp.getwidth();
	hpheight = gameimage.hp.getheight();

	LOGFONT myfont;
	gettextstyle(&myfont);
	myfont.lfHeight = 12;
	myfont.lfWeight = FW_NORMAL;
	_tcscpy_s(myfont.lfFaceName, _T("黑体"));
	myfont.lfQuality = PROOF_QUALITY;
	settextstyle(&myfont);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "混乱大枪战");

	role[0].num = 0;
	role[1].num = 1;
	playbgmusic = false;

	return;
}

void initsettings(FILE* fp) {
	fopen_s(&fp, "settings.ini", "r");
	if (fp == NULL)
		return;
	else {
		fscanf_s(fp, "Player1:%s\n", player1, sizeof(player1));
		fscanf_s(fp, "Player2:%s\n", player2, sizeof(player2));
		fclose(fp);
		return;
	}
}

void writesettings(FILE* fp) {
	fopen_s(&fp, "settings.ini", "w");
	if (fp == NULL) {
		exit(0);
	}
	else {
		fprintf_s(fp, "Player1:%s\n", "玩家a");
		fprintf_s(fp, "Player2:%s\n", "玩家b");
		fclose(fp);
		return;
	}
}

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}
