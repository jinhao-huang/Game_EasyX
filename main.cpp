#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "key.h"
#include "move.h"
#include "Settings.h"
#include "role.h"
#include "image.h"
#include "bullet.h"
#include "show.h"
#include "image.h"

void gameinit() {
	loadimage(&gameimage.background1, _T("image\\background_0.png"));
	loadimage(&gameimage.background2[0], _T("image\\background_1_0.jpg"));
	loadimage(&gameimage.background2[1], _T("image\\background_1_1.jpg"));

	loadimage(&gameimage.img_role[0], _T("image\\role.jpg"));
	loadimage(&gameimage.img_role[1], _T("image\\role_red.jpg"));
	loadimage(&gameimage.img_role[2], _T("image\\role_blue.jpg"));

	loadimage(&gameimage.img_role_left[0], _T("image\\role_left.jpg"));
	loadimage(&gameimage.img_role_left[1], _T("image\\role_red_left.jpg"));
	loadimage(&gameimage.img_role_left[2], _T("image\\role_blue_left.jpg"));


	loadimage(&gameimage.bullet[0], _T("image\\bullet_0.jpg"));
	loadimage(&gameimage.bullet[1], _T("image\\bullet_1.jpg"));

	loadimage(&gameimage.bullet_left[0], _T("image\\bullet_left_0.jpg"));
	loadimage(&gameimage.bullet_left[1], _T("image\\bullet_left_1.jpg"));

	loadimage(&gameimage.hit[0], _T("image\\hit_0.jpg"));
	loadimage(&gameimage.hit[1], _T("image\\hit_1.jpg"));

	loadimage(&gameimage.fire[0], _T("image\\fire_0.jpg"));
	loadimage(&gameimage.fire[1], _T("image\\fire_1.jpg"));
	loadimage(&gameimage.fire_left[0], _T("image\\fire_0_left.jpg"));
	loadimage(&gameimage.fire_left[1], _T("image\\fire_1_left.jpg"));

	initbullet();
	initimagelinks();

	DWORD bullet_time1 = bullet_time2 = GetTickCount();

	role[0].num = 0;
	role[1].num = 1;
	reborn(role[0]);
	reborn(role[1]);
 	//loadimage(&gameimage.background3[0], _T("image\\background_2_0.jpg"));
	//loadimage(&gameimage.background3[1], _T("image\\background_2_1.jpg"));
	return;
}

int centerx(IMAGE& back, IMAGE& front) {
	return (back.getwidth() - front.getwidth()) / 2;
}

int main () {
	initgraph (width, height, EW_SHOWCONSOLE);
	gameinit ();
	clock_t time = clock();
	while (1) {
	BeginBatchDraw();
	putimage (0, 0, &gameimage.background1);
	/*
	putimage (centerx(gameimage.background1, gameimage.background3[0]), 0, &gameimage.background3[0], SRCAND);
	putimage (centerx(gameimage.background1, gameimage.background3[1]), 0, &gameimage.background3[1], SRCINVERT);
	*/
	putimage (centerx(gameimage.background1, gameimage.background2[0]), 0, &gameimage.background2[0], SRCAND);
	putimage (centerx(gameimage.background1, gameimage.background2[1]), 0, &gameimage.background2[1], SRCINVERT);

	if (role[0].direction == rightdire) {
		putimage ((int)role[0].x, (int)role[0].y, &gameimage.img_role[0], SRCAND);
		putimage ((int)role[0].x, (int)role[0].y, &gameimage.img_role[1], SRCINVERT);
	}
	else {
		putimage((int)role[0].x, (int)role[0].y, &gameimage.img_role_left[0], SRCAND);
		putimage((int)role[0].x, (int)role[0].y, &gameimage.img_role_left[1], SRCINVERT);
	}
	
	if (role[1].direction == rightdire) {
		putimage((int)role[1].x, (int)role[1].y, &gameimage.img_role[0], SRCAND);
		putimage((int)role[1].x, (int)role[1].y, &gameimage.img_role[2], SRCINVERT);
	}
	else {
		putimage((int)role[1].x, (int)role[1].y, &gameimage.img_role_left[0], SRCAND);
		putimage((int)role[1].x, (int)role[1].y, &gameimage.img_role_left[2], SRCINVERT);
	}

	initkey();
	getorder();

	move1(role[0], clock() - time);
	move2(role[1], clock() - time);
	time = clock();

	updataimage();
	updatabullet();

	showpoint();
	EndBatchDraw();
	if (role[0].hp <= 0) {
		reborn(role[0]);
	}
	if (role[1].hp <= 0) {
		reborn(role[1]);
	}

	}
	while (1);
	return 0;
}