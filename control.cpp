#include "control.h"

int state;
bool playbgmusic;
LOGFONT myfont;
FILE* fp = NULL;

void startgame() {
	clearbullet();
	myfont.lfHeight = 12;
	myfont.lfWeight = FW_NORMAL;
	settextstyle(&myfont);
	bullet_time1 = bullet_time2 = clock();
	role[0].lives = rolelives;
	role[1].lives = rolelives;
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
	gettextstyle(&myfont);
	_tcscpy_s(myfont.lfFaceName, _T("ºÚÌå"));
	myfont.lfQuality = PROOF_QUALITY;
	settextstyle(&myfont);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "»ìÂÒ´óÇ¹Õ½");

	role[0].num = 0;
	role[1].num = 1;
	playbgmusic = false;

	return;
}

void initsettings() {
	fopen_s(&fp, "settings.ini", "r");
	if (fp == NULL)
		return;
	else {
		fscanf_s(fp, "Player1:%s\n", player1, sizeof(player1));
		fscanf_s(fp, "Player2:%s\n", player2, sizeof(player2));
		fscanf_s(fp, "Rolelives:%d\n", &rolelives);
		fclose(fp);
		return;
	}
}

void writesettings() {
	fopen_s(&fp, "settings.ini", "w");
	if (fp == NULL) {
		exit(0);
	}
	else {
		fprintf_s(fp, "Player1:%s\n", player1);
		fprintf_s(fp, "Player2:%s\n", player2);
		fprintf_s(fp, "Rolelives:%d\n", rolelives);
		fclose(fp);
		return;
	}
}

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}