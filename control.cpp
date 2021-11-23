#include <graphics.h>
#include "control.h"
#include "image.h"
#include "bullet.h"
#include "key.h"

int state;
bool playbgmusic;

void startgame() {
	bullet_time1 = bullet_time2 = clock();
	role[0].lives = 5;
	role[1].lives = 5;
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

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}