#include "show.h"
TCHAR lives1[10];
TCHAR lives2[10];

void gameover(int winnernum) {
	drawAlpha(&gameimage.winner[winnernum - 1], 0, 0);
}

void showrole() {
	if (role[0].direction == rightdire) {
		putimage((int)role[0].x, (int)role[0].y, &gameimage.img_role[0], SRCAND);
		putimage((int)role[0].x, (int)role[0].y, &gameimage.img_role[1], SRCINVERT);
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
	return;
}

void showpanel() {
  Resize(&hp1, hpwidth * (role[0].hp / (double)initialhp), hpheight);
  drawAlpha(&gameimage.role_panel, 100, 35);
  drawAlpha(&hp1, 138, 54);
  Resize(&hp2, hpwidth * (role[1].hp / (double)initialhp), hpheight);
  drawAlpha(&gameimage.role_panel, 890, 35);
  drawAlpha(&hp2, 928, 54);

  outtextxy(142, 40, _T("玩家1"));
  outtextxy(933, 40, _T("玩家2"));

	_stprintf_s(lives1, _T("生命数：%d"), role[0].lives);
	_stprintf_s(lives2, _T("生命数：%d"), role[1].lives);
	outtextxy(194, 39, lives1);
	outtextxy(984, 39, lives2);
	return;
}